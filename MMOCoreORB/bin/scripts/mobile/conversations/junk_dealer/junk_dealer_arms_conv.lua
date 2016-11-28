junkDealerArmsConvoTemplate = ConvoTemplate:new {
	initialScreen = "ask_for_loot",
	templateType = "Lua",
	luaClassHandler = "JunkDealerArmsConvoHandler",
	screens = {}
}

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_dealer_arms:s_3c06418f", -- Hmmm. You seem to be a discreet sort. Perhaps you are looking to do some business. If you have any untraceable weapons that maybe you would like to get off your hands I am the right person to see
	stopConversation = "false",
	options = {
		--{"@conversation/junk_dealer_arms:s_c86eba88", "start_sale"}, -- I think I have a few things that you might be interested in.
		--{"@conversation/junk_dealer_arms:s_370a03c", "no_loot"}, -- I don't think that I have anything you would be interested in.
	}
}
junkDealerArmsConvoTemplate:addScreen(ask_for_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_dealer_arms:s_24f30320", -- Just remember what I said about discretion. My buyers would be less then pleased if the authorities got word of this transaction. And I don't think you want my buyers to be unhappy.
	stopConversation = "true",
	options = {}
}
junkDealerArmsConvoTemplate:addScreen(start_sale);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_dealer_arms:s_df5bd64e", -- Right you are. Oh, and we never met.
	stopConversation = "true",
	options = {}
}
junkDealerArmsConvoTemplate:addScreen(no_loot);

addConversationTemplate("junkDealerArmsConvoTemplate", junkDealerArmsConvoTemplate);
