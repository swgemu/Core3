local JunkDealer = require("screenplays.junk_dealer.junk_dealer")

JunkDealerConvoHandler = conv_handler:new {}

function JunkDealerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if string.find(screenID, "start_sale") ~= nil then
		local dealerType = string.gsub(screenID, "start_sale_", "")
		JunkDealer:sendSellJunkSelection(pPlayer, pNpc, dealerType)
	elseif string.find(screenID, "give_") ~= nil then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if pInventory == nil or SceneObject(pInventory):isContainerFullRecursive() then
			clonedScreen:setDialogTextStringId("@conversation/junk_dealer_generic:s_5b10c0b9") -- I am sorry but you do not have any space in your inventory for me to give you a kit. Maybe you should clear out some room and talk to me again if you are still interested.
		else
			local kitTemplate = ""

			if screenID == "give_orange" then
				kitTemplate = "object/tangible/loot/collectible/kits/orange_rug_kit.iff"
			elseif screenID == "give_blue" then
				kitTemplate = "object/tangible/loot/collectible/kits/blue_rug_kit.iff"
			elseif screenID == "give_gong" then
				kitTemplate = "object/tangible/loot/collectible/kits/gong_kit.iff"
			elseif screenID == "give_table" then
				kitTemplate = "object/tangible/loot/collectible/kits/light_table_kit.iff"
			elseif screenID == "give_sculpture" then
				kitTemplate = "object/tangible/loot/collectible/kits/sculpture_kit.iff"
			end

			if getContainerObjectByTemplate(pInventory, kitTemplate, true) ~= nil then
				clonedScreen:setDialogTextStringId("@conversation/junk_dealer_generic:s_3df21ea0") -- It would appear that you already have one of these kits. I know I really want to get rid of all these kits but I just can't be handing them all out at once. You never know when they might be worth something.
			else
				giveItem(pInventory, kitTemplate, -1)
			end
		end
	end

	return pConvScreen
end
