local ObjectManager = require("managers.object.object_manager")

bestineStoneMerchantConvoHandler = conv_handler:new {}

function bestineStoneMerchantConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_SMOOTH_STONE) == BestineElection.VICTOR_STONE_REWARD_RECEIVED or
		BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_CARVED_STONE) == BestineElection.VICTOR_STONE_REWARD_RECEIVED) then
		return convoTemplate:getScreen("init_return")
	else
		return convoTemplate:getScreen("init_default")
	end
end

function bestineStoneMerchantConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local curPhase = BestineElection:getCurrentPhase()
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (screenID == "init_default") then
		if (pInventory == nil or curPhase == BestineElection.ELECTION_PHASE) then
			clonedConversation:setStopConversation(true)
		else
			if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true) or getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true)) then
				clonedConversation:addOption("@conversation/bestine_stone_merchant:s_98e55c89", "what_kind") -- I may have the stones you are looking for.
			else
				clonedConversation:addOption("@conversation/bestine_stone_merchant:s_2b5e768f", "dont_know_where") -- I guess so. I'll look for some.
			end

			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_4242e25b", "keep_searching") -- Probably. Bye!
		end
	elseif (screenID == "init_return") then
		if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true)) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_b6e7bea1", "take_off_your_hands") -- Yes, I do. I have a carved stone.
		end

		if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true)) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_af25c425", "take_off_your_hands") -- Yes, I do. I have a smooth stone.
		end

		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_eaee4954", "be_sure_to_come_back") -- No, just looking around. See ya later!
	elseif (screenID == "what_kind") then
		if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true)) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_b6f71f8a", "take_off_your_hands") -- I have a carved stone.
		end

		if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true)) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_af35650e", "take_off_your_hands") -- I have a smooth stone.
		end
	elseif (screenID == "take_off_your_hands") then
		if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true)) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_211ab5b4", "carved_guard_it") -- I'll give you the carved stone.
		end

		if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true)) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_38d8cf30", "smooth_guard_it") -- I'll give you the smooth stone.
		end

		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_8c741032", "seek_me_out") -- I'm going to keep it.
	elseif (screenID == "carved_guard_it" or screenID == "smooth_guard_it") then
		local rewardTemplate
		local pStone

		if (pInventory == nil) then
			return pConvScreen
		end

		if (screenID == "carved_guard_it") then
			rewardTemplate = "object/tangible/wearables/armor/marauder/armor_marauder_s02_chest_plate_quest.iff"
			pStone = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true)
			BestineElection:setQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_CARVED_STONE, BestineElection.VICTOR_STONE_REWARD_RECEIVED)
		elseif (screenID == "smooth_guard_it") then
			rewardTemplate = "object/weapon/ranged/carbine/carbine_e11_victor_quest.iff"
			pStone = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true)
			BestineElection:setQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_SMOOTH_STONE, BestineElection.VICTOR_STONE_REWARD_RECEIVED)
		end

		if (pStone == nil) then
			return pConvScreen
		end

		SceneObject(pStone):destroyObjectFromWorld()
		SceneObject(pStone):destroyObjectFromDatabase()

		local pEvidence = giveItem(pInventory, rewardTemplate, -1)

		if (pEvidence == nil) then
			printLuaError("Error creating stone reward " .. rewardTemplate .. " for player " .. CreatureObject(pPlayer):getFirstName())
		end
	end

	return pConvScreen
end
