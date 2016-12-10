local QuestManager = require("managers.quest.quest_manager")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

local OLD_MAN_GREETING_STRING = "@quest/force_sensitive/intro:oldman_greeting"
local OLD_MAN_DESPAWN_TIME = 10 * 1000
local OLD_MAN_FORCE_CRYSTAL_STRING = "object/tangible/loot/quest/force_sensitive/force_crystal.iff"
local OLD_MAN_FORCE_CRYSTAL_ID_STRING = "force_crystal_id"

OldManIntroEncounter = Encounter:new {
	-- Task properties
	taskName = "OldManIntroEncounter",
	-- Encounter properties
	encounterDespawnTime = 5 * 60 * 1000, -- 5 minutes
	despawnMessage = "@quest/force_sensitive/intro:leave",
	spawnObjectList = {
		{ template = "old_man", minimumDistance = 64, maximumDistance = 96, referencePoint = 0, followPlayer = true, setNotAttackable = true, runOnDespawn = true }
	},
	onEncounterSpawned = nil,
	isEncounterFinished = nil,
	onEncounterInRange = nil,
	inRangeValue = 16,
}

-- Handling of the encounter in range event.
-- Send the greeting string from the old man and activate the old man quest.
-- @param pPlayer pointer to the creature object of the player.
-- @param oldManPointerList a list with a pointer to the old man.
function OldManIntroEncounter:onEncounterInRange(pPlayer, oldManPointerList)
	if (pPlayer == nil or oldManPointerList == nil or oldManPointerList[1] == nil) then
		return
	end

	local greetingString = LuaStringIdChatParameter(OLD_MAN_GREETING_STRING)
	greetingString:setTT(CreatureObject(pPlayer):getFirstName())
	spatialChat(oldManPointerList[1], greetingString:_getObject())

	FsIntro:setCurrentStep(pPlayer, 2)
	QuestManager.activateQuest(pPlayer, QuestManager.quests.OLD_MAN_INITIAL)
end

-- Event handler for the scheduled despawn of the old man when the player has finished the conversation.
-- @param pPlayer pointer to the creatureObject of the player.
function OldManIntroEncounter:handleScheduledDespawn(pPlayer)
	if (pPlayer == nil) then
		return
	end

	self:handleDespawnEvent(pPlayer)
end

-- Schedule despawn of old man due to player conversation has ended.
-- @param pPlayer pointer to the creature object of the player.
function OldManIntroEncounter:scheduleDespawnOfOldMan(pPlayer)
	if (pPlayer == nil) then
		return
	end

	Logger:log("Scheduling despawn of old man.", LT_INFO)
	createEvent(OLD_MAN_DESPAWN_TIME, "OldManIntroEncounter", "handleScheduledDespawn", pPlayer, "")
end

-- Give the force crystal to the player.
-- @param pPlayer pointer to the creature object of the player.
function OldManIntroEncounter:giveForceCrystalToPlayer(pPlayer)
	if (pPlayer == nil) then
		return
	end

	Logger:log("Giving crystal to player.", LT_INFO)

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pCrystal = giveItem(pInventory, OLD_MAN_FORCE_CRYSTAL_STRING, -1)

	if (pCrystal ~= nil) then
		CreatureObject(pPlayer):removeScreenPlayState(0xFFFFFFFFFFFFFFFF, self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)
		CreatureObject(pPlayer):setScreenPlayState(SceneObject(pCrystal):getObjectID(), self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)

		VillageJediManagerCommon.setJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.OLD_MAN_INITIAL)
		QuestManager.completeQuest(pPlayer, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/intro:crystal_message")
		writeScreenPlayData(pPlayer, "VillageJediProgression", "FsIntroOldManVisits", 0)
	end
end

function OldManIntroEncounter:hasForceCrystal(pPlayer)
	local forceCrystalId = CreatureObject(pPlayer):getScreenPlayState(self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)
	local pForceCrystal = getSceneObject(forceCrystalId)

	return pForceCrystal ~= nil
end

-- Remove the force crystal from the player.
-- @param pPlayer pointer to the creature object of the player.
function OldManIntroEncounter:removeForceCrystalFromPlayer(pPlayer)
	if (pPlayer == nil) then
		return
	end

	Logger:log("Removing crystal from player.", LT_INFO)
	local forceCrystalId = CreatureObject(pPlayer):getScreenPlayState(self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)
	local pForceCrystal = getSceneObject(forceCrystalId)

	if pForceCrystal ~= nil then
		SceneObject(pForceCrystal):destroyObjectFromWorld()
		SceneObject(pForceCrystal):destroyObjectFromDatabase()
	end

	CreatureObject(pPlayer):removeScreenPlayState(0xFFFFFFFFFFFFFFFF, self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)

	QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_INITIAL)
	QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)
end

-- Check if the player is conversing with the old man that is spawned for the player
-- @param pPlayer pointer to the creature object of the player.
-- @param pOldMan pointer to the creature object of the conversing old man.
-- @return true if the old man belongs to the player.
function OldManIntroEncounter:doesOldManBelongToThePlayer(pPlayer, pOldMan)
	if (pPlayer == nil or pOldMan == nil) then
		return false
	end

	local playerOldMan = SpawnMobiles.getSpawnedMobiles(pPlayer, OldManIntroEncounter.taskName)

	if playerOldMan ~= nil and playerOldMan[1] ~= nil and #playerOldMan == 1 then
		return SceneObject(pOldMan):getObjectID() == SceneObject(playerOldMan[1]):getObjectID()
	else
		return false
	end
end

-- Check if the old man encounter is finished or not.
-- @param pPlayer pointer to the creature object of the player.
-- @return true if the encounter is finished. I.e. the player has the crystal.
function OldManIntroEncounter:isEncounterFinished(pPlayer)
	if (pPlayer == nil) then
		return true
	end

	return QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)
end

-- Handling of finishing the encounter.
-- @param pPlayer pointer to the creature object of the player.
function OldManIntroEncounter:taskFinish(pPlayer)
	if (pPlayer == nil) then
		return true
	end
	
	local oldManVisits = readScreenPlayData(pPlayer, "VillageJediProgression", "FsIntroOldManVisits")
	
	if (oldManVisits == "") then
		oldManVisits = 1
	else
		oldManVisits = tonumber(oldManVisits) + 1
	end
	
	writeScreenPlayData(pPlayer, "VillageJediProgression", "FsIntroOldManVisits", oldManVisits)

	if (self:isEncounterFinished(pPlayer)) then
		FsIntro:startStepDelay(pPlayer, 3)
	else
		QuestManager.resetQuest(pPlayer, QuestManager.quests.OLD_MAN_INITIAL)
		FsIntro:startStepDelay(pPlayer, 1)
	end

	return true
end

return OldManIntroEncounter
