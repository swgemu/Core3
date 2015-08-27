local ObjectManager = require("managers.object.object_manager")

rebelCommanderConvoHandler = Object:new {}

function rebelCommanderConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local playerID = SceneObject(pPlayer):getObjectID()
	local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))

	if TangibleObject(pPlayer):isImperial() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif state == 9 then
		return convoTemplate:getScreen("m4_finish")
	elseif state == 10 then
		if TangibleObject(pPlayer):isNeutral() then
			return convoTemplate:getScreen("m5_begin_undeclared")
		else
			return convoTemplate:getScreen("m5_begin")
		end
	elseif state == 11 then
		return convoTemplate:getScreen("m5_refused")
	elseif state == 12 then
		return convoTemplate:getScreen("m5_active")
	elseif state > 12 then
		return convoTemplate:getScreen("m5_finish")
	else
		return convoTemplate:getScreen("m4_finish_incomplete")
	end
end

function rebelCommanderConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local playerID = SceneObject(conversingPlayer):getObjectID()

	if screenID == "m4_finish" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 10)
		coa2ScreenPlay:finishMission(conversingPlayer, "rebel", 4)
	elseif screenID == "m5_begin_no" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 11)
	elseif screenID == "m5_begin_yes" or screenID == "m5_refused_yes" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 12)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 5)
	elseif screenID == "m5_active_abort" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 11)
		coa2ScreenPlay:cleanupMission(conversingPlayer, "rebel", 5)
	elseif screenID == "m5_active_restart" then
		coa2ScreenPlay:cleanupMission(conversingPlayer, "rebel", 5)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 5)
	elseif screenID == "m5_finish" then
		if readScreenPlayData(conversingPlayer, "rebel_coa2", "state") == "13" then
			writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 14)
			coa2ScreenPlay:finishMission(conversingPlayer, "rebel", 5)
		end
	end

	return conversationScreen
end

function rebelCommanderConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
