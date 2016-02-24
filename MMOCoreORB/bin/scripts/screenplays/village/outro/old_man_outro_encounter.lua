local QuestManager = require("managers.quest.quest_manager")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

local OLD_MAN_GREETING_STRING_EXIT = "@quest/force_sensitive/exit:old_man_greeting"

OldManOutroEncounter = Encounter:new {
	-- Task properties
	taskName = "OldManOutroEncounter",
	-- Encounter properties
	--minimumTimeUntilEncounter = 12 * 60 * 60 * 1000, -- 12 hours
	--maximumTimeUntilEncounter = 24 * 60 * 60 * 1000, -- 24 hours
	minimumTimeUntilEncounter = 5 * 60 * 1000, -- 12 hours
	maximumTimeUntilEncounter = 10 * 60 * 1000, -- 24 hours
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

-- Get the first name of the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return the first name of the player.
function OldManOutroEncounter:getPlayerFirstName(pCreatureObject)
	local firstName = CreatureObject(pCreatureObject):getFirstName()

	if firstName == nil then
		return ""
	end

	return firstName
end

-- Send the greeting string to the player.
-- @param pOldMan pointer to the old man.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManOutroEncounter:sendGreetingString(pOldMan, pCreatureObject)
	Logger:log("Sending greeting string.", LT_INFO)
	local greetingString = LuaStringIdChatParameter(OLD_MAN_GREETING_STRING_EXIT)
	local firstName = self:getPlayerFirstName(pCreatureObject)
	greetingString:setTT(firstName)
	spatialChat(pOldMan, greetingString:_getObject())
end

-- Handling of the encounter in range event.
-- Send the greeting string from the old man and activate the old man quest.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param oldManPointerList a list with a pointer to the old man.
function OldManOutroEncounter:onEncounterInRange(pCreatureObject, oldManPointerList)
	if (pCreatureObject == nil or oldManPointerList == nil or oldManPointerList[1] == nil) then
		return
	end

	self:sendGreetingString(oldManPointerList[1], pCreatureObject)

	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.OLD_MAN_FINAL)
end

-- Event handler for the scheduled despawn of the old man when the player has finished the conversation.
-- @param pCreatureObject pointer to the creatureObject of the player.
function OldManOutroEncounter:handleScheduledDespawn(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	self:handleDespawnEvent(pCreatureObject)
end

-- Schedule despawn of old man due to player conversation has ended.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManOutroEncounter:scheduleDespawnOfOldMan(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	Logger:log("Scheduling despawn of old man.", LT_INFO)
	createEvent(OLD_MAN_DESPAWN_TIME, "OldManOutroEncounter", "handleScheduledDespawn", pCreatureObject, "")
end

-- Check if the player is conversing with the old man that is spawned for the player
-- @param pConversingPlayer pointer to the creature object of the player.
-- @param pConversingOldMan pointer to the creature object of the conversing old man.
-- @return true if the old man belongs to the player.
function OldManOutroEncounter:doesOldManBelongToThePlayer(pConversingPlayer, pConversingOldMan)
	if (pConversingPlayer == nil or pConversingOldMan == nil) then
		return false
	end

	local playerOldMan = SpawnMobiles.getSpawnedMobiles(pConversingPlayer, OldManOutroEncounter.taskName)

	if playerOldMan ~= nil and playerOldMan[1] ~= nil and #playerOldMan == 1 then
		return SceneObject(pConversingOldMan):getObjectID() == SceneObject(playerOldMan[1]):getObjectID()
	else
		return false
	end
end

-- Check if the old man encounter is finished or not.
-- @param pCreatureObject pointer to the creature object of the player.
-- @return true if the encounter is finished. I.e. the player has the crystal.
function OldManOutroEncounter:isEncounterFinished(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	return QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.OLD_MAN_FINAL)
end

-- Handling of finishing the encounter.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManOutroEncounter:taskFinish(pCreatureObject)
	if (pCreatureObject == nil) then
		return true
	end

	-- TODO
	
	return true
end

return OldManOutroEncounter
