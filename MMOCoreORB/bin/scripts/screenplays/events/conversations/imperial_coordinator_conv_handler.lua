local ObjectManager = require("managers.object.object_manager")

imperialCoordinatorConvoHandler = Object:new {}

function imperialCoordinatorConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local state = tonumber(readScreenPlayData(pPlayer, "imperial_coa2", "state"))

	if TangibleObject(pPlayer):isRebel() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif state == 1 then
		return convoTemplate:getScreen("m1_active")
	elseif state == 2 then
		return convoTemplate:getScreen("m2_begin")
	elseif state == 3 then
		return convoTemplate:getScreen("m2_active")
	elseif state == 4 then
		return convoTemplate:getScreen("m3_begin")
	elseif state == 5 then
		return convoTemplate:getScreen("m3_active")
	elseif state > 5 then
		return convoTemplate:getScreen("m3_finish")
	else
		return convoTemplate:getScreen("m1_begin")
	end
end

function imperialCoordinatorConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if screenID == "m1_begin_yes" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 1)
		coa2ScreenPlay:startMission(conversingPlayer, "imperial", 1)
	elseif screenID == "m1_active_abort" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 0)
		coa2ScreenPlay:cleanupMission(conversingPlayer, "imperial", 1)
	elseif screenID == "m1_active_restart" then
		coa2ScreenPlay:cleanupMission(conversingPlayer, "imperial", 1)
		coa2ScreenPlay:startMission(conversingPlayer, "imperial", 1)
	elseif screenID == "m2_begin_yes" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 3)
		coa2ScreenPlay:startMission(conversingPlayer, "imperial", 2)
	elseif screenID == "m2_active_abort" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 2)
		coa2ScreenPlay:cleanupMission(conversingPlayer, "imperial", 2)
	elseif screenID == "m2_active_restart" then
		coa2ScreenPlay:cleanupMission(conversingPlayer, "imperial", 2)
		coa2ScreenPlay:startMission(conversingPlayer, "imperial", 2)
	elseif screenID == "m3_begin_yes" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 5)
		coa2ScreenPlay:startMission(conversingPlayer, "imperial", 3)
	elseif screenID == "m3_active_abort" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 4)
		coa2ScreenPlay:cleanupMission(conversingPlayer, "imperial", 3)
	elseif screenID == "m3_active_restart" then
		coa2ScreenPlay:cleanupMission(conversingPlayer, "imperial", 3)
		coa2ScreenPlay:startMission(conversingPlayer, "imperial", 3)
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
