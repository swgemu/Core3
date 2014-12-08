local Encounter = require("quest.tasks.encounter")
local QuestManager = require("managers.quest.quest_manager")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")
local VillageJediManagerCommon = require("managers.jedi.village.village_jedi_manager_common")
local SithShadowEncounter = require("managers.jedi.village.sith_shadow_encounter")

local OLD_MAN_GREETING_STRING = "@quest/force_sensitive/intro:oldman_greeting"
local OLD_MAN_DESPAWN_TIME = 10 * 1000
local OLD_MAN_FORCE_CRYSTAL_STRING = "object/tangible/loot/quest/force_sensitive/force_crystal.iff"
local OLD_MAN_FORCE_CRYSTAL_ID_STRING = "force_crystal_id"

OldManEncounter = Encounter:new {
	-- Task properties
	taskName = "OldManEncounter",
	-- Encounter properties
	--minimumTimeUntilEncounter = 12 * 60 * 60 * 1000, -- 12 hours
	--maximumTimeUntilEncounter = 24 * 60 * 60 * 1000, -- 24 hours
	minimumTimeUntilEncounter = 5 * 60 * 1000, -- 12 hours
	maximumTimeUntilEncounter = 10 * 60 * 1000, -- 24 hours
	--encounterDespawnTime = 5 * 60 * 1000, -- 5 minutes
	encounterDespawnTime = 5 * 60 * 1000, -- 5 minutes
	spawnObjectList = {
		{ template = "old_man", minimumDistance = 64, maximumDistance = 96, referencePoint = 0, followPlayer = true, setNotAttackable = true }
	},
	onEncounterSpawned = nil,
	isEncounterFinished = nil,
	onEncounterClosingIn = nil,
	onEncounterAtPlayer = nil
}

-- Get the first name of the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return the first name of the player.
function OldManEncounter:getPlayerFirstName(pCreatureObject)
	local firstName = ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return creatureObject:getFirstName()
	end)

	if firstName == nil then
		return ""
	end

	return firstName
end

-- Send the greeting string to the player.
-- @param pOldMan pointer to the old man.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManEncounter:sendGreetingString(pOldMan, pCreatureObject)
	Logger:log("Sending greeting string.", LT_INFO)
	local greetingString = LuaStringIdChatParameter(OLD_MAN_GREETING_STRING)
	local firstName = self:getPlayerFirstName(pCreatureObject)
	greetingString:setTT(firstName)
	spatialChat(pOldMan, greetingString:_getObject())
end

-- Handling of the encounter closing in event.
-- Send the greeting string from the old man and activate the old man quest.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param oldManPointerList a list with a pointer to the old man.
function OldManEncounter:onEncounterClosingIn(pCreatureObject, oldManPointerList)
	self:sendGreetingString(oldManPointerList[1], pCreatureObject)
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.OLD_MAN_INITIAL)
end

-- Event handler for the scheduled despawn of the old man when the player has finished the conversation.
-- @param pCreatureObject pointer to the creatureObject of the player.
function OldManEncounter:handleScheduledDespawn(pCreatureObject)
	self:handleDespawnEvent(pCreatureObject)
end

-- Schedule despawn of old man due to player conversation has ended.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManEncounter:scheduleDespawnOfOldMan(pCreatureObject)
	Logger:log("Scheduling despawn of old man.", LT_INFO)
	createEvent(OLD_MAN_DESPAWN_TIME, "OldManEncounter", "handleScheduledDespawn", pCreatureObject)
end

-- Give the force crystal to the player.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManEncounter:giveForceCrystalToPlayer(pCreatureObject)
	Logger:log("Giving crystal to player.", LT_INFO)
	ObjectManager.withInventoryPointer(pCreatureObject, function(pInventory)
		local pCrystal = giveItem(pInventory, OLD_MAN_FORCE_CRYSTAL_STRING, -1)
		ObjectManager.withSceneObject(pCrystal, function(crystal)
			ObjectManager.withCreatureObject(pCreatureObject, function(creature)
				creature:removeScreenPlayState(0xFFFFFFFFFFFFFFFF, self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)
				creature:setScreenPlayState(crystal:getObjectID(), self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)
				creature:sendSystemMessage("@quest/quests:task_complete")
				creature:sendSystemMessage("@quest/quests:quest_journal_updated")
			end)
		end)
		VillageJediManagerCommon.setJediProgressionScreenPlayState(pCreatureObject, VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL)
		QuestManager.completeQuest(pCreatureObject, QuestManager.quests.OLD_MAN_INITIAL)
		QuestManager.completeQuest(pCreatureObject, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)
	end)
end

-- Remove the force crystal from the player.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManEncounter:removeForceCrystalFromPlayer(pCreatureObject)
	Logger:log("Removing crystal from player.", LT_INFO)
	local forceCrystalId = ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return creatureObject:getScreenPlayState(self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)
	end)
	local pForceCrystal = getSceneObject(forceCrystalId)

	if pForceCrystal ~= nil then
		ObjectManager.withSceneObject(pForceCrystal, function(forceCrystal)
			forceCrystal:destroyObjectFromWorld()
			forceCrystal:destroyObjectFromDatabase()
		end)
	end

	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:sendSystemMessage("@quest/quests:quest_journal_updated")
		return creatureObject:removeScreenPlayState(0xFFFFFFFFFFFFFFFF, self.taskName .. OLD_MAN_FORCE_CRYSTAL_ID_STRING)
	end)

	QuestManager.resetQuest(pCreatureObject, QuestManager.quests.OLD_MAN_INITIAL)
	QuestManager.resetQuest(pCreatureObject, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)
end

-- Check if the player is conversing with the old man that is spawned for the player
-- @param pConversingPlayer pointer to the creature object of the player.
-- @param pConversingOldMan pointer to the creature object of the conversing old man.
-- @return true if the old man belongs to the player.
function OldManEncounter:doesOldManBelongToThePlayer(pConversingPlayer, pConversingOldMan)
	local playerOldMan = SpawnMobiles.getSpawnedMobiles(pConversingPlayer, OldManEncounter.taskName)

	if playerOldMan ~= nil and table.getn(playerOldMan) == 1 then
		return SceneObject(pConversingOldMan):getObjectID() == SceneObject(playerOldMan[1]):getObjectID()
	else
		return false
	end
end

-- Check if the old man encounter is finished or not.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the encounter is finished. I.e. the player has the crystal.
function OldManEncounter:isEncounterFinished(pCreatureObject)
	return QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.OLD_MAN_FORCE_CRYSTAL)
end

-- Handling of finishing the encounter.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManEncounter:taskFinish(pCreatureObject)
	Logger:log("Finishing " .. self.taskName .. " and starting SithShadowEncounter.", LT_INFO)
	SithShadowEncounter:start(pCreatureObject)
end

return OldManEncounter
