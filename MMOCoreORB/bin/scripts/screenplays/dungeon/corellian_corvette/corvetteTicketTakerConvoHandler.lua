local ObjectManager = require("managers.object.object_manager")

CorvetteTicketTakerConvoHandler = conv_handler:new {
	ticketTaker = nil
}

function CorvetteTicketTakerConvoHandler:setTicketTaker(taker)
	self.ticketTaker = taker
end

function CorvetteTicketTakerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local playerID = SceneObject(pPlayer):getObjectID()
	local activeStep = tonumber(getQuestStatus(playerID .. ":activeCorvetteStep"))
	if (screenID == "start") then
		if (activeStep == 2) then
			if (self.ticketTaker.faction == 0) then
				if (CreatureObject(pPlayer):getGroupSize() > 10) then
					clonedConversation:addOption(self.ticketTaker.helpMeString, "too_many")
				else
					clonedConversation:addOption(self.ticketTaker.helpMeString, "continue")
				end
			else
				local rightFaction = self.ticketTaker:checkFaction(pPlayer)
				if (CreatureObject(pPlayer):getGroupSize() > 10) and (rightFaction == false) then
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission_wrong_faction_too_many")
				elseif (CreatureObject(pPlayer):getGroupSize() > 10) then
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission_too_many")
				elseif (rightFaction == false) then
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission_wrong_faction")
				else
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission")
				end
			end
		end
		clonedConversation:addOption(self.ticketTaker.goodbyeString, "goodbye")
	elseif (screenID == "continue") then
		if (activeStep == 2) then
			if (self.ticketTaker.faction == FACTIONNEUTRAL) then
				if (CreatureObject(pPlayer):getGroupSize() > 10) then
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission_too_many")
				else
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission")
				end
			else
				local rightFaction = self.ticketTaker:checkFaction(pPlayer)
				if (CreatureObject(pPlayer):getGroupSize() > 10) and (rightFaction == false) then
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission_wrong_faction_too_many")
				elseif (CreatureObject(pPlayer):getGroupSize() > 10) then
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission_too_many")
				elseif (rightFaction == false) then
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission_wrong_faction")
				else
					clonedConversation:addOption(self.ticketTaker.aboutMissionString, "mission")
				end
			end
		end
		clonedConversation:addOption(self.ticketTaker.nevermindString, "goodbye2")
	elseif (screenID == "authorization") then
		self.ticketTaker:validateTicket(pPlayer)
	end
	return pConvScreen
end

function CorvetteTicketTakerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	return convoTemplate:getScreen("start")
end
