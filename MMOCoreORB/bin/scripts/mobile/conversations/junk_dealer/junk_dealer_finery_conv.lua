junkDealerFineryConvoTemplate = ConvoTemplate:new {
	initialScreen = "ask_for_loot",
	templateType = "Lua",
	luaClassHandler = "JunkDealerFineryConvoHandler",
	screens = {}
}

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_dealer_finery:s_9666d79a", -- Hello my friend. How are you doing today? I am a buyer of finery....clothing, jewelry, and such. If you happen to have anything that I might like to buy please let me know.
	stopConversation = "false",
	options = {
		--{"@conversation/junk_dealer_finery:s_c86eba88", "start_sale"}, -- I think I have a few things that you might be interested in.
		--{"@conversation/junk_dealer_finery:s_370a03c", "no_loot"}, -- I don't think that I have anything you would be interested in.
	}
}
junkDealerFineryConvoTemplate:addScreen(ask_for_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_dealer_finery:s_e8ceb290", -- That is wonderful news. Let me see what you have to offer and I will give you price on anything I wish to buy. Remember there is no obligation to sell but I certainly hope you decide to conduct your business with me.
	stopConversation = "true",
	options = {}
}
junkDealerFineryConvoTemplate:addScreen(start_sale);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_dealer_finery:s_1eb9feb7", -- That is too bad. I was really hoping to get some new stock in today.
	stopConversation = "true",
	options = {}
}
junkDealerFineryConvoTemplate:addScreen(no_loot);

addConversationTemplate("junkDealerFineryConvoTemplate", junkDealerFineryConvoTemplate);
