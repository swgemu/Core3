local ObjectManager = require("managers.object.object_manager")

BestineElectionQuestnConvoHandler = conv_handler:new {
}

local CANTINA = "object/tangible/loot/quest/victor_questn_dseal.iff"
local CAPITOL = "object/tangible/loot/quest/victor_questn_hlist.iff"
local UNIVERSITY = "object/tangible/loot/quest/sean_questn_gpapers.iff"

function BestineElectionQuestnConvoHandler:getQuestID(objectName)
	if (string.find(objectName, "cantina") ~= nil) then
		return "cantina"
	elseif (string.find(objectName, "capitol") ~= nil) then
		return "capitol"
	else
		return ("university")
	end
end

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

function BestineElectionQuestnConvoHandler:giveQuestnItem(pPlayer, quest)
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
			CreatureObject(pPlayer):subtractCashCredits(200)
			CreatureObject(pPlayer):sendSystemMessage("You successfully make a payment of 200 credits.")
		end
		local pItem = giveItem(pInventory, questnItem, -1)
		if (pItem == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item."..quest)
			return
		end

		deleteData(CreatureObject(pPlayer):getObjectID()..":bestine_election:"..quest.."_noroom")
	end
end

function BestineElectionQuestnConvoHandler:hasEnoughMoney(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	if (CreatureObject(pPlayer):getCashCredits() >= 200) then
		return true
	end

	return false
end

function BestineElectionQuestnConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerID = SceneObject(pPlayer):getObjectID()
	local objectName = SceneObject(pNpc):getTemplateObjectPath()
	local questID = self:getQuestID(objectName)

	if (screenID == "no_room") then
		writeData(playerID..":bestine_election:"..questID.."_noroom", electionNum)
	elseif (screenID == "give_item") or (screenID == "noroom_returned_giveitem") then
		self:giveQuestnItem(pPlayer, questID)
	elseif (screenID == "convo_start_give") then
		if (questID == "capitol") then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_b9b27823", "no_room") -- Thank you.
			else
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_b9b27823", "give_item") -- Thank you.
			end
		elseif (questID == "cantina") then
			if self:hasEnoughMoney(pPlayer) then
				if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
					clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991", "no_room") -- Hmm. Here you go.
				else
					clonedConversation:addOption("@conversation/victor_questn_cantina:s_51ac4991", "give_item") -- Hmm. Here you go.
				end
			else
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_19d90991", "no_money") -- I don't have that kind of money.
			end
		elseif (questID == "university") then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_questn_university:s_5ec23736", "no_room") -- Oh? I could really use your help...
			else
				clonedConversation:addOption("@conversation/sean_questn_university:s_5ec23736", "give_item") -- Oh? I could really use your help...
			end
		end
	elseif (screenID == "noroom_returned") then
		if (questID == "capitol") then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_90ec63e0", "noroom_returned_noroom") -- Yes, I do.
			else
				clonedConversation:addOption("@conversation/victor_questn_capitol:s_90ec63e0", "noroom_returned_giveitem") -- Yes, I do.
			end
			clonedConversation:addOption("@conversation/victor_questn_capitol:s_da9a29e9", "noroom_returned_reply") -- No, not yet.
		elseif (questID == "cantina") then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_90ec63e0", "noroom_returned_noroom") -- Yes, I do.
			else
				clonedConversation:addOption("@conversation/victor_questn_cantina:s_90ec63e0", "give_item") -- Yes, I do.
			end
			clonedConversation:addOption("@conversation/victor_questn_cantina:s_62bf3631", "noroom_returned_reply") -- No, I haven't made room yet.
		elseif (questID == "university") then
			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f", "noroom_returned_noroom") -- Yes, can I have the evidence, please?
			else
				clonedConversation:addOption("@conversation/sean_questn_university:s_7e78bf8f", "noroom_returned_giveitem") -- Yes, can I have the evidence, please?
			end
			clonedConversation:addOption("@conversation/sean_questn_university:s_7291fe2e", "noroom_returned_reply") -- Not yet. I still need to make room.
		end
	end

	return pConvScreen
end

function BestineElectionQuestnConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local objectName = SceneObject(pNpc):getTemplateObjectPath()
	local questID = self:getQuestID(objectName)

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return convoTemplate:getScreen("no_business")
	end

	if BestineElectionScreenPlay:getCurrentPhase() == 2 then
		return convoTemplate:getScreen("no_election")
	elseif self:alreadyHasEvidence(pPlayer, questID) then
		return convoTemplate:getScreen("already_has_evidence")
	elseif BestineElectionScreenPlay:noroomReturned(pPlayer,questID) then
		return convoTemplate:getScreen("noroom_returned")
	elseif (string.find(objectName, "victor") ~= nil and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "sean")) or (string.find(objectName, "sean") ~= nil and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "victor")) then
		if questID == "cantina" then
			return convoTemplate:getScreen("convo_start_give")
		else
			return convoTemplate:getScreen("convo_start")
		end
	end

	return convoTemplate:getScreen("no_business")
end
