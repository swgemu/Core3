junkDealerSnegConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerSnegConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_sneg_valarian:s_6dbdfc7", -- Greetings and be welcome. Please enjoy the facilities here at the Lucky Despot. Are you here to try your luck at one of our gaming tables or....perhaps you are here for business rather then pleasure?
	stopConversation = "false",
	options = {
		{"@conversation/junk_sneg_valarian:s_f0f3bea2", "sell_something"}, -- That depends on what sort of business you have in mind.
		{"@conversation/junk_sneg_valarian:s_50c8b3e1", "enjoy"}, -- I am just taking a look around.
	}
}
junkDealerSnegConvoTemplate:addScreen(init);

enjoy = ConvoScreen:new {
	id = "enjoy",
	leftDialog = "@conversation/junk_sneg_valarian:s_f7c66216", -- In that case, please enjoy the fabulous Lucky Despot.
	stopConversation = "true",
	options = {}
}
junkDealerSnegConvoTemplate:addScreen(enjoy);

sell_something = ConvoScreen:new {
	id = "sell_something",
	leftDialog = "@conversation/junk_sneg_valarian:s_4717ab1e", -- Perhaps you are here to sell something. Something that might be a little hard to sell elsewhere. Many people come here looking for Lady V's help in moving things that they otherwise cannot. If it something that the Lady deals with she might be willing to take it off of your hands.
	stopConversation = "false",
	options = {
		{"@conversation/junk_sneg_valarian:s_14b517b1", "assortment"}, -- What sort of things does Lady Valarian deal in?
		{"@conversation/junk_sneg_valarian:s_b4cc3fb7", "no_loot"}, -- I don't think I have anything that the Lady is interested in.
	}
}
junkDealerSnegConvoTemplate:addScreen(sell_something);

assortment = ConvoScreen:new {
	id = "assortment",
	leftDialog = "@conversation/junk_sneg_valarian:s_7debe28e", -- The Lady deals with all assortment of items. Anything from a CDEF to an imperial T-21. Of course, she currently has a special interest in hand-to-hand weapons. She also has a liking to various other odds and ends that can fetch a nice profit if you know the right people.
	stopConversation = "false",
	options = {
		{"@conversation/junk_sneg_valarian:s_50b9f32f", "ask_for_loot"}, -- What does Lady Valarian want with melee weapons?
		{"@conversation/junk_sneg_valarian:s_b4cc3fb7", "no_loot"}, -- I don't think I have anything that the Lady is interested in.
	}
}
junkDealerSnegConvoTemplate:addScreen(assortment);

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_sneg_valarian:s_e27c50ad", -- It is never wise to stick your nose into the Lady's business. Do you wish to do business with us or not?
	stopConversation = "false",
	options = {
		--{"@conversation/junk_sneg_valarian:s_94fa366f", "start_sale"}, -- Of course, lets conduct some business.
		--{"@conversation/junk_sneg_valarian:s_b4cc3fb7", "no_loot"}, -- I don't think I have anything that the Lady is interested in.
	}
}
junkDealerSnegConvoTemplate:addScreen(ask_for_loot);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_sneg_valarian:s_a3ad61f1", -- Very well. Good day to you.
	stopConversation = "true",
	options = {}
}
junkDealerSnegConvoTemplate:addScreen(no_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_sneg_valarian:s_63a817cf", -- Let me see what you have to offer. If I see anything that we might be interested in dealing with I will make an offer on. It is very wise to accept the generous offer that Lady V grants.
	stopConversation = "true",
	options = {}
}
junkDealerSnegConvoTemplate:addScreen(start_sale);

addConversationTemplate("junkDealerSnegConvoTemplate", junkDealerSnegConvoTemplate);
