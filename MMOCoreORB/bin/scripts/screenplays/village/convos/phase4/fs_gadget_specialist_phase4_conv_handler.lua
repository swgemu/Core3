local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageGadgetSpecialistPhase4ConvoHandler = {  }

function villageGadgetSpecialistPhase4ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (readData(SceneObject(pPlayer):getObjectID() .. ":returningForCraftingKit") == 1) then
		return convoTemplate:getScreen("return_to_buy")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageGadgetSpecialistPhase4ConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	local playerID = SceneObject(conversingPlayer):getObjectID()

	if (screenID == "intro") then
		local curQuestNum = FsCrafting4:getActiveQuestNum(conversingPlayer)

		if (curQuestNum == 1) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_79fe19ed", "who_gave_idea")
		elseif (curQuestNum == 2) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_c7baf80c", "collect_all_components")
		elseif (curQuestNum == 3) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_bab2829b", "any_ticket_droid")
		elseif (curQuestNum == 4) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_7f396fce", "simply_use_device")
		elseif (curQuestNum == 5) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_b867b2e4", "ask_chief_engineer")
		elseif (curQuestNum == 6) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_fe739220", "bask_in_glory")
		end

		clonedConversation:addOption("@conversation/fs_gadget_specialist:s_5542b04b", "quite_alright")
	elseif (screenID == "one_other_thing" or screenID == "return_to_buy") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if (CreatureObject(conversingPlayer):getCashCredits() < 530) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_a8749106", "not_enough_funds")
		elseif (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_a8749106", "not_enough_space")
		else
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_a8749106", "place_in_inventory")
		end

		clonedConversation:addOption("@conversation/fs_gadget_specialist:s_8fe6a678", "offering_to_help")
	elseif (screenID == "place_in_inventory") then
		local pInventory = CreatureObject(conversingPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pTracker = getContainerObjectByTemplate(pInventory, "object/tangible/loot/collectible/collectible_rewards/fs_tracking_device.iff", true)

			if (pTracker == nil) then
				local pItem = giveItem(pInventory, "object/tangible/loot/collectible/kits/fs_tracking_device_kit.iff", -1)

				if (pItem ~= nil) then
					CreatureObject(conversingPlayer):subtractCashCredits(530)
					QuestManager.completeQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_01)
					QuestManager.activateQuest(conversingPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_02)
					deleteData(SceneObject(conversingPlayer):getObjectID() .. ":returningForCraftingKit")
					TangibleObject(pItem):setLuaStringData("ownerID", playerID)
					createObserver(OBJECTREMOVEDFROMZONE, "FsCrafting4", "notifyTrackingKitDestroyed", pItem, 1)
				end
			end
		end
	elseif (screenID == "not_enough_funds" or screenID == "not_enough_space" or screenID == "offering_to_help") then
		writeData(playerID .. ":returningForCraftingKit", 1)
	end

	return conversationScreen
end

function villageGadgetSpecialistPhase4ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
