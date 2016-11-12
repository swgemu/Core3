local ObjectManager = require("managers.object.object_manager")

StoneMerchantConvoHandler = conv_handler:new {
}

local CARVED = "object/tangible/loot/quest/carved_stone.iff"
local SMOOTH = "object/tangible/loot/quest/smooth_stone.iff"

function StoneMerchantConvoHandler:SearchForStones(pPlayer, stoneObj)
	if (pPlayer == nil) or (stoneObj == "") then
		return false
	end

	if (stoneObj ~= CARVED) or (stoneObj ~= SMOOTH) then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		if getContainerObjectByTemplate(pInventory, stoneObj , true) then
			return true
		end
	end

	return false
end

function StoneMerchantConvoHandler:returnCustomer(pPlayer)
	local gotReward = readScreenPlayData(pPlayer, "BestineElection", "carvedStoneReward")

	if (gotReward == nil) or (gotReward == "") then
		gotReward = 0
	end

	if tonumber(gotReward) == 1 then
		return true
	end

	gotReward = readScreenPlayData(pPlayer, "BestineElection", "smoothStoneReward")
	if (gotReward == nil) or (gotReward == "") then
		gotReward = 0
	end

	if tonumber(gotReward) == 1 then
		return true
	end

	return false
end

function StoneMerchantConvoHandler:giveReward(pPlayer, stoneObj)
	if (pPlayer == nil) or (stoneObj == "") then
		return
	end

	local rewardObj = ""

	if (stoneObj == CARVED) then
		rewardObj = "object/tangible/wearables/armor/marauder/armor_marauder_s02_chest_plate_quest.iff"
	elseif (stoneObj == SMOOTH) then
		rewardObj = "object/weapon/ranged/carbine/carbine_e11_victor_quest.iff"
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		local pStone = getContainerObjectByTemplate(pInventory, stoneObj, true)
		if pStone ~= nil then
			SceneObject(pStone):destroyObjectFromWorld()
			SceneObject(pStone):destroyObjectFromDatabase()
			local pReward = giveItem(pInventory,rewardObj, -1)
			if (pReward == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item "..pReward)
				return
			end
			writeScreenPlayData(pPlayer, "BestineElection", string.lower(stoneObj).."StoneReward", 1)
		end
	end
end

function StoneMerchantConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()

	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "intro_start") then
		if StoneMerchantConvoHandler:SearchForStones(pPlayer, CARVED) or StoneMerchantConvoHandler:SearchforStones(pPlayer, SMOOTH) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_98e55c89","may_have_stones")--I may have the stones you are looking for. s_98e55c89
		end
		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_2b5e768f","look_for_some")--I guess so. I'll look for some. s_2b5e768f
		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_4242e25b","probably_bye") -- Probably. Bye!
	elseif (screenID == "may_have_stones") then
		if StoneMerchantConvoHandler:SearchforStones(pPlayer, CARVED) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_b6f71f8a","have_carved_stone")--I have a carved stone.s_b6f71f8a
		end
		if StoneMerchantConvoHandler:SearchforStones(pPlayer, SMOOTH) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_af35650e","have_smooth_stone")-- I have a smooth stone.s_af35650e
		end
	elseif (screenID == "returned_have_stones") then
		if StoneMerchantConvoHandler:SearchforStones(pPlayer, CARVED) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_b6e7bea1","have_carved_stone")--Yes, I do. I have a carved stone.
		end
		if StoneMerchantConvoHandler:SearchforStones(pPlayer, SMOOTH) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_af25c425","have_smooth_stone")-- Yes, I do. I have a smooth stone.
		end
		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_eaee4954","just_looking") --No, just looking around. See ya later!
	elseif (screenID == "have_carved_stone") or (screenID == "have_smooth_stone") then
		if StoneMerchantConvoHandler:SearchforStones(pPlayer, CARVED) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_211ab5b4","give_carved_stone") --I'll give you the carved stone
		end
		if StoneMerchantConvoHandler:SearchforStones(pPlayer, SMOOTH) then
			clonedConversation:addOption("@conversation/bestine_stone_merchant:s_38d8cf30","give_smooth_stone")--I'll give you the smooth stone.
		end
		clonedConversation:addOption("@conversation/bestine_stone_merchant:s_8c741032","keeping_stone") --I'm going to keep it.
	elseif (screenID == "give_smooth_stone") then
		StoneMerchantConvoHandler:giveReward(pPlayer, SMOOTH)
	elseif (screenID == "give_carved_stone") then
		StoneMerchantConvoHandler:giveReward(pPlayer, CARVED)
	end

	return pConvScreen
end

function StoneMerchantConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if self:returnCustomer(pPlayer) then
		return convoTemplate:getScreen("returned_have_stones")
	end

	return convoTemplate:getScreen("intro_start")
end
