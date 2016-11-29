junkDealerOlloboConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerOlloboConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_ollobo_jabbas:s_6d35d0e1", -- If yer lookin' ta get into mighty Jabba's good graces then Ollobo wrong chap ta talk at. If'n yer lookin' ta make extra credit or two mayhaps we make good deal.
	stopConversation = "false",
	options = {
		{"@conversation/junk_ollobo_jabbas:s_6ee477c3", "ask_for_loot"}, -- What sort of deal are you talking about?
		{"@conversation/junk_ollobo_jabbas:s_aadc214b", "yer_choice"}, -- I am not interested in any sort of deal.
	}
}
junkDealerOlloboConvoTemplate:addScreen(init);

yer_choice = ConvoScreen:new {
	id = "yer_choice",
	leftDialog = "@conversation/junk_ollobo_jabbas:s_935bfcd0", -- That yer choice. Just ya 'member, Ollobo willing ta deal fer what Jabba wants.
	stopConversation = "true",
	options = {}
}
junkDealerOlloboConvoTemplate:addScreen(yer_choice);

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_ollobo_jabbas:s_472f3294", -- Jabba tell Ollobo ta deal fer shooters an' stabbers, Jabba tell Ollobo ta deal fer pretties. Jabba tell Ollobo ta make good deal fer pistol shooters an' polearm stabbers. If'n ya got what Jabba wants, Ollobo deal fer it.
	stopConversation = "false",
	options = {
		--{"@conversation/junk_ollobo_jabbas:s_e2ee167d", "start_sale"}, -- I think that I have what Jabba is looking for.
		--{"@conversation/junk_ollobo_jabbas:s_b85badf5", "no_loot"}, -- I don't think that I have anything Jabba is interested in.
	}
}
junkDealerOlloboConvoTemplate:addScreen(ask_for_loot);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_ollobo_jabbas:s_b950c3eb", -- Ya 'member that Ollobo here. Ya find what Jabba wants, Ollobo deal fer it.
	stopConversation = "true",
	options = {}
}
junkDealerOlloboConvoTemplate:addScreen(no_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_ollobo_jabbas:s_73b59dd6", -- Ollobo check what ya got. No barter. Ya deal or not deal. Ollobo no ask questions, 'cause Ollobo no care. Jabba tell Ollobo ta deal, Ollobo deal.
	stopConversation = "true",
	options = {}
}
junkDealerOlloboConvoTemplate:addScreen(start_sale);

addConversationTemplate("junkDealerOlloboConvoTemplate", junkDealerOlloboConvoTemplate);
