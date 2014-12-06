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
	elseif screenID == "authorization" then
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
	local rightFaction = self.ticketTaker:checkFaction(pConversingPlayer)

	clonedScreen:removeAllOptions()

	if activeStep == 2 then
		if player:getGroupSize() > 10 and rightFaction == false then
			clonedScreen:addOption(self.ticketTaker.helpMeString, "wrong_faction_too_many")
		elseif player:getGroupSize() > 10 then
			clonedScreen:addOption(self.ticketTaker.helpMeString, "too_many")
		elseif rightFaction == false then
			clonedScreen:addOption(self.ticketTaker.helpMeString, "wrong_faction")
		else
			clonedScreen:addOption(self.ticketTaker.helpMeString, "continue")
		end
	end

	clonedScreen:addOption(self.ticketTaker.goodbyeString, "goodbye")

	return pConversationScreen
end

function CorvetteTicketTakerConvoHandler:handleScreenContinue(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local player = CreatureObject(pConversingPlayer)
	local activeStep = tonumber(getQuestStatus(player:getObjectID() .. ":activeCorvetteStep"))
	local rightFaction = self.ticketTaker:checkFaction(pConversingPlayer)

	clonedScreen:removeAllOptions()

	if activeStep == 2 then
		if player:getGroupSize() > 10 and rightFaction == false then
			clonedScreen:addOption(self.ticketTaker.aboutMissionString, "mission_wrong_faction_too_many")
		elseif player:getGroupSize() > 10 then
			clonedScreen:addOption(self.ticketTaker.aboutMissionString, "mission_too_many")
		elseif rightFaction == false then
			clonedScreen:addOption(self.ticketTaker.aboutMissionString, "mission_wrong_faction")
		else
			clonedScreen:addOption(self.ticketTaker.aboutMissionString, "mission")
		end
	end

	clonedScreen:addOption(self.ticketTaker.nevermindString, "goodbye2")

	return pConversationScreen
end
