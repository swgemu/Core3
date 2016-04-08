local ObjectManager = require("managers.object.object_manager")

StoneMerchantConvoHandler = Object:new {
}

function StoneMerchantConvoHandler:SearchForStones(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		if getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true) or
			getContainerObjectByTemplate(pInventory,"object/tangible/loot/quest/smooth_stone.iff", true) then
			return true
		end
 	end
	return false
end

function StoneMerchantConvoHandler:SearchforSmooth(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		if getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true) then
			return true
		end
	end
	return false
end

function StoneMerchantConvoHandler:SearchforCarved(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory ~= nil then
		if getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true) then
			return true
		end
	end
	return false
end

function StoneMerchantConvoHandler:returnCustomer(pPlayer)
	local playerID = CreatureObject(pPlayer):getObjectID()
	if (tonumber(readScreenPlayData(pPlayer, "BestineElection", "carvedStoneReward")) ~= nil) then
		return (tonumber(readScreenPlayData(pPlayer, "BestineElection", "carvedStoneReward")) > 0)
	end

	if readData(playerID..":bestine_election:smoothstonereward") > 0 then
 		return true
	end
	return false
end

function StoneMerchantConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if self:returnCustomer(pPlayer) then
		return convoTemplate:getScreen("returned_have_stones")
	end
	return convoTemplate:getScreen("intro_start")
end

function StoneMerchantConvoHandler:GiveSmoothStoneReward(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		local pSmoothStone = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true)
		if pSmoothStone ~= nil then
			SceneObject(pSmoothStone):destroyObjectFromWorld()
			SceneObject(pSmoothStone):destroyObjectFromDatabase()
		end
		local pReward = giveItem(pInventory, "object/weapon/ranged/carbine/carbine_e11_victor_quest.iff", -1)
		if (pReward == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item carbine_e11_victor_quest.iff")
			return
		end
		writeScreenPlayData(pPlayer, "BestineElection", "smootheStoneReward", 1)
		
		return
	end
end

function StoneMerchantConvoHandler:GiveCarvedStoneReward(pPlayer)
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		local pCarvedStone = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true)
		if pCarvedStone ~= nil then
			SceneObject(pCarvedStone):destroyObjectFromWorld()
			SceneObject(pCarvedStone):destroyObjectFromDatabase()
		end
		local pReward = giveItem(pInventory,"object/tangible/wearables/armor/marauder/armor_marauder_s02_chest_plate_quest.iff", -1)
		if (pReward == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item carbine_e11_victor_quest.iff")
			return
		end
		writeScreenPlayData(pPlayer, "BestineElection", "carvedStoneReward", 1)
	end
	return
end

function StoneMerchantConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if (screenID == "intro_start") then
		if StoneMerchantConvoHandler:SearchForStones(conversingPlayer) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_98e55c89","may_have_stones")--I may have the stones you are looking for. s_98e55c89
		end
		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_2b5e768f","look_for_some")--I guess so. I'll look for some. s_2b5e768f
		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_4242e25b","probably_bye") -- Probably. Bye!
	end

	if (screenID == "may_have_stones") then
		if StoneMerchantConvoHandler:SearchforCarved(conversingPlayer) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_b6f71f8a","have_carved_stone")--I have a carved stone.s_b6f71f8a
		end
		if StoneMerchantConvoHandler:SearchforSmooth(conversingPlayer) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_af35650e","have_smooth_stone")-- I have a smooth stone.s_af35650e
		end
	end

	if (screenID == "have_more_stones") then
		if StoneMerchantConvoHandler:SearchforCarved(conversingPlayer) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_b6e7bea1","have_carved_stone")--Yes, I do. I have a carved stone.
		end
		if StoneMerchantConvoHandler:SearchforSmooth(conversingPlayer) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_af25c425","have_smooth_stone")-- Yes, I do. I have a smooth stone.
		end
		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_eaee4954","just_looking") --No, just looking around. See ya later!
	end

	if (screenID == "have_carved_stone") or (screenID == "have_smooth_stone") then
		if StoneMerchantConvoHandler:SearchforCarved(conversingPlayer) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_211ab5b4","give_carved_stone") --I'll give you the carved stone
		end
		if StoneMerchantConvoHandler:SearchforSmooth(conversingPlayer) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_38d8cf30","give_smooth_stone")--I'll give you the smooth stone.
		end
		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_8c741032","keeping_stone") --I'm going to keep it.
	end

	if (screenID == "give_smooth_stone") then
		StoneMerchantConvoHandler:GiveSmoothStoneReward(conversingPlayer)
	end

	if (screenID == "give_carved_stone") then
		StoneMerchantConvoHandler:GiveCarvedStoneReward(conversingPlayer)
	end

	return conversationScreen
end

function StoneMerchantConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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