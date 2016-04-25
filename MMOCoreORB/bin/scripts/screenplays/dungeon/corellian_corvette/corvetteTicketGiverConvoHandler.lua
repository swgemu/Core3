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
	elseif screenID == "back_already" then
		pConversationScreen = self:handleScreenBackAlready(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "has_intel" or  screenID == "other_documents" then
		 pConversationScreen = self:handleScreenHasIntel(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "decline_quest_reset2" or screenID == "back_already_reset" or screenID == "decline_quest_reset" then
		removeQuestStatus(playerID .. ":activeCorvetteQuest")
		removeQuestStatus(playerID .. ":activeCorvetteStep")
		removeQuestStatus(playerID .. ":corvetteIntelAcquired")
		removeQuestStatus(playerID .. ":corvetteIntelLocs")
		removeQuestStatus(playerID .. ":activeCorvetteQuestType")
		removeQuestStatus(playerID .. ":heardLocation1")
		removeQuestStatus(playerID .. ":heardLocation2")
		removeQuestStatus(playerID .. ":heardLocation3")
		self.ticketGiver:removeDocuments(pConversingPlayer)
	elseif screenID == "which_planet" then
		removeQuestStatus(playerID .. ":heardLocation1")
		removeQuestStatus(playerID .. ":heardLocation2")
		removeQuestStatus(playerID .. ":heardLocation3")
		pConversationScreen = self:handleScreenHeardLocations(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "first_location" then
		setQuestStatus(playerID .. ":heardLocation1",1)
		pConversationScreen = self:handleScreenHeardLocations(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "second_location" then
		setQuestStatus(playerID .. ":heardLocation2",1)
		pConversationScreen = self:handleScreenHeardLocations(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "third_location" then
		setQuestStatus(playerID .. ":heardLocation3",1)
		pConversationScreen = self:handleScreenHeardLocations(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif screenID == "bad_intel_1" then
		self.ticketGiver:removeIntel(pConversingPlayer, 1)
		self.ticketGiver:giveCompensation(pConversingPlayer)
		pConversationScreen = self:handleScreenHasIntel(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif  screenID == "bad_intel_2" then
		self.ticketGiver:removeIntel(pConversingPlayer, 2)
		self.ticketGiver:giveCompensation(pConversingPlayer)
		pConversationScreen = self:handleScreenHasIntel(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif  screenID == "good_intel" then
		removeQuestStatus(playerID .. ":corvetteIntelAcquired")
		removeQuestStatus(playerID .. ":corvetteIntelLocs")
		removeQuestStatus(playerID .. ":heardLocation1")
		removeQuestStatus(playerID .. ":heardLocation2")
		removeQuestStatus(playerID .. ":heardLocation3")
		setQuestStatus(playerID .. ":activeCorvetteStep", "2")
		self.ticketGiver:removeIntel(pConversingPlayer, 3)
		self.ticketGiver:giveTicket(pConversingPlayer)
		pConversationScreen = self:handleScreenGoodIntel(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	elseif  screenID == "earned_reward" then
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
		return convoTemplate:getScreen("quest_start")
	elseif (activeStep == 1) then
		return convoTemplate:getScreen("back_already")
	elseif (activeStep == 2) then
		return convoTemplate:getScreen("still_here")
	elseif (activeStep == 3) then
		return convoTemplate:getScreen("earned_reward")
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

function CorvetteTicketGiverConvoHandler:hasIntel(pPlayer)
local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return false
	end
	
	local templates = self.ticketGiver.intelMap.itemTemplates
	local intel1 = getContainerObjectByTemplate(pInventory, templates[1], true)
	local intel2 = getContainerObjectByTemplate(pInventory, templates[2], true)
	local intel3 = getContainerObjectByTemplate(pInventory, templates[3], true)

	if intel1 ~= nil and intel2 ~= nil and intel3 ~= nil then
		return true
	end
	return false
end

function CorvetteTicketGiverConvoHandler:handleScreenReward(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)

	local pInventory = CreatureObject(pConversingPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return pConversationScreen
	end

	if SceneObject(pInventory):isContainerFullRecursive() then
		local text = clonedScreen:getOptionText(0)
		clonedScreen:removeAllOptions()
		clonedScreen:addOption(text, "cant_give_reward")
	end

	return pConversationScreen
end

function CorvetteTicketGiverConvoHandler:handleScreenHeardLocations(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local player = CreatureObject(pConversingPlayer)
	local playerID = player:getObjectID()
	local screen = LuaConversationScreen(pConversationScreen)
	pConversationScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConversationScreen)
	
	local heard1 = tonumber(getQuestStatus(player:getObjectID() .. ":heardLocation1"))
	local heard2 = tonumber(getQuestStatus(player:getObjectID() .. ":heardLocation2"))
	local heard3 = tonumber(getQuestStatus(player:getObjectID() .. ":heardLocation3"))

	
	local optionTable =  {}
	local optionText, optionLink
	for i = 0,clonedScreen:getOptionCount(pConversationScreen)-1, 1 do
		optionText = clonedScreen:getOptionText(i)
		optionLink = clonedScreen:getOptionLink(i)
		table.insert(optionTable,{optionText = optionText, optionLink = optionLink })
		--print("{"..optionText..","..optionLink.."} "..i)
	end

	clonedScreen:removeAllOptions()
	if heard1 == nil then
		clonedScreen:addOption(optionTable[1].optionText,optionTable[1].optionLink)
	end
	if heard2 == nil then
		clonedScreen:addOption(optionTable[2].optionText,optionTable[2].optionLink)
	end
	if heard3 == nil then
		clonedScreen:addOption(optionTable[3].optionText,optionTable[3].optionLink)
	end
	if optionTable[4] ~= nil then
			clonedScreen:addOption(optionTable[4].optionText,optionTable[4].optionLink)
	end
	if optionTable[5] ~= nil then 
		clonedScreen:addOption(optionTable[5].optionText,optionTable[5].optionLink)
	end
	return pConversationScreen
end


function CorvetteTicketGiverConvoHandler:handleScreenBackAlready(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
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

	local optionTable =  {}
	local optionLink, optionText
	for i = 0,clonedScreen:getOptionCount(pConversationScreen)-1, 1 do
		optionText = clonedScreen:getOptionText(i)
		optionLink = clonedScreen:getOptionLink(i)
		table.insert(optionTable,{optionText = optionText, optionLink = optionLink })
		--print("{"..optionText..","..optionLink.."} "..i)
	end
	clonedScreen:removeAllOptions()

	if intel1 ~= nil or intel2 ~= nil or intel3 ~= nil then
		clonedScreen:addOption(optionTable[1].optionText,optionTable[1].optionLink)
	end
	
	if optionTable[2] ~= nil then
		clonedScreen:addOption(optionTable[2].optionText,optionTable[2].optionLink)
	end
	
	if optionTable[3] ~= nil then
		clonedScreen:addOption(optionTable[3].optionText,optionTable[3].optionLink)
	end
	if self.ticketGiver:hasTicket(pConversingPlayer) then 
		if optionTable[4] ~= nil then
			clonedScreen:addOption(optionTable[4].optionText,optionTable[4].optionLink)
		end
	elseif intel1 == nil and intel2 == nil and intel3 == nil then
		if optionTable[5] ~= nil then
			clonedScreen:addOption(optionTable[5].optionText,optionTable[5].optionLink)
		end
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


	local optionTable =  {}
	local optionLink, optionText
	for i = 0,clonedScreen:getOptionCount(pConversationScreen)-1, 1 do
		optionText = clonedScreen:getOptionText(i)
		optionLink = clonedScreen:getOptionLink(i)
		table.insert(optionTable,{optionText = optionText, optionLink = optionLink })
		--print("{"..optionText..","..optionLink.."} "..i)
	end
	
	clonedScreen:removeAllOptions()
	if intel1 ~= nil then 
		clonedScreen:addOption(optionTable[1].optionText,optionTable[1].optionLink)
	end
	if intel2 ~= nil then 
		clonedScreen:addOption(optionTable[2].optionText,optionTable[2].optionLink)
	end
	if intel3 ~= nil then 
		clonedScreen:addOption(optionTable[3].optionText,optionTable[3].optionLink)
	end
	
	if self.ticketGiver:hasTicket(pConversingPlayer) then 
		if optionTable[4] ~= nil then
			clonedScreen:addOption(optionTable[4].optionText,optionTable[4].optionLink)
		end
	elseif optionTable[5] ~= nil then
			clonedScreen:addOption(optionTable[5].optionText,optionTable[5].optionLink)
	end
	
	return pConversationScreen
end

function CorvetteTicketGiverConvoHandler:handleScreenGoodIntel(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
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


	local optionTable =  {}
	local optionLink, optionText
	for i = 0,clonedScreen:getOptionCount(pConversationScreen)-1, 1 do
		optionText = clonedScreen:getOptionText(i)
		optionLink = clonedScreen:getOptionLink(i)
		table.insert(optionTable,{optionText = optionText, optionLink = optionLink })
		--print("{"..optionText..","..optionLink.."} "..i)
	end
	
	clonedScreen:removeAllOptions()
	if self.ticketGiver:hasTicket(pConversingPlayer) then 
		if optionTable[1] ~= nil then
			clonedScreen:addOption(optionTable[1].optionText,optionTable[1].optionLink)
		end
	elseif intel1 ~= nil or intel2 ~= nil or intel3 ~= nil then
		if optionTable[2] ~= nil then
			clonedScreen:addOption(optionTable[2].optionText,optionTable[2].optionLink)
		end
	end
	
	return pConversationScreen
end
