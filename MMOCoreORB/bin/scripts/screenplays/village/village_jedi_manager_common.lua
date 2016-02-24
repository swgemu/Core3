local ObjectManager = require("managers.object.object_manager")

VillageJediManagerCommon = ScreenPlay:new {}

VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING = "VillageJediProgression"
VILLAGE_JEDI_PROGRESSION_GLOWING = 1
VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL = 2
VILLAGE_JEDI_PROGRESSION_HAS_VILLAGE_ACCESS = 4
VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE = 8
VILLAGE_JEDI_PROGRESSION_ACCEPTED_MELLICHAE = 16
VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE = 32
VILLAGE_JEDI_PROGRESSION_COMPLETED_PADAWAN_TRIALS = 64

-- Set the jedi progression screen play state on the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param state the state to set.
function VillageJediManagerCommon.setJediProgressionScreenPlayState(pCreatureObject, state)
	if (pCreatureObject == nil) then
		return
	end

	CreatureObject(pCreatureObject):setScreenPlayState(state, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
end

-- Check if the player has the jedi progression screen play state.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param state the state to check if the player has.
-- @return true if the player has the state.
function VillageJediManagerCommon.hasJediProgressionScreenPlayState(pCreatureObject, state)
	if (pCreatureObject == nil) then
		return false
	end

	return CreatureObject(pCreatureObject):hasScreenPlayState(state, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
end

function VillageJediManagerCommon.unlockBranch(pPlayer, branch)
	if (pPlayer == nil) then
		return false
	end

	local questStatusTemp = CreatureObject(pPlayer):getScreenPlayState("VillageUnlockScreenPlay:" .. branch)
	if (questStatusTemp == 0) then
		CreatureObject(pPlayer):setScreenPlayState(2, "VillageUnlockScreenPlay:" .. branch)
	end

	local stringTO = "@quest/force_sensitive/utils:" .. branch

	local messageString = LuaStringIdChatParameter("@quest/force_sensitive/utils:branch_selected_unlock")
	messageString:setTO(stringTO)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

function VillageJediManagerCommon.hasUnlockedBranch(pPlayer, branch)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):hasScreenPlayState(2, "VillageUnlockScreenPlay:" .. branch)
end

function VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local lastActiveQuest = tonumber(getQuestStatus(SceneObject(pPlayer):getObjectID() .. ":village:lastActiveQuest"))

	return phaseID == lastActiveQuest
end

function VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	VillageJediManagerCommon.addToActiveQuestList(pPlayer)
	setQuestStatus(SceneObject(pPlayer):getObjectID() .. ":village:lastActiveQuest", phaseID)
end

function VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local lastCompletedQuest = tonumber(getQuestStatus(SceneObject(pPlayer):getObjectID() .. ":village:lastCompletedQuest"))

	return phaseID == lastCompletedQuest
end

function VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	VillageJediManagerCommon.removeFromActiveQuestList(pPlayer)
	setQuestStatus(SceneObject(pPlayer):getObjectID() .. ":village:lastCompletedQuest", phaseID)
end

function VillageJediManagerCommon.createNewActiveQuestList()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	return createQuestVectorMap("VillageActiveQuestsPhaseID" .. phaseID)
end

function VillageJediManagerCommon.removeActiveQuestList(phaseID)
	removeQuestVectorMap("VillageActiveQuestsPhaseID" .. phaseID)
end

function VillageJediManagerCommon.getActiveQuestList(phaseID)
	return getQuestVectorMap("VillageActiveQuestsPhaseID" .. phaseID)
end

function VillageJediManagerCommon.addToActiveQuestList(pPlayer)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local pMap = VillageJediManagerCommon.getActiveQuestList(phaseID)

	if (pMap == nil) then
		pMap = VillageJediManagerCommon.createNewActiveQuestList()
	end

	local questMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	if (not questMap:hasMapRow(playerID)) then
		questMap:addMapRow(playerID, tostring(os.time()))
	else
		printf("Error in VillageJediManagerCommon.addToActiveQuestList, attempting to add existing player " .. SceneObject(pPlayer):getCustomObjectName() .. " to active quest list.\n")
	end

end

function VillageJediManagerCommon.removeFromActiveQuestList(pPlayer)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	local pMap = VillageJediManagerCommon.getActiveQuestList(phaseID)

	if (pMap == nil) then
		return
	end

	local questMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	if (questMap:hasMapRow(playerID)) then
		questMap:deleteMapRow(playerID)
	end
end

return VillageJediManagerCommon
