junkDealerJawaConvoTemplate = ConvoTemplate:new {
	initialScreen = "ask_for_loot",
	templateType = "Lua",
	luaClassHandler = "JunkDealerJawaConvoHandler",
	screens = {}
}

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@jawa_trader:greeting", -- ...
	stopConversation = "false",
	options = {
		--{"@jawa_trader:yes", "start_sale"}, -- Yes.
		--{"@jawa_trader:no", "no_loot"}, -- No.
	}
}
junkDealerJawaConvoTemplate:addScreen(ask_for_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@jawa_trader:start_trading", -- He is going to look at what I have to sell and see if there is anything that he wants to buy. He will make me an offer on anything he is interested in. I better keep a keen eye on him, things seem to have a way of disappearing when Jawas are around.
	stopConversation = "true",
	options = {}
}
junkDealerJawaConvoTemplate:addScreen(start_sale);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@jawa_trader:goodbye", -- The Jawa wishes me safe journey and told me to come back if I come across anything that he would be interested in.
	stopConversation = "true",
	options = {}
}
junkDealerJawaConvoTemplate:addScreen(no_loot);

addConversationTemplate("junkDealerJawaConvoTemplate", junkDealerJawaConvoTemplate);

junkDealerJawaArmsConvoTemplate = junkDealerJawaConvoTemplate:new {
	luaClassHandler = "JunkDealerJawaArmsConvoHandler"
}

addConversationTemplate("junkDealerJawaArmsConvoTemplate", junkDealerJawaArmsConvoTemplate);

junkDealerJawaFineryConvoTemplate = junkDealerJawaConvoTemplate:new {
	luaClassHandler = "JunkDealerJawaFineryConvoHandler"
}

addConversationTemplate("junkDealerJawaFineryConvoTemplate", junkDealerJawaFineryConvoTemplate);

junkDealerJawaTuskenConvoTemplate = junkDealerJawaConvoTemplate:new {
	luaClassHandler = "JunkDealerJawaTuskenConvoHandler"
}

addConversationTemplate("junkDealerJawaTuskenConvoTemplate", junkDealerJawaTuskenConvoTemplate);
