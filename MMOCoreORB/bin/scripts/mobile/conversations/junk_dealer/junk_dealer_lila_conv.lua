junkDealerLilaConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerLilaConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_lila_borvo:s_ea90afa0", -- Well aren't you a fine specimen. Hmmmm....I gather that you are not here for the pleasure of my company. Speak up now, what is it that I can do for you?
	stopConversation = "false",
	options = {
		{"@conversation/junk_lila_borvo:s_a16cfd3b", "ask_for_loot"}, -- I hear that you are the person to see if one has something they need to move.
		{"@conversation/junk_lila_borvo:s_210d33b4", "shame"}, -- I don't think that there is anything that I need help with.
	}
}
junkDealerLilaConvoTemplate:addScreen(init);

shame = ConvoScreen:new {
	id = "shame",
	leftDialog = "@conversation/junk_lila_borvo:s_98d18f02", -- Isn't that a shame. Perhaps some other time.
	stopConversation = "true",
	options = {}
}
junkDealerLilaConvoTemplate:addScreen(shame);

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_lila_borvo:s_113dbce8", -- People talk to much. Loose talk has a way of getting them into trouble of the worse sort. But you strike me as being the discreet sort. My employer has been known to buying certain goods, as long as they are untraceable.
	stopConversation = "false",
	options = {
		--{"@conversation/junk_lila_borvo:s_1875d09c", "start_sale"}, -- I believe that I have just what your employer is looking for.
		--{"@conversation/junk_lila_borvo:s_e8b03c7c", "no_loot"}, -- This seems a little shady. I don't think I want to be involved.
	}
}
junkDealerLilaConvoTemplate:addScreen(ask_for_loot);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_lila_borvo:s_a83a2e6b", -- How sweet. Aren't you just the little hero.
	stopConversation = "true",
	options = {}
}
junkDealerLilaConvoTemplate:addScreen(no_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_lila_borvo:s_7edb783c", -- Why don't you let me take a look at what you have to offer. If the goods are what my employer is after I am more then willing to take them off of your hands. Of course you understand that this deal is strictly confidential. If you break that confidence you will not live long enough to regret it.
	stopConversation = "true",
	options = {}
}
junkDealerLilaConvoTemplate:addScreen(start_sale);

addConversationTemplate("junkDealerLilaConvoTemplate", junkDealerLilaConvoTemplate);
