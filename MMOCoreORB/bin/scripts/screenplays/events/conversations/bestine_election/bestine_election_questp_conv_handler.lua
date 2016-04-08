local ObjectManager = require("managers.object.object_manager")

BestineElectionQuestpConvoHandler = Object:new {
		themePark = nil
}

local HOUSE = "object/tangible/loot/quest/sean_questp_htestimony.iff"
local MARKET = "object/tangible/loot/quest/sean_questp_mdisk.iff"
local SLUMS = "object/tangible/loot/quest/victor_questp_testimony.iff"
local HOSPITAL = "object/tangible/loot/quest/victor_questp_receipt.iff"



function BestineElectionQuestpConvoHandler:alreadyHasEvidence(pPlayer, quest)
	if (pPlayer == nil or quest == nil) then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		if quest == "slums" then
			return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_testimony.iff" , true) ~= nil
		elseif quest == "hospital" then
			return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_receipt.iff" , true) ~= nil
		elseif quest == "market" then
			return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_mdisk.iff" , true) ~= nil
		elseif quest == "house" then
			return getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questp_htestimony.iff" , true) ~= nil
		end
	end
	return false
end

function BestineElectionQuestpConvoHandler:hasNoRoom(pPlayer,quest)
	if (pPlayer == nil or quest == nil) then
		return false
	end
	if (BestineElectionScreenPlay:getCurrentPhase() == 1) then
		local playerID = CreatureObject(pPlayer):getObjectID()
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if BestineElectionScreenPlay:joinedVictorCampaign(pPlayer) or BestineElectionScreenPlay:joinedSeanCampaign(pPlayer) then
			local playerCampaign = readData(playerID..":bestine_election:"..quest.."_noroom")
			return (playerCampaign > 0)
		end
	end
	return false
end

function BestineElectionQuestpConvoHandler:giveQuestnItem(pPlayer,quest)
	if (pPlayer == nil or quest == nil) then
		return
	end
	
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		if quest == "slums" then
			local pItem = giveItem(pInventory,"object/tangible/loot/quest/victor_questp_testimony.iff", -1)
			if (pItem == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				return
			end
		elseif quest == "hospital" then
			local pItem = giveItem(pInventory,"object/tangible/loot/quest/victor_questp_receipt.iff", -1)
			if (pItem == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				return
			end
		elseif quest == "market" then
			local pItem = giveItem(pInventory,"object/tangible/loot/quest/sean_questp_mdisk.iff", -1)
			if (pItem == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
				return
			end
		elseif quest == "house" then
			local pItem = giveItem(pInventory,"object/tangible/loot/quest/sean_questp_htestimony.iff", -1)
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

function BestineElectionQuestpConvoHandler:getQuestID(pNpc)
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

function BestineElectionQuestpConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local objectName = SceneObject(pNpc):getTemplateObjectPath()
	local questID = self:getQuestID(pNpc)
	if BestineElectionScreenPlay:getCurrentPhase() == 2 then
		return convoTemplate:getScreen("no_office")
	end
	
	if string.find(SceneObject(pNpc):getTemplateObjectPath(), "sean") ~= nil and (not seanTrenwellConvoHandler:seanNegQuest(pPlayer)) then
		return convoTemplate:getScreen("default_reply")
	end

	if string.find(SceneObject(pNpc):getTemplateObjectPath(), "victor") ~= nil and (not victorVisalisConvoHandler:victorNegQuest(pPlayer)) then
		return convoTemplate:getScreen("default_reply")
	end

	if self:alreadyHasEvidence(pPlayer,questID) then
		return convoTemplate:getScreen("already_has_evidence")
	end

	if self:hasNoRoom(pPlayer,questID) then
		return convoTemplate:getScreen("noroom_returned")
	end
	if BestineElectionScreenPlay:joinedVictorCampaign(pPlayer) or BestineElectionScreenPlay:joinedSeanCampaign(pPlayer) then
		return convoTemplate:getScreen("quest_start")
	end
	return convoTemplate:getScreen("default_reply")
end


function BestineElectionQuestpConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local playerID = CreatureObject(conversingPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local questID = self:getQuestID(conversingNPC)

	if (screenID == "noroom") then
		writeData(playerID..":bestine_election:"..questID.."_noroom",electionNum)
	end

	if (screenID == "noroom_returned") then
		if questID == "house" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_house:s_e69937da","noroom_returned_noroom") --Yes. Thank you.
			else clonedConversation:addOption("@conversation/sean_questp_house:s_e69937da","give_item") --Yes. Thank you.
			end
		clonedConversation:addOption("@conversation/sean_questp_house:s_48b343d3","noroom_returned_nochance") 	--Actually, no I don't.
		elseif questID == "market" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_market:s_e69937da","noroom_returned_noroom") --Yes. Thank you.
			else clonedConversation:addOption("@conversation/sean_questp_market:s_e69937da","give_item") --Yes. Thank you.
			end
		clonedConversation:addOption("@conversation/sean_questp_market:s_48b343d3","noroom_returned_nochance") 	--Actually, no I don't.
		elseif questID == "hospital" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questp_hospital:s_ee6997ba","noroom_returned_noroom") -- I do, thank you.
			else	clonedConversation:addOption("@conversation/victor_questp_hospital:s_ee6997ba","noroom_returned_giveitem") -- I do, thank you.
			end
		clonedConversation:addOption("@conversation/victor_questp_hospital:s_76cc19da","noroom_returned_nochance") --No, I still don't have room.
		elseif questID == "slums" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questp_slums:s_ee6997ba","noroom_returned_noroom") -- I do, thank you.
			else	clonedConversation:addOption("@conversation/victor_questp_slums:s_ee6997ba","noroom_returned_giveitem") -- I do, thank you.
			end
		clonedConversation:addOption("@conversation/victor_questp_slums:s_76cc19da","noroom_returned_nochance") --No, I still don't have room.
		end
	end

	if (screenID == "quest_start3") or (screenID == "quest_start4") then
		if questID == "house" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_house:s_67e6df55","noroom") --Okay
				else clonedConversation:addOption("@conversation/sean_questp_house:s_67e6df55","give_item") --Okay
			end
		elseif questID == "hospital" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questp_hospital:s_67e6df55","noroom") --Okay.
				else clonedConversation:addOption("@conversation/victor_questp_hospital:s_67e6df55","give_item") --Okay.
			end
		elseif questID == "market" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_market:s_fc27931b","noroom") --Thanks.
			else clonedConversation:addOption("@conversation/sean_questp_market:s_fc27931b","give_item") --Thanks.
			end
		elseif questID == "slums" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/victor_questp_slums:s_67e6df55","noroom") --Okay.
			else clonedConversation:addOption("@conversation/victor_questp_slums:s_67e6df55","give_item") --Okay.
			end
		end
	end

	if (screenID == "give_item") then
		self:giveQuestpItem(conversingPlayer,questID)
	end

	return conversationScreen
end

function BestineElectionQuestpConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
