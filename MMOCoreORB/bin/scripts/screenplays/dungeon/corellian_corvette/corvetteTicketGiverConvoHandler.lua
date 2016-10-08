local ObjectManager = require("managers.object.object_manager")

CorvetteTicketGiverConvoHandler = conv_handler:new {
	ticketGiver = nil
}

function CorvetteTicketGiverConvoHandler:setTicketGiver(giver)
	self.ticketGiver = giver
end

function CorvetteTicketGiverConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local player = CreatureObject(pPlayer)
	local playerID = player:getObjectID()
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if screenID == "go_get_intel" then
		setQuestStatus(playerID .. ":activeCorvetteQuest", self.ticketGiver.giverName)
		setQuestStatus(playerID .. ":activeCorvetteStep", "1")
		self.ticketGiver:randomizeIntelLocs(pPlayer)
	elseif screenID == "has_intel" or screenID == "other_documents" then
		pConvScreen = self:handleScreenHasIntel(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "reset" or screenID == "reset2" or screenID == "reset3" then
		removeQuestStatus(playerID .. ":activeCorvetteQuest")
		removeQuestStatus(playerID .. ":activeCorvetteStep")
		removeQuestStatus(playerID .. ":corvetteIntelAcquired")
		removeQuestStatus(playerID .. ":corvetteIntelLocs")
		removeQuestStatus(playerID .. ":activeCorvetteQuestType")
		self.ticketGiver:removeDocuments(pPlayer)
	elseif  screenID == "bad_intel_1" then
		self.ticketGiver:removeIntel(pPlayer, 1)
		self.ticketGiver:giveCompensation(pPlayer)
	elseif  screenID == "bad_intel_2" then
		self.ticketGiver:removeIntel(pPlayer, 2)
		self.ticketGiver:giveCompensation(pPlayer)
	elseif  screenID == "good_intel" then
		removeQuestStatus(playerID .. ":corvetteIntelAcquired")
		removeQuestStatus(playerID .. ":corvetteIntelLocs")
		setQuestStatus(playerID .. ":activeCorvetteStep", "2")
		self.ticketGiver:removeIntel(pPlayer, 3)
		self.ticketGiver:giveTicket(pPlayer)
	elseif  screenID == "reward" then
		pConvScreen = self:handleScreenReward(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif screenID == "give_reward" then
		removeQuestStatus(playerID .. ":activeCorvetteQuest")
		removeQuestStatus(playerID .. ":activeCorvetteStep")
		removeQuestStatus(playerID .. ":activeCorvetteQuestType")
		self.ticketGiver:removeDocuments(pPlayer)
		self.ticketGiver:giveReward(PConversingPlayer)
	end
	return pConvScreen
end

function CorvetteTicketGiverConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
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

function CorvetteTicketGiverConvoHandler:handleScreenReward(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return pConvScreen
	end

	if SceneObject(pInventory):isContainerFullRecursive() then
		local text = clonedScreen:getOptionText(0)
		clonedScreen:removeAllOptions()
		clonedScreen:addOption(text, "cant_give_reward")
	end

	return pConvScreen
end

function CorvetteTicketGiverConvoHandler:handleScreenHasIntel(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return pConvScreen
	end

	local templates = self.ticketGiver.intelMap.itemTemplates
	local intel1 = getContainerObjectByTemplate(pInventory, templates[1], true)
	local intel2 = getContainerObjectByTemplate(pInventory, templates[2], true)
	local intel3 = getContainerObjectByTemplate(pInventory, templates[3], true)

	if intel1 ~= nil and intel2 ~= nil and intel3 ~= nil then
		return pConvScreen
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

	return pConvScreen
end
