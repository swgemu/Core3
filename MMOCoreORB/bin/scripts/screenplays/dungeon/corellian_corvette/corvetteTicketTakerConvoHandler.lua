local ObjectManager = require("managers.object.object_manager")

CorvetteTicketTakerConvoHandler = Object:new {
	ticketTaker = nil
}

function CorvetteTicketTakerConvoHandler:setTicketTaker(taker)
	self.ticketTaker = taker
end

function CorvetteTicketTakerConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local player = CreatureObject(pConversingPlayer)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if screenID == "start" then
		pConversationScreen = self:handleScreenStart(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "continue" then
		pConversationScreen = self:handleScreenContinue(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "not_so_fast" then
		self.ticketTaker:validateTicket(pConversingPlayer)
	end
	return pConversationScreen
end

function CorvetteTicketTakerConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return convoTemplate:getScreen("start")

end

function CorvetteTicketTakerConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function CorvetteTicketTakerConvoHandler:handleScreenStart(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local player = CreatureObject(pConversingPlayer)
	local activeStep = tonumber(getQuestStatus(player:getObjectID() .. ":activeCorvetteStep"))

	clonedScreen:removeAllOptions()
	clonedScreen:addOption(self.ticketTaker.sorryString, "sorry")

	if activeStep == 2 then
		if player:getGroupSize() > 10 then
			clonedScreen:addOption(self.ticketTaker.helpMeString, "too_many_to_help")
		else
			clonedScreen:addOption(self.ticketTaker.helpMeString, "continue")
		end
	end

	return pConversationScreen
end

function CorvetteTicketTakerConvoHandler:handleScreenContinue(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local player = CreatureObject(pConversingPlayer)
	local activeStep = tonumber(getQuestStatus(player:getObjectID() .. ":activeCorvetteStep"))

	clonedScreen:removeAllOptions()
	clonedScreen:addOption(self.ticketTaker.nevermindString, "in_my_way")

	if activeStep == 2 then
		if player:getGroupSize() > 10 then
			clonedScreen:addOption(self.ticketTaker.aboutMissionString, "mission_too_many")
		else
			clonedScreen:addOption(self.ticketTaker.aboutMissionString, "mission")
		end
	end

	return pConversationScreen
end
