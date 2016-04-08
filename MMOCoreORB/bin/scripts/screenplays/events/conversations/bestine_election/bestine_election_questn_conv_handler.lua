local ObjectManager = require("managers.object.object_manager")

BestineElectionQuestnConvoHandler = Object:new {}

local CANTINA = "object/tangible/loot/quest/victor_questn_dseal.iff"
local CAPITOL = "object/tangible/loot/quest/victor_questn_hlist.iff"
local UNIVERSITY = "object/tangible/loot/quest/sean_questn_gpapers.iff"

function BestineElectionQuestnConvoHandler:alreadyHasEvidence(pPlayer, quest)
	if (pPlayer == nil or quest == "") then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		if quest == "cantina" then
			return getContainerObjectByTemplate(pInventory, CANTINA , true) ~= nil
		elseif quest == "capitol" then
			return getContainerObjectByTemplate(pInventory, CAPITOL , true) ~= nil
		elseif quest == "university" then
			return getContainerObjectByTemplate(pInventory, UNIVERSITY , true) ~= nil
		end
	end
	return false
end

function BestineElectionQuestnConvoHandler:giveQuestnItem(pPlayer,quest)
	if (pPlayer == nil or quest == "") then
		return
	end

	local questnItem = ""
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		if quest == "university" then
			questnItem = UNIVERSITY
		elseif quest == "capitol" then
			questnItem = CAPITOL
		elseif quest == "cantina" then
			questnItem = CANTINA
		end
		local pItem = giveItem(pInventory, questnItem, -1)
		if (pItem == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item."..quest)
			return
		end
	end
	local playerID = CreatureObject(pPlayer):getObjectID()
	deleteData(playerID..":bestine_election:"..quest.."_noroom")
end

function BestineElectionQuestnConvoHandler:getQuestID(pNpc)
	if (pNpc == nil) then
		return ""
	end

	local questID = string.sub(SceneObject(pNpc):getTemplateObjectPath(),0,-5)
	local start = 0
	local splitStart,splitEnd = string.find(questID, "_", start)
	while splitStart do
		start = splitEnd+1
		splitStart, splitEnd = string.find(questID, "_", start)
	end
	return string.sub(questID,start)
end

function BestineElectionQuestnConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local objectName = SceneObject(pNpc):getTemplateObjectPath()
	local questID = self:getQuestID(pNpc)

	if BestineElectionScreenPlay:getCurrentPhase() == 2 then
		return convoTemplate:getScreen("no_election")
	elseif self:alreadyHasEvidence(pPlayer,questID) then
		return convoTemplate:getScreen("already_has_evidence")
	elseif BestineElectionScreenPlay:noroomReturned(pPlayer,questID) then
		return convoTemplate:getScreen("noroom_returned")
	elseif (string.find(objectName,"victor") ~= nil and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Sean")) or (string.find(objectName,"sean") ~= nil and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Victor")) then
		return convoTemplate:getScreen("convo_start")
	end
	return convoTemplate:getScreen("no_business")
end

function BestineElectionQuestnConvoHandler:hasEnoughMoney(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	if(CreatureObject(pPlayer):getCashCredits() >= 200) then
		return true
	end
	return false
end

function BestineElectionQuestnConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	
	local questID = self:getQuestID(conversingNPC)
	
	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
	local playerID = player:getObjectID()
	if (questID == "capitol") then
		if (screenID == "convo_start2") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_b9b27823","no_room")
			else
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_b9b27823","give_item")
			end
		elseif (screenID == "give_item") then
			self:giveQuestnItem(conversingPlayer,questID)
		elseif (screenID == "no_room") then
			writeData(playerID..":bestine_election:"..questID.."_noroom",electionNum)
		elseif (screenID == "noroom_returned") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_90ec63e0","noroom_returned_noroom")
			else
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_90ec63e0","noroom_returned_giveitem")
			end
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_da9a29e9","noroom_returned_noroom2")
		end
	elseif (questID == "cantina") then
		if (screenID == "convo_start") then
			if self:hasEnoughMoney(conversingPlayer) then
				if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
					clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991","no_room")
				else
					clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991","give_item")
				end
			else
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_19d90991","no_money")
			end
		elseif (screenID == "give_item") then
			player:subtractCashCredits(200)
			player:sendSystemMessage("You successfully make a payment of 200 credits.")
			self:giveQuestnItem(conversingPlayer,questID)
		elseif (screenID == "no_room") then
			writeData(playerID..":bestine_election:cantina_noroom",electionNum)
		elseif (screenID == "noroom_returned") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_90ec63e0","noroom_returned_noroom")
			else
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_90ec63e0","give_item")
			end
			clonedConversation:addOption("@conversation/victor_questn_cantina:s_62bf3631","noroom_returned_noroom2")
		end
	elseif (questID == "university") then
		if (screenID == "convo_start2") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questn_university:s_5ec23736","no_room")
			else
				clonedConversation:addOption("@conversation/sean_questn_university:s_5ec23736","give_item")
			end
		elseif (screenID == "give_item") then
			self:giveQuestnItem(conversingPlayer,questID)
		elseif (screenID == "no_room") then
			writeData(playerID..":bestine_election:sean_university_noroom",electionNum)
		elseif (screenID == "noroom_returned") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f","noroom_returned_noroom")
			else
				clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f","give_item")
			end
			clonedConversation:addOption("@conversation/sean_questn_university:s_7291fe2e","noroom_returned_noroom2")
		end
	end
	
	return conversationScreen
	end)
end

function BestineElectionQuestnConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
