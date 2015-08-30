local ObjectManager = require("managers.object.object_manager")

imperialCoordinatorConvoHandler = Object:new {}

function imperialCoordinatorConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local state = tonumber(readScreenPlayData(pPlayer, "imperial_coa2", "state"))

	if TangibleObject(pPlayer):isRebel() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif state == nil or state == 1 then
		return convoTemplate:getScreen("m1_begin")
	elseif state == 2 then
		return convoTemplate:getScreen("m1_active")
	elseif state == 3 or state == 4 or state == 5 then
		return convoTemplate:getScreen("m2_begin")
	elseif state == 6 then
		return convoTemplate:getScreen("m2_active")
	elseif state == 7 or state == 8 then
		return convoTemplate:getScreen("m3_begin")
	elseif state == 9 then
		return convoTemplate:getScreen("m3_active")
	elseif state > 9 then
		return convoTemplate:getScreen("m3_finish")
	end

	return convoTemplate:getScreen("m1_begin")
end

function imperialCoordinatorConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	local state = tonumber(readScreenPlayData(conversingPlayer, "imperial_coa2", "state"))

	if screenID == "m1_begin_yes" then
		Coa2Screenplay:startMissionOne(conversingPlayer, conversingNPC, "imperial")
	elseif screenID == "m1_active_abort" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 1)
		Coa2Screenplay:cleanupMission(conversingPlayer, 1)
	elseif screenID == "m1_active_restart" then
		Coa2Screenplay:cleanupMission(conversingPlayer, 1)
		Coa2Screenplay:startMissionOne(conversingPlayer, conversingNPC, "imperial")
	elseif screenID == "m2_begin" and state == 3 then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 4)
		Coa2Screenplay:cleanupMission(conversingPlayer, 1)
	elseif screenID == "m2_begin_yes" then
		Coa2Screenplay:startMissionTwo(conversingPlayer, conversingNPC, "imperial")
	elseif screenID == "m2_active_abort" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 5)
		Coa2Screenplay:cleanupMission(conversingPlayer, 2)
	elseif screenID == "m2_active_restart" then
		Coa2Screenplay:cleanupMission(conversingPlayer, 2)
		Coa2Screenplay:startMissionTwo(conversingPlayer, conversingNPC, "imperial")
	elseif screenID == "m3_begin" and state == 7 then
		Coa2Screenplay:finishMissionTwo(conversingPlayer, "imperial")
	elseif screenID == "m3_begin_yes" then
		Coa2Screenplay:startMissionThree(conversingPlayer, conversingNPC, "imperial")
	elseif screenID == "m3_active_abort" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 8)
		Coa2Screenplay:cleanupMission(conversingPlayer, 3)
	elseif screenID == "m3_active_restart" then
		Coa2Screenplay:cleanupMission(conversingPlayer, 3)
		Coa2Screenplay:startMissionThree(conversingPlayer, conversingNPC, "imperial")
	end

	return conversationScreen
end

function imperialCoordinatorConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
