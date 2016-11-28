junkDealerQuichConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "JunkDealerQuichConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/junk_quich_dantooine:s_87c4b1c3", -- Lookie lookie what I see here. Ye certainly be a brave sort. The type that be trying to make a name for ye. Perhaps I be able to help ye make that name?
	stopConversation = "false",
	options = {
		{"@conversation/junk_quich_dantooine:s_2313ac9e", "artifacts"}, -- What are you talking about?
		{"@conversation/junk_quich_dantooine:s_953d967f", "bye"}, -- Ummm...I think you have me confused for someone else.
	}
}
junkDealerQuichConvoTemplate:addScreen(init);

bye = ConvoScreen:new {
	id = "bye",
	leftDialog = "@conversation/junk_quich_dantooine:s_35b56f0a", -- Oh, well have I now. In that case ye should go about ye business.
	stopConversation = "true",
	options = {}
}
junkDealerQuichConvoTemplate:addScreen(bye);

artifacts = ConvoScreen:new {
	id = "artifacts",
	leftDialog = "@conversation/junk_quich_dantooine:s_86df00aa", -- I have ye curious now. I be looking for rare artifacts of the mysterious nature. Artifacts that this planet have in abundance. Artifacts of jedi.
	stopConversation = "false",
	options = {
		{"@conversation/junk_quich_dantooine:s_f2e88b32", "ask_for_loot"}, -- Jedi eh? And I suppose you will pay for these artifacts?
		{"@conversation/junk_quich_dantooine:s_fbe44b83", "wise"}, -- Jedi! I want nothing to do with anything Jedi.
	}
}
junkDealerQuichConvoTemplate:addScreen(artifacts);

wise = ConvoScreen:new {
	id = "wise",
	leftDialog = "@conversation/junk_quich_dantooine:s_f5349262", -- Ye be wise beyond ye years for making that decision. I be wrong in thinking that ye could hold ye own with the likes of Jedi.
	stopConversation = "true",
	options = {}
}
junkDealerQuichConvoTemplate:addScreen(wise);

ask_for_loot = ConvoScreen:new {
	id = "ask_for_loot",
	leftDialog = "@conversation/junk_quich_dantooine:s_5bc0c939", -- Pay and pay well. I be working for a collector who has credits to spend. Ye get me artifacts and I get ye credits.
	stopConversation = "false",
	options = {
		--{"@conversation/junk_quich_dantooine:s_463bc6c4", "start_sale"}, -- I just might have some things you would be interested in.
		--{"@conversation/junk_quich_dantooine:s_6e11f342", "no_loot"}, -- I don't have anything you would be interested in.
	}
}
junkDealerQuichConvoTemplate:addScreen(ask_for_loot);

no_loot = ConvoScreen:new {
	id = "no_loot",
	leftDialog = "@conversation/junk_quich_dantooine:s_413bfd08", -- Well if ye find any Jedi artifacts ye know where I be.
	stopConversation = "true",
	options = {}
}
junkDealerQuichConvoTemplate:addScreen(no_loot);

start_sale = ConvoScreen:new {
	id = "start_sale",
	leftDialog = "@conversation/junk_quich_dantooine:s_ba5cc7c", -- Excellent. Let me look at what ye got for me. How nice...how nice indeed. I will make an offer on these. Ye should take me up on my offer because no one else will pay for what ye got.
	stopConversation = "true",
	options = {}
}
junkDealerQuichConvoTemplate:addScreen(start_sale);

addConversationTemplate("junkDealerQuichConvoTemplate", junkDealerQuichConvoTemplate);
