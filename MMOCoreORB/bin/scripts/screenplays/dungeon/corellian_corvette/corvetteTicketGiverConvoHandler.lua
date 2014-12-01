local ObjectManager = require("managers.object.object_manager")

CorvetteTicketGiverConvoHandler = Object:new {
	ticketGiver = nil
}

function CorvetteTicketGiverConvoHandler:setTicketGiver(giver)
	self.ticketGiver = giver
end

function CorvetteTicketGiverConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local player = CreatureObject(pConversingPlayer)
	local playerID = player:getObjectID()
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if screenID == "go_get_intel" then
		setQuestStatus(playerID .. ":activeCorvetteQuest", self.ticketGiver.giverName)
		setQuestStatus(playerID .. ":activeCorvetteStep", "1")
		self.ticketGiver:randomizeIntelLocs(pConversingPlayer)
	elseif screenID == "has_intel" or screenID == "other_documents" then
		pConversationScreen = self:handleScreenHasIntel(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "reset" or screenID == "reset2" or screenID == "reset3" then
		removeQuestStatus(playerID .. ":activeCorvetteQuest")
		removeQuestStatus(playerID .. ":activeCorvetteStep")
		removeQuestStatus(playerID .. ":corvetteIntelAcquired")
		removeQuestStatus(playerID .. ":corvetteIntelLocs")
		removeQuestStatus(playerID .. ":activeCorvetteQuestType")
		self.ticketGiver:removeDocuments(pConversingPlayer)
	elseif  screenID == "bad_intel_1" then
		self.ticketGiver:removeIntel(pConversingPlayer, 1)
		self.ticketGiver:giveCompensation(pConversingPlayer)
	elseif  screenID == "bad_intel_2" then
		self.ticketGiver:removeIntel(pConversingPlayer, 2)
		self.ticketGiver:giveCompensation(pConversingPlayer)
	elseif  screenID == "good_intel" then
		removeQuestStatus(playerID .. ":corvetteIntelAcquired")
		removeQuestStatus(playerID .. ":corvetteIntelLocs")
		setQuestStatus(playerID .. ":activeCorvetteStep", "2")
		self.ticketGiver:removeIntel(pConversingPlayer, 3)
		self.ticketGiver:giveTicket(pConversingPlayer)
	elseif  screenID == "reward" then
		pConversationScreen = self:handleScreenReward(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "give_reward" then
		removeQuestStatus(playerID .. ":activeCorvetteQuest")
		removeQuestStatus(playerID .. ":activeCorvetteStep")
		removeQuestStatus(playerID .. ":activeCorvetteQuestType")
		self.ticketGiver:removeDocuments(pConversingPlayer)
		self.ticketGiver:giveReward(PConversingPlayer)
	end
	return pConversationScreen
end

function CorvetteTicketGiverConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local player = CreatureObject(pPlayer)
	local activeQuest = getQuestStatus(player:getObjectID() .. ":activeCorvetteQuest")
	local activeStep = tonumber(getQuestStatus(player:getObjectID() .. ":activeCorvetteStep"))

	if (ThemeParkLogic:hasEliteCombatProfession(pPlayer) == false) then
		return convoTemplate:getScreen("no_business")
	elseif (activeQuest ~= nil and activeQuest ~= self.ticketGiver.giverName) then
		return convoTemplate:getScreen("already_busy")
	elseif (activeQuest == nil) then
		return convoTemplate:getScreen("start")
	elseif (activeStep == 1 and self.ticketGiver:hasIntel(pPlayer) == false) then
		return convoTemplate:getScreen("back_already")
	elseif (activeStep == 1) then
		return convoTemplate:getScreen("has_intel")
	elseif (activeStep == 2) then
		return convoTemplate:getScreen("still_here")
	elseif (activeStep == 3) then
		return convoTemplate:getScreen("reward")
	end
end

function CorvetteTicketGiverConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function CorvetteTicketGiverConvoHandler:handleScreenReward(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local pInventory = CreatureObject(pConversingPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return pConversationScreen
	end

	if SceneObject(pInventory):hasFullContainerObjects() then
		local text = clonedScreen:getOptionText(0)
		clonedScreen:removeAllOptions()
		clonedScreen:addOption(text, "cant_give_reward")
	end

	return pConversationScreen
end

function CorvetteTicketGiverConvoHandler:handleScreenHasIntel(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local pInventory = CreatureObject(pConversingPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return pConversationScreen
	end

	local templates = self.ticketGiver.intelMap.itemTemplates
	local intel1 = getContainerObjectByTemplate(pInventory, templates[1], true)
	local intel2 = getContainerObjectByTemplate(pInventory, templates[2], true)
	local intel3 = getContainerObjectByTemplate(pInventory, templates[3], true)

	if intel1 ~= nil and intel2 ~= nil and intel3 ~= nil then
		return pConversationScreen
	end

	local text1, text2, text3, link1, link2, link3

	if intel1 ~= nil then
		text1 = clonedScreen:getOptionText(0)
		link1 = clonedScreen:getOptionLink(0)
	end
	if intel2 ~= nil then
		text2 = clonedScreen:getOptionText(1)
		link2 = clonedScreen:getOptionLink(1)
	end
	if intel3 ~= nil then
		text3 = clonedScreen:getOptionText(2)
		link3 = clonedScreen:getOptionLink(2)
	end

	clonedScreen:removeAllOptions()

	if intel1 ~= nil then
		clonedScreen:addOption(text1, link1)
	end
	if intel2 ~= nil then
		clonedScreen:addOption(text2, link2)
	end
	if intel3 ~= nil then
		clonedScreen:addOption(text3, link3)
	end

	return pConversationScreen
end
