local ObjectManager = require("managers.object.object_manager")

rebelCoordinatorConvoHandler = Object:new {}

function rebelCoordinatorConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local state = tonumber(readScreenPlayData(pPlayer, "rebel_coa2", "state"))

	if TangibleObject(pPlayer):isImperial() then
		return convoTemplate:getScreen("begin_wrong_faction")
	elseif state == 1 then
		return convoTemplate:getScreen("m1_refused")
	elseif state == 2 then
		return convoTemplate:getScreen("m1_active")
	elseif state == 3 then
		if coa2ScreenPlay:hasDecodedDisk(pPlayer) then
			return convoTemplate:getScreen("m1_finish_decoded")
		elseif coa2ScreenPlay:hasEncodedDisk(pPlayer) then
			return convoTemplate:getScreen("m1_finish_encoded")
		else
			return convoTemplate:getScreen("m1_active")
		end
	elseif state == 4 then
		if coa2ScreenPlay:hasDecodedDisk(pPlayer) then
			return convoTemplate:getScreen("m2_begin")
		else
			return convoTemplate:getScreen("m2_begin_encoded")
		end
	elseif state == 5 then
		return convoTemplate:getScreen("m2_refused")
	elseif state == 6 then
		return convoTemplate:getScreen("m2_active")
	elseif state == 7 then
		return convoTemplate:getScreen("m2_finish")
	elseif state == 8 then
		return convoTemplate:getScreen("m3_begin")
	elseif state == 9 then
		return convoTemplate:getScreen("m3_active")
	elseif state > 9 then
		return convoTemplate:getScreen("m3_finish")
	else
		return convoTemplate:getScreen("m1_begin")
	end
end

function rebelCoordinatorConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if screenID == "m1_begin_no" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 1)
	elseif screenID == "m1_begin_yes" or screenID == "m1_refused_yes" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 2)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 1)
	elseif screenID == "m1_active_abort" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 1)
		coa2ScreenPlay:cleanupMission(conversingPlayer, "rebel", 1)
	elseif screenID == "m1_active_restart" then
		coa2ScreenPlay:cleanupMission(conversingPlayer, "rebel", 1)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 1)
	elseif screenID == "m1_finish_encoded" or screenID == "m1_finish_decoded" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 4)
		coa2ScreenPlay:finishMission(conversingPlayer, "rebel", 1)
	elseif screenID == "m2_begin_no" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 5)
	elseif screenID == "m2_begin_yes" or screenID == "m2_refused_yes" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 6)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 2)
	elseif screenID == "m2_active_abort" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 5)
		coa2ScreenPlay:cleanupMission(conversingPlayer, "rebel", 2)
	elseif screenID == "m2_active_restart" then
		coa2ScreenPlay:cleanupMission(conversingPlayer, "rebel", 2)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 2)
	elseif screenID == "m2_finish_no" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 8)
		coa2ScreenPlay:finishMission(conversingPlayer, "rebel", 2)
	elseif screenID == "m2_finish_yes" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 9)
		coa2ScreenPlay:finishMission(conversingPlayer, "rebel", 2)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 3)
	elseif screenID == "m3_begin_yes" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 9)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 3)
	elseif screenID == "m3_active_abort" then
		writeScreenPlayData(conversingPlayer, "rebel_coa2", "state", 8)
		coa2ScreenPlay:cleanupMission(conversingPlayer, "rebel", 3)
	elseif screenID == "m3_active_restart" then
		coa2ScreenPlay:cleanupMission(conversingPlayer, "rebel", 3)
		coa2ScreenPlay:startMission(conversingPlayer, "rebel", 3)
	end

	return conversationScreen
end

function rebelCoordinatorConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
