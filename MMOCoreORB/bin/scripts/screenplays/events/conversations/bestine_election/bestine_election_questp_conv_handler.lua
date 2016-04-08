local ObjectManager = require("managers.object.object_manager")

BestineElectionQuestpConvoHandler = Object:new {
	}

local HOUSE = "object/tangible/loot/quest/sean_questp_htestimony.iff"
local MARKET = "object/tangible/loot/quest/sean_questp_mdisk.iff"
local SLUMS = "object/tangible/loot/quest/victor_questp_testimony.iff"
local HOSPITAL = "object/tangible/loot/quest/victor_questp_receipt.iff"



function BestineElectionQuestpConvoHandler:alreadyHasEvidence(pPlayer, quest)
	if (pPlayer == nil or quest == "") then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		if quest == "slums" then
			return getContainerObjectByTemplate(pInventory, SLUMS , true) ~= nil
		elseif quest == "hospital" then
			return getContainerObjectByTemplate(pInventory, HOSPITAL , true) ~= nil
		elseif quest == "market" then
			return getContainerObjectByTemplate(pInventory, MARKET , true) ~= nil
		elseif quest == "house" then
			return getContainerObjectByTemplate(pInventory, HOUSE , true) ~= nil
		end
	end
	return false
end

function BestineElectionQuestpConvoHandler:giveQuestpItem(pPlayer,quest)
	if (pPlayer == nil or quest == "") then
		return
	end
	local pItem = nil

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		if quest == "slums" then
			pItem = giveItem(pInventory, SLUMS, -1)
		elseif quest == "hospital" then
			pItem = giveItem(pInventory, HOSPITAL, -1)
		elseif quest == "market" then
			pItem = giveItem(pInventory, MARKET, -1)
		elseif quest == "house" then
			pItem = giveItem(pInventory, HOUSE, -1)
		end
		if (pItem == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
			return
		end
		local playerID = CreatureObject(pPlayer):getObjectID()
		deleteData(playerID..":bestine_election:"..quest.."_noroom")
	end
end

function BestineElectionQuestpConvoHandler:getQuestID(pNpc)
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

function BestineElectionQuestpConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local objectName = SceneObject(pNpc):getTemplateObjectPath()
	local questID = self:getQuestID(pNpc)

	if BestineElectionScreenPlay:getCurrentPhase() == 2 then
		return convoTemplate:getScreen("no_office")
	elseif (string.find(objectName,"sean") and (BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Sean"))) then
		return convoTemplate:getScreen("default_reply")
	elseif (string.find(objectName,"victor") and (BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Victor"))) then
		return convoTemplate:getScreen("default_reply")
	elseif self:alreadyHasEvidence(pPlayer,questID) then
		return convoTemplate:getScreen("already_has_evidence")
	elseif BestineElectionScreenPlay:noroomReturned(pPlayer,questID) then
		return convoTemplate:getScreen("noroom_returned")
	elseif BestineElectionScreenPlay:joinedCampaign(pPlayer, "Victor") or BestineElectionScreenPlay:joinedCampaign(pPlayer, "Sean") then
		return convoTemplate:getScreen("quest_start")
	end
	return convoTemplate:getScreen("default_reply")
end


function BestineElectionQuestpConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local questID = self:getQuestID(conversingNPC)

	if (screenID == "noroom") then
		writeData(CreatureObject(conversingPlayer):getObjectID()..":bestine_election:"..questID.."_noroom",electionNum)
	elseif (screenID == "noroom_returned") then
		if questID == "house" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_house:s_e69937da","noroom_returned_noroom") --Yes. Thank you.
			else clonedConversation:addOption("@conversation/sean_questp_house:s_e69937da","noroom_returned_giveitem") --Yes. Thank you.
			end
			clonedConversation:addOption("@conversation/sean_questp_house:s_48b343d3","noroom_returned_nochance") 	--Actually, no I don't.
		elseif questID == "market" then
			if BestineElectionScreenPlay:hasFullInventory(conversingPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_market:s_e69937da","noroom_returned_noroom") --Yes. Thank you.
			else clonedConversation:addOption("@conversation/sean_questp_market:s_e69937da","noroom_returned_giveitem") --Yes. Thank you.
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
	elseif (screenID == "quest_start_final") then
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
	elseif (screenID == "give_item") or (screenID == "noroom_returned_giveitem") then
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
