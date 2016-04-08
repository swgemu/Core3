local ObjectManager = require("managers.object.object_manager")

BestineElectionQuestnConvoHandler = Object:new {
	themePark = nil
}

local CANTINA = "object/tangible/loot/quest/victor_questn_dseal.iff"
local CAPITOL = "object/tangible/loot/quest/victor_questn_hlist.iff"
local UNIVERSITY = "object/tangible/loot/quest/sean_questn_gpapers.iff"

function BestineElectionQuestnConvoHandler:alreadyHasEvidence(pPlayer, quest)
	if (pPlayer == nil or quest == nil) then
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


function BestineElectionQuestnConvoHandler:hasNoRoomVar(pPlayer, quest)
	if (pPlayer == nil or quest == nil) then
		return false
	end
	
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = readData(playerID..":bestine_election:"..quest.."_noroom")
	return (playerCampaign >= electionNum)
end

function BestineElectionQuestnConvoHandler:giveQuestnItem(pPlayer,quest)
	if (pPlayer == nil or quest == nil) then
		return
	end
	
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		if quest == "cantina" then
			local pItem = giveItem(pInventory,CANTINA, -1)
			if (pItem == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				return
			end
		elseif quest == "capitol" then
			local pItem = giveItem(pInventory,CAPITOL, -1)
			if (pItem == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				return
			end
		elseif quest == "university" then
			local pItem = giveItem(pInventory,UNIVERSITY, -1)
			if (pItem == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				return
			end
		end
		
		local playerID = CreatureObject(pPlayer):getObjectID()
		deleteData(playerID..":bestine_election:"..quest.."_noroom")
	end
	return
end

function BestineElectionQuestnConvoHandler:getQuestID(pNpc)
	if (pNpc == nil) then
		return
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
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local objectName = SceneObject(pNpc):getTemplateObjectPath()
	local questID = self:getQuestID(pNpc)
	
	if BestineElectionScreenPlay:getCurrentPhase() == 2 then
		return convoTemplate:getScreen("no_election")
	end
	
	if self:alreadyHasEvidence(pPlayer,questID) then
		return convoTemplate:getScreen("already_has_evidence")
	end
	
	if (string.find(SceneObject(pNpc):getTemplateObjectPath(), "victor") ~= nil and seanTrenwellConvoHandler:seanNegQuest(pPlayer))
	or (string.find(SceneObject(pNpc):getTemplateObjectPath(), "sean") ~= nil and victorVisalisConvoHandler:victorNegQuest(pPlayer)) then
		return convoTemplate:getScreen("convo_start")
	end

	if self:alreadyHasEvidence(pPlayer,questID) then
		return convoTemplate:getScreen("already_has_evidence")
	end
	
	if self:hasNoRoomVar(pPlayer,questID) then
			return convoTemplate:getScreen("noroom_returned")
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
	local playerID = CreatureObject(conversingPlayer):getObjectID()
	local questID = self:getQuestID(conversingNPC)

	if (questID == "capitol") then
		if (screenID == "convo_start2") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_b9b27823","no_room")
			else
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_b9b27823","give_item") 
			end	
		elseif (screenID == "give_item") then
			self:giveQuestnItem(conversingPlayer,questID)
			deleteData(playerID..":bestine_election:capitol_noroom")
		elseif (screenID == "no_room") then
			writeData(playerID..":bestine_election:capitol_noroom",electionNum)
		elseif (screenID == "noroom_returned") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_da9a29e9","noroom_returned_noroom") 
			else
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_90ec63e0","noroom_returned_giveitem") --Yes, I do.
			end
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_da9a29e9","noroom_returned_fullinv") -- No, not yet.
		end
	elseif (questID == "cantina") then
		if (screenID == "convo_start") then
			if self:hasEnoughMoney(conversingPlayer) then
				if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
					clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991","no_room") --Hmm. Here you go.
				else
					clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991","give_item") --Hmm. Here you go.
				end
			else
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_19d90991","no_money") -- I don't have that kind of money.
			end
		elseif (screenID == "give_item") then
			CreatureObject(conversingPlayer):subtractCashCredits(200)
			CreatureObject(conversingPlayer):sendSystemMessage("You successfully make a payment of 200 credits.")
			self:giveQuestnItem(conversingPlayer,questID)
			deleteData(playerID..":bestine_election:cantina_noroom")
		elseif (screenID == "no_room") then
			writeData(playerID..":bestine_election:cantina_noroom",electionNum)
		elseif (screenID == "noroom_returned") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_62bf3631","noroom_returned_noroom") --No, I haven't made room yet.
			else
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_90ec63e0","give_item") --Yes, I do.
			end
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
			deleteData(playerID..":bestine_election:university_noroom")
		elseif (screenID == "no_room") then
			writeData(playerID..":bestine_election:sean_university_noroom",electionNum)
		elseif (screenID == "noroom_returned") then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f","noroom_returned_noroom")
			else
				clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f","give_item")
			end
			clonedConversation:addOption("@conversation/sean_questn_university:s_7291fe2e","havent_made_room")
		end
	end

	return conversationScreen
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
