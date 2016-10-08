local ObjectManager = require("managers.object.object_manager")

imperialCoordinatorConvoHandler = conv_handler:new {}

function imperialCoordinatorConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	local state = tonumber(readScreenPlayData(pPlayer, "imperial_coa2", "state"))

	if TangibleObject(pPlayer):isRebel() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif pGhost == nil or not PlayerObject(pGhost):hasBadge(EVENT_PROJECT_DEAD_EYE_1) then
		return convoTemplate:getScreen("act1_not_complete")
	elseif state == nil or state == 1 then
		return convoTemplate:getScreen("m1_begin")
	elseif state == 2 then
		return convoTemplate:getScreen("m1_active")
	elseif state == 3 or state == 4 or state == 5 then
		return convoTemplate:getScreen("m2_begin")
	elseif state == 6 then
		return convoTemplate:getScreen("m2_active")
	elseif state == 7 then
		if Coa2Screenplay:hasDisk(pPlayer, "slicer") then
			return convoTemplate:getScreen("m3_begin")
		else
			return convoTemplate:getScreen("m2_active")
		end
	elseif state == 8 then
		return convoTemplate:getScreen("m3_begin")
	elseif state == 9 then
		return convoTemplate:getScreen("m3_active")
	elseif state > 9 then
		return convoTemplate:getScreen("m3_finish")
	end

	return convoTemplate:getScreen("m1_begin")
end

function imperialCoordinatorConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local state = tonumber(readScreenPlayData(pPlayer, "imperial_coa2", "state"))

	if screenID == "m1_begin_yes" then
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "imperial")
	elseif screenID == "m1_active_abort" then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", 1)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m1_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionOne(pPlayer, pNpc, "imperial")
	elseif screenID == "m2_begin" and state == 3 then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", 4)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m2_begin_yes" then
		Coa2Screenplay:startMissionTwo(pPlayer, pNpc, "imperial")
	elseif screenID == "m2_active_abort" then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", 5)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m2_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionTwo(pPlayer, pNpc, "imperial")
	elseif screenID == "m3_begin" and state == 7 then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", 8)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m3_begin_yes" then
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "imperial")
	elseif screenID == "m3_active_abort" then
		writeScreenPlayData(pPlayer, "imperial_coa2", "state", 8)
		Coa2Screenplay:cleanupMission(pPlayer)
	elseif screenID == "m3_active_restart" then
		Coa2Screenplay:cleanupMission(pPlayer)
		Coa2Screenplay:startMissionThree(pPlayer, pNpc, "imperial")
	end

	return pConvScreen
end
