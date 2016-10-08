local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageGadgetSpecialistPhase4ConvoHandler = conv_handler:new {}

function villageGadgetSpecialistPhase4ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (readData(SceneObject(pPlayer):getObjectID() .. ":returningForCraftingKit") == 1) then
		return convoTemplate:getScreen("return_to_buy")
	else
		return convoTemplate:getScreen("intro")
	end
end

function villageGadgetSpecialistPhase4ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local playerID = SceneObject(pPlayer):getObjectID()

	if (screenID == "intro") then
		local curQuestNum = FsCrafting4:getActiveQuestNum(pPlayer)

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
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (CreatureObject(pPlayer):getCashCredits() < 530) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_a8749106", "not_enough_funds")
		elseif (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_a8749106", "not_enough_space")
		else
			clonedConversation:addOption("@conversation/fs_gadget_specialist:s_a8749106", "place_in_inventory")
		end

		clonedConversation:addOption("@conversation/fs_gadget_specialist:s_8fe6a678", "offering_to_help")
	elseif (screenID == "place_in_inventory") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pTracker = getContainerObjectByTemplate(pInventory, "object/tangible/loot/collectible/collectible_rewards/fs_tracking_device.iff", true)

			if (pTracker == nil) then
				local pItem = giveItem(pInventory, "object/tangible/loot/collectible/kits/fs_tracking_device_kit.iff", -1)

				if (pItem ~= nil) then
					CreatureObject(pPlayer):subtractCashCredits(530)
					QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_01)
					QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_CRAFTING4_QUEST_02)
					deleteData(SceneObject(pPlayer):getObjectID() .. ":returningForCraftingKit")
					TangibleObject(pItem):setLuaStringData("ownerID", playerID)
					createObserver(OBJECTREMOVEDFROMZONE, "FsCrafting4", "notifyTrackingKitDestroyed", pItem, 1)
				end
			end
		end
	elseif (screenID == "not_enough_funds" or screenID == "not_enough_space" or screenID == "offering_to_help") then
		writeData(playerID .. ":returningForCraftingKit", 1)
	end

	return pConvScreen
end
