local JunkDealer = require("screenplays.junk_dealer.junk_dealer")

JunkDealerConvoHandler = conv_handler:new {
	junkType = "",
	noLootText = "",
	startSaleText = "",
	inventorText = ""
}

function JunkDealerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if screenID == "ask_for_loot" then
		local junkList = JunkDealer:getEligibleJunk(pPlayer, self.junkType)

		if #junkList > 0 then
			clonedScreen:addOption(self.startSaleText, "start_sale")
		end

		clonedScreen:addOption(self.noLootText, "no_loot")

		if self.inventorText ~= "" then
			clonedScreen:addOption(self.inventorText, "inventor")
		end
	elseif screenID == "start_sale" then
		JunkDealer:sendSellJunkSelection(pPlayer, pNpc, self.junkType)
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

JunkDealerGenericConvoHandler = JunkDealerConvoHandler:new {
	junkType = "generic",
	noLootText = "@conversation/junk_dealer_generic:s_cd7a3f41",
	startSaleText = "@conversation/junk_dealer_generic:s_54fab04f",
	inventorText = "@conversation/junk_dealer_generic:s_3aa18b2d"
}

JunkDealerArmsConvoHandler = JunkDealerConvoHandler:new {
	junkType = "arms",
	noLootText = "@conversation/junk_dealer_arms:s_370a03c",
	startSaleText = "@conversation/junk_dealer_arms:s_c86eba88"
}

JunkDealerFineryConvoHandler = JunkDealerConvoHandler:new {
	junkType = "finery",
	noLootText = "@conversation/junk_dealer_finery:s_370a03c",
	startSaleText = "@conversation/junk_dealer_finery:s_c86eba88"
}

JunkDealerDenderConvoHandler = JunkDealerConvoHandler:new {
	junkType = "gungan",
	noLootText = "@conversation/junk_dender_rori:s_a753e4d6",
	startSaleText = "@conversation/junk_dender_rori:s_673b632f"
}

JunkDealerLilaConvoHandler = JunkDealerConvoHandler:new {
	junkType = "arms",
	noLootText = "@conversation/junk_lila_borvo:s_e8b03c7c",
	startSaleText = "@conversation/junk_lila_borvo:s_1875d09c"
}

JunkDealerMalikConvoHandler = JunkDealerConvoHandler:new {
	junkType = "corsec",
	noLootText = "@conversation/junk_malik_vistal:s_d36db42d",
	startSaleText = "@conversation/junk_malik_vistal:s_fc51be40"
}

JunkDealerNadoConvoHandler = JunkDealerConvoHandler:new {
	junkType = "generic",
	noLootText = "@conversation/junk_nado_wattos:s_90b63763",
	startSaleText = "@conversation/junk_nado_wattos:s_a5d02a3c"
}

JunkDealerNathanConvoHandler = JunkDealerConvoHandler:new {
	junkType = "jawa",
	noLootText = "@conversation/junk_nathan_taike:s_69567be7",
	startSaleText = "@conversation/junk_nathan_taike:s_ecf19442"
}

JunkDealerOlloboConvoHandler = JunkDealerConvoHandler:new {
	junkType = "arms",
	noLootText = "@conversation/junk_ollobo_jabbas:s_b85badf5",
	startSaleText = "@conversation/junk_ollobo_jabbas:s_e2ee167d"
}

JunkDealerQuichConvoHandler = JunkDealerConvoHandler:new {
	junkType = "jedi",
	noLootText = "@conversation/junk_quich_dantooine:s_6e11f342",
	startSaleText = "@conversation/junk_quich_dantooine:s_463bc6c4"
}

JunkDealerReggiConvoHandler = JunkDealerConvoHandler:new {
	junkType = "arms",
	noLootText = "@conversation/junk_reggi_nym:s_2e005077",
	startSaleText = "@conversation/junk_reggi_nym:s_b8e27f3c"
}

JunkDealerSheaniConvoHandler = JunkDealerConvoHandler:new {
	junkType = "finery",
	noLootText = "@conversation/junk_sheani_lake:s_d264cf44",
	startSaleText = "@conversation/junk_sheani_lake:s_370197a6"
}

JunkDealerSnegConvoHandler = JunkDealerConvoHandler:new {
	junkType = "arms",
	noLootText = "@conversation/junk_sneg_valarian:s_b4cc3fb7",
	startSaleText = "@conversation/junk_sneg_valarian:s_94fa366f"
}
