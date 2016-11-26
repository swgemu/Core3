junkDealerArmsConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_dealer_arms:s_3c06418f", -- Hmmm. You seem to be a discreet sort. Perhaps you are looking to do some business. If you have any untraceable weapons that maybe you would like to get off your hands I am the right person to see
	stopConversation = "false",
	options = {
		{"@conversation/junk_dealer_arms:s_c86eba88", "start_sale_arms"}, -- I think I have a few things that you might be interested in.
		{"@conversation/junk_dealer_arms:s_370a03c", "right_you_are"}, -- I don't think that I have anything you would be interested in.
	}
}
junkDealerArmsConvoTemplate:addScreen(init);

start_sale_arms = ConvoScreen:new {
	id = "start_sale_arms",
	leftDialog = "@conversation/junk_dealer_arms:s_24f30320", -- Just remember what I said about discretion. My buyers would be less then pleased if the authorities got word of this transaction. And I don't think you want my buyers to be unhappy.
	stopConversation = "true",
	options = {}
}
junkDealerArmsConvoTemplate:addScreen(start_sale_arms);

right_you_are = ConvoScreen:new {
	id = "right_you_are",
	leftDialog = "@conversation/junk_dealer_arms:s_df5bd64e", -- Right you are. Oh, and we never met.
	stopConversation = "true",
	options = {}
}
junkDealerArmsConvoTemplate:addScreen(right_you_are);

addConversationTemplate("junkDealerArmsConvoTemplate", junkDealerArmsConvoTemplate);
