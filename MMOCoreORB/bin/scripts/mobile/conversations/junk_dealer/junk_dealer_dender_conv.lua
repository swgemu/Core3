junkDealerDenderConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_dender_rori:s_e88820", -- 'Ey thur! What you think you doin' walkin' up to me like that. If this was my bad day you be six feet under now. Since I feelin' generous I let slide...this time.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dender_rori:s_12400728", "have_guts"}, -- That decision was the smartest thing you have ever done.
		{"@conversation/junk_dender_rori:s_13d756ae", "leave"}, -- Whoa, sorry about that didn't mean to bother you.
	}
}
junkDealerDenderConvoTemplate:addScreen(init);

leave = ConvoScreen:new {
	id = "leave",
	leftDialog = "@conversation/junk_dender_rori:s_1ea1fb0f", -- Save your apology for someone who cares. You leave now!
	stopConversation = "true",
	options = {}
}
junkDealerDenderConvoTemplate:addScreen(leave);

have_guts = ConvoScreen:new {
	id = "have_guts",
	leftDialog = "@conversation/junk_dender_rori:s_fd11d689", -- You have some guts, eh thur killer? Me need someone with big guts to help me out with business deal that me have. You help me out and I make it worth your while.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dender_rori:s_c9aa99a2", "interested"}, -- I am listening.
		{"@conversation/junk_dender_rori:s_19e6693b", "later"}, -- I don't do business with your kind.
	}
}
junkDealerDenderConvoTemplate:addScreen(have_guts);

later = ConvoScreen:new {
	id = "later",
	leftDialog = "@conversation/junk_dender_rori:s_cfe66406", -- Too bad. I offering easy work and good credits. Later chump.
	stopConversation = "true",
	options = {}
}
junkDealerDenderConvoTemplate:addScreen(later);

interested = ConvoScreen:new {
	id = "interested",
	leftDialog = "@conversation/junk_dender_rori:s_42c6dbd2", -- I knew you interested. I have buyers, big league Imperial types, who trying to get their hands on gungan stuffs. I don't think they want the souvenirs so much as they want less gungans in world.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dender_rori:s_6925372f", "whole_lot"}, -- Keep going, I am still listening.
		{"@conversation/junk_dender_rori:s_e2f6a3b8", "neighborly"}, -- This just sounds like a bad idea.
	}
}
junkDealerDenderConvoTemplate:addScreen(interested);

neighborly = ConvoScreen:new {
	id = "neighborly",
	leftDialog = "@conversation/junk_dender_rori:s_ef66cf46:", -- Your loss. I tryin' to be all neighborly like and share the spoils with you...
	stopConversation = "true",
	options = {}
}
junkDealerDenderConvoTemplate:addScreen(neighborly);

whole_lot = ConvoScreen:new {
	id = "whole_lot",
	leftDialog = "@conversation/junk_dender_rori:s_7d842aa5", -- If you come across any of those gungan signets that they wear or one of their lances, you come back and see me. I buy whole lot from you, no questions.
	stopConversation = "false",
	options = {
		{"@conversation/junk_dender_rori:s_673b632f", "start_sale_gungan"}, -- It is your lucky day. I have what you are looking for.
		{"@conversation/junk_dender_rori:s_a753e4d6", "looking_dumb"}, -- I don't appear to have anything you would want to buy.
	}
}
junkDealerDenderConvoTemplate:addScreen(whole_lot);

looking_dumb = ConvoScreen:new {
	id = "looking_dumb",
	leftDialog = "@conversation/junk_dender_rori:s_b0d63c3a", -- Bah...don't stand thur lookin' dumb. Come back if you have anything me buy.
	stopConversation = "true",
	options = {}
}
junkDealerDenderConvoTemplate:addScreen(looking_dumb);

start_sale_gungan = ConvoScreen:new {
	id = "start_sale_gungan",
	leftDialog = "@conversation/junk_dender_rori:s_9aa94773", -- I right about you, eh thur killer? Lets see what you gots. Hmmm...not to bad, you have some things I make offer on.
	stopConversation = "true",
	options = {}
}
junkDealerDenderConvoTemplate:addScreen(start_sale_gungan);

addConversationTemplate("junkDealerDenderConvoTemplate", junkDealerDenderConvoTemplate);
