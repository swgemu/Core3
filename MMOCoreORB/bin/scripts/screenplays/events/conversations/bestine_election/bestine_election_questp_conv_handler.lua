local ObjectManager = require("managers.object.object_manager")

BestineElectionQuestpConvoHandler = conv_handler:new {
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

function BestineElectionQuestpConvoHandler:giveQuestpItem(pPlayer, quest)
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
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item: "..quest)
			return
		end

		deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:"..quest.."_noroom")
	end
end

function BestineElectionQuestpConvoHandler:getQuestID(objectName)
	if (string.find(objectName, "slums") ~= nil) then
		return "slums"
	elseif (string.find(objectName, "hospital") ~= nil) then
		return "hospital"
	elseif (string.find(objectName, "market") ~= nil) then
		return "market"
	elseif (string.find(objectName, "house") ~= nil) then
		return "house"
	else
		return ""
	end
end

function BestineElectionQuestpConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local objectName = SceneObject(pNpc):getTemplateObjectPath()
	local questID = self:getQuestID(objectName)

	if (screenID == "noroom") then
		writeData(CreatureObject(pPlayer):getObjectID()..":bestine_election:"..questID.."_noroom", electionNum)
	elseif (screenID == "noroom_returned") then
		if questID == "house" then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_house:s_e69937da", "noroom_returned_noroom") -- Yes. Thank you.
			else
				clonedConversation:addOption("@conversation/sean_questp_house:s_e69937da", "noroom_returned_giveitem") -- Yes. Thank you.
			end
			clonedConversation:addOption("@conversation/sean_questp_house:s_48b343d3", "noroom_returned_reply") -- Actually, no I don't.
		elseif questID == "market" then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_market:s_e69937da", "noroom_returned_noroom") -- Yes. Thank you.
			else
				clonedConversation:addOption("@conversation/sean_questp_market:s_e69937da", "noroom_returned_giveitem") -- Yes. Thank you.
			end
			clonedConversation:addOption("@conversation/sean_questp_market:s_48b343d3", "noroom_returned_reply") -- Actually, no I don't.
		elseif questID == "hospital" then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_questp_hospital:s_ee6997ba", "noroom_returned_noroom") -- I do, thank you.
			else
				clonedConversation:addOption("@conversation/victor_questp_hospital:s_ee6997ba", "noroom_returned_giveitem") -- I do, thank you.
			end
			clonedConversation:addOption("@conversation/victor_questp_hospital:s_76cc19da", "noroom_returned_reply") -- No, I still don't have room.
		elseif questID == "slums" then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_questp_slums:s_ee6997ba", "noroom_returned_noroom") -- I do, thank you.
			else
				clonedConversation:addOption("@conversation/victor_questp_slums:s_ee6997ba", "noroom_returned_giveitem") -- I do, thank you.
			end
			clonedConversation:addOption("@conversation/victor_questp_slums:s_76cc19da", "noroom_returned_reply") -- No, I still don't have room.
		end
	elseif (screenID == "convo_start_give") then
		if questID == "house" then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_house:s_67e6df55", "noroom") -- Okay
			else
				clonedConversation:addOption("@conversation/sean_questp_house:s_67e6df55", "give_item") -- Okay
			end
		elseif questID == "hospital" then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_questp_hospital:s_67e6df55", "noroom") -- Okay.
			else
				clonedConversation:addOption("@conversation/victor_questp_hospital:s_67e6df55", "give_item") -- Okay.
			end
		elseif questID == "market" then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_questp_market:s_fc27931b", "noroom") -- Thanks.
			else
				clonedConversation:addOption("@conversation/sean_questp_market:s_fc27931b", "give_item") -- Thanks.
			end
		elseif questID == "slums" then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_questp_slums:s_67e6df55", "noroom") -- Okay.
			else
				clonedConversation:addOption("@conversation/victor_questp_slums:s_67e6df55", "give_item") -- Okay.
			end
		end
	elseif (screenID == "give_item") or (screenID == "noroom_returned_giveitem") then
		self:giveQuestpItem(pPlayer,questID)
	end

	return pConvScreen
end

function BestineElectionQuestpConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local objectName = SceneObject(pNpc):getTemplateObjectPath()
	local questID = self:getQuestID(objectName)

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return convoTemplate:getScreen("no_business")
	elseif BestineElectionScreenPlay:getCurrentPhase() == 2 then
		return convoTemplate:getScreen("no_election")
	elseif self:alreadyHasEvidence(pPlayer, questID) then
		return convoTemplate:getScreen("already_has_evidence")
	elseif BestineElectionScreenPlay:noroomReturned(pPlayer, questID) then
		return convoTemplate:getScreen("noroom_returned")
	elseif ((string.find(objectName, "victor") ~= nil) and (BestineElectionScreenPlay:joinedCampaign(pPlayer, "victor"))) then
		return convoTemplate:getScreen("convo_start")
	elseif ((string.find(objectName, "sean") ~= nil) and (BestineElectionScreenPlay:joinedCampaign(pPlayer, "sean"))) then
		return convoTemplate:getScreen("convo_start")
	end

	return convoTemplate:getScreen("no_business")
end
