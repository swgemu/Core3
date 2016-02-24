local QuestManager = require("managers.quest.quest_manager")
local ObjectManager = require("managers.object.object_manager")
local SpawnMobiles = require("utils.spawn_mobiles")

DathWomanEncounter = Encounter:new {
	-- Task properties
	taskName = "DathWomanEncounter",
	-- Encounter properties
	minimumTimeUntilEncounter = 1 * 1000, -- 1 second
	maximumTimeUntilEncounter = 5 * 1000, -- 5 seconds
	encounterDespawnTime = 5 * 60 * 1000, -- 5 minutes
	despawnMessage = "@quest/force_sensitive/intro:woman_leave",
	spawnObjectList = {
		{ template = "old_man", minimumDistance = 64, maximumDistance = 96, referencePoint = 0, followPlayer = true, setNotAttackable = true, runOnDespawn = true }
	},
	onEncounterSpawned = nil,
	isEncounterFinished = nil,
	onEncounterInRange = nil,
	inRangeValue = 16,
}

function DathWomanEncounter:getPlayerFirstName(pCreatureObject)
	local firstName = CreatureObject(pCreatureObject):getFirstName()

	if firstName == nil then
		return ""
	end

	return firstName
end

function DathWomanEncounter:sendGreetingString(pWoman, pCreatureObject)
	local greetingString = LuaStringIdChatParameter("@quest/force_sensitive/intro:woman_greeting")
	local firstName = self:getPlayerFirstName(pCreatureObject)
	greetingString:setTT(firstName)
	spatialChat(pWoman, greetingString:_getObject())
end

function DathWomanEncounter:onEncounterInRange(pCreatureObject, dathWomanPointerList)
	if (pCreatureObject == nil or dathWomanPointerList == nil or dathWomanPointerList[1] == nil) then
		return
	end

	self:sendGreetingString(dathWomanPointerList[1], pCreatureObject)
	QuestManager.activateQuest(pCreatureObject, QuestManager.quests.FS_DATH_wOMAN)
end

function DathWomanEncounter:handleScheduledDespawn(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	self:handleDespawnEvent(pCreatureObject)
end

-- Schedule despawn of old man due to player conversation has ended.
-- @param pCreatureObject pointer to the creature object of the player.
function DathWomanEncounter:scheduleDespawnOfWoman(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	createEvent(10 * 1000, "DathWomanEncounter", "handleScheduledDespawn", pCreatureObject)
end

function DathWomanEncounter:doesWomanBelongToThePlayer(pConversingPlayer, pConversingWoman)
	if (pConversingPlayer == nil or pConversingWoman == nil) then
		return false
	end

	local dathWoman = SpawnMobiles.getSpawnedMobiles(pConversingPlayer, self.taskName)

	if dathWoman ~= nil and dathWoman[1] ~= nil and table.getn(dathWoman) == 1 then
		return SceneObject(pConversingWoman):getObjectID() == SceneObject(dathWoman[1]):getObjectID()
	else
		return false
	end
end

function OldManEncounter:isEncounterFinished(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	return QuestManager.hasCompletedQuest(pCreatureObject, QuestManager.quests.FS_DATH_WOMAN)
end

-- Handling of finishing the encounter.
-- @param pCreatureObject pointer to the creature object of the player.
function OldManEncounter:taskFinish(pCreatureObject)
	if (pCreatureObject == nil) then
		return
	end

	Logger:log("Finishing " .. self.taskName .. " and starting SithShadowEncounter.", LT_INFO)
	SithShadowEncounter:start(pCreatureObject)
end

return OldManEncounter
