junkDealerReggiConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerReggiConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_reggi_nym:s_60d2f507", -- Looking for work? I don't know that for sure but normally people who come around here are always looking for something.
	stopConversation = "false",
	options = {
		{"@conversation/junk_reggi_nym:s_ef8c7236", "ask_for_loot"}, -- I am always looking for work.
		{"@conversation/junk_reggi_nym:s_53d778d8", "true_words"}, -- Not really...work has never suited me.
	}
}
junkDealerReggiConvoTemplate:addScreen(init);

true_words = ConvoScreen:new {
	id = "true_words",
	leftDialog = "@conversation/junk_reggi_nym:s_f25d9c2", -- Truer words have never been spoken. But if you ever change your mind you know where to find me.
	stopConversation = "true",
	options = {}
}
junkDealerReggiConvoTemplate:addScreen(true_words);

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_reggi_nym:s_14e5bdc0", -- I don't really have to much in the way of jobs but Nym is always looking to buy weapons and such. He also has some bounties out on those cursed Blood Razors and Canyon Cosairs who haven't figured out their place yet.
	stopConversation = "false",
	options = {
		--{"@conversation/junk_reggi_nym:s_b8e27f3c", "start_sale"}, -- Well this looks like my lucky day.
		--{"@conversation/junk_reggi_nym:s_2e005077", "no_loot"}, -- It doesn't look like I have anything Nym would like to buy.
	}
}
junkDealerReggiConvoTemplate:addScreen(ask_for_loot);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_reggi_nym:s_233f3214", -- Not a problem. Like I said Nym is always looking for these things so if you run across any come on back.
	stopConversation = "true",
	options = {}
}
junkDealerReggiConvoTemplate:addScreen(no_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_reggi_nym:s_5c453a2f", -- Being lucky is one of the best things in the world. Lets take a look at what you have to offer. Nym isn't much for bartering so you can take the price I give or you can leave it. Makes no difference to me really.
	stopConversation = "true",
	options = {}
}
junkDealerReggiConvoTemplate:addScreen(start_sale);

addConversationTemplate("junkDealerReggiConvoTemplate", junkDealerReggiConvoTemplate);
