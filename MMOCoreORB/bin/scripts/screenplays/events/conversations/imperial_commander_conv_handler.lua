local ObjectManager = require("managers.object.object_manager")

imperialCommanderConvoHandler = Object:new {}

function imperialCommanderConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local state = tonumber(readScreenPlayData(pPlayer, "imperial_coa2", "state"))

	if TangibleObject(pPlayer):isRebel() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif state == nil or state < 5 then
		return convoTemplate:getScreen("m4_finish_incomplete")
	elseif state == 5 then
		return convoTemplate:getScreen("m4_finish")
	elseif state == 6 then
		if TangibleObject(pPlayer):isNeutral() then
			return convoTemplate:getScreen("m5_begin_undeclared")
		else
			return convoTemplate:getScreen("m5_begin_declared")
		end
	elseif state == 7 then
		return convoTemplate:getScreen("m5_active")
	elseif state > 7 then
		return convoTemplate:getScreen("m5_finish")
	end

	return convoTemplate:getScreen("m4_finish_incomplete")
end

function imperialCommanderConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if screenID == "m4_finish" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 6)
		Coa2Screenplay:finishMission(conversingPlayer, "imperial", 4)
	elseif screenID == "m5_begin_yes" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 7)
		Coa2Screenplay:startMission(conversingPlayer, "imperial", 5)
	elseif screenID == "m5_active_abort" then
		writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 6)
		Coa2Screenplay:cleanupMission(conversingPlayer, "imperial", 5)
	elseif screenID == "m5_active_restart" then
		Coa2Screenplay:cleanupMission(conversingPlayer, "imperial", 5)
		Coa2Screenplay:startMission(conversingPlayer, "imperial", 5)
	elseif screenID == "m5_finish" then
		if readScreenPlayData(conversingPlayer, "imperial_coa2", "state") == "8" then
			writeScreenPlayData(conversingPlayer, "imperial_coa2", "state", 9)
			Coa2Screenplay:finishMission(conversingPlayer, "imperial", 5)
		end
	end

	return conversationScreen
end

function imperialCommanderConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
