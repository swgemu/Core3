biogenic_construction_ConversationTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicConstructionConvoHandler",
	screens = {}
}

intro_assistant_done = ConvoScreen:new {
	id = "intro_assistant_done",
	leftDialog = "@conversation/biogenic_construction:s_575de8f1", -- Thanks again for killing those spiders. I'm getting out of here as soon as the way is clear.
	stopConversation = "false",
	options = {}
}
biogenic_construction_ConversationTemplate:addScreen(intro_assistant_done);

intro_check_engineering = ConvoScreen:new {
	id = "intro_check_engineering",
	leftDialog = "@conversation/biogenic_construction:s_dc2d689c", -- Thanks again for killing those spiders. If you need to get to the engineering area, the code 51892 will get you in.
	stopConversation = "false",
	options = {}
}
biogenic_construction_ConversationTemplate:addScreen(intro_check_engineering);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/biogenic_construction:s_1df6adfc", -- Thank goodness you got here in time! That spider was going to kill me. I thought for sure I was a goner. How can I ever repay you?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_e4b06f76","get_wits_back"}, -- There's no need. I'm glad you're alright.
		{"@conversation/biogenic_construction:s_355bc632","dont_have_much"}, -- I'm sure you'll think of some way.
		{"@conversation/biogenic_construction:s_355bc632","excavating_passage"}, -- What were you doing in here anyway?
		{"@conversation/biogenic_construction:s_457410bd","getting_out_too"} -- No problem. Good-bye.
	}
}
biogenic_construction_ConversationTemplate:addScreen(intro);

get_wits_back = ConvoScreen:new {
	id = "get_wits_back",
	leftDialog = "@conversation/biogenic_construction:s_fc129e0e", -- Well I'm only interested in getting out of here now.  I'll do that as soon as I get my wits back.
	stopConversation = "false",
	options = {
		--{"@conversation/biogenic_construction:s_5fe23666","bye_good_luck"}, -- OK. Good-bye then.
	}
}
biogenic_construction_ConversationTemplate:addScreen(get_wits_back);

dont_have_much = ConvoScreen:new {
	id = "dont_have_much",
	leftDialog = "@conversation/biogenic_construction:s_eb771a95", -- Actually, I don't have much to give you. Perhaps I'll think of something later.
	stopConversation = "false",
	options = {
		--{"@conversation/biogenic_construction:s_5fe23666","bye_good_luck"}, -- OK. Good-bye then.
	}
}
biogenic_construction_ConversationTemplate:addScreen(dont_have_much);

excavating_passage = ConvoScreen:new {
	id = "excavating_passage",
	leftDialog = "@conversation/biogenic_construction:s_75118515", -- I was working on excavating this passage when the earthquake hit. Not long after, the spiders attacked. Now I just want to get out of here. 
	stopConversation = "false",
	options = {
		--{"@conversation/biogenic_construction:s_5fe23666","bye_good_luck"}, -- OK. Good-bye then.
	}
}
biogenic_construction_ConversationTemplate:addScreen(excavating_passage);

getting_out_too = ConvoScreen:new {
	id = "getting_out_too",
	leftDialog = "@conversation/biogenic_construction:s_c30b797d", -- Yea, I'm getting out of here too.
	stopConversation = "false",
	options = {
		--{"@conversation/biogenic_construction:s_5fe23666","bye_good_luck"}, -- OK. Good-bye then.
	}
}
biogenic_construction_ConversationTemplate:addScreen(getting_out_too);

bye_good_luck = ConvoScreen:new {
	id = "bye_good_luck",
	leftDialog = "@conversation/biogenic_construction:s_c1d58076", -- Good-bye, and good luck!
	stopConversation = "false",
	options = {}
}
biogenic_construction_ConversationTemplate:addScreen(bye_good_luck);

bye_check_engineering = ConvoScreen:new {
	id = "bye_check_engineering",
	leftDialog = "@conversation/biogenic_construction:s_67f9970", -- If you have a chance, you might want to go check out the main engineering area. It looks like the power core might be damaged or offline. If the door is locked, the code 51892 will get you in. Good-bye, and good luck!
	stopConversation = "false",
	options = {}
}
biogenic_construction_ConversationTemplate:addScreen(bye_check_engineering);

addConversationTemplate("biogenic_construction_ConversationTemplate", biogenic_construction_ConversationTemplate);


