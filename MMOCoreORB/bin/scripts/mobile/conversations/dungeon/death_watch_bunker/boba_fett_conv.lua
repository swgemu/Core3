boba_fett_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "boba_fett_handler",
	screens = {}
}

boba_fett_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/boba_fett:s_8e66f1ea", --Another of Jabba's little toys...
	stopConversation = "false",
	options = {
		{"@conversation/boba_fett:s_ab11aabd", "convoscreen2"}, --Okay. Anything else you can tell me?
	}
}

boba_fett_convotemplate:addScreen(boba_fett_convoscreen1);

boba_fett_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/boba_fett:s_d586da5f", --The Death Watch can be...
	stopConversation = "false",
	options = {
		{"@conversation/boba_fett:s_f215b084", "convoscreen3"}, --Sounds like you've...
		{"@conversation/boba_fett:s_783590a2", "convoscreen5"}, --Do I get a reward...
	}
}

boba_fett_convotemplate:addScreen(boba_fett_convoscreen2);

boba_fett_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/boba_fett:s_58de331a", --Mind your business...
	stopConversation = "false",
	options = {
			{"@conversation/boba_fett:s_4c801419", "convoscreen4"}, --Are you sure that's all...
	}
}

boba_fett_convotemplate:addScreen(boba_fett_convoscreen3);

boba_fett_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@conversation/boba_fett:s_262c1b3f", --I dont usually...
	stopConversation = "true",
	options = {
	}
}

boba_fett_convotemplate:addScreen(boba_fett_convoscreen4);

boba_fett_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@conversation/boba_fett:s_f959107f",--the experience itself
	stopConversation = "true",
	options = {
	}
}

boba_fett_convotemplate:addScreen(boba_fett_convoscreen5);

boba_fett_convoscreen6 = ConvoScreen:new {
	id = "convoscreen6",
	leftDialog = "@conversation/boba_fett:s_3c8497c", -- you're back?
	stopConversation = "false",
	options = {
		{"@conversation/boba_fett:s_1122d80a", "convoscreen1"},--can you tell me again?
		{"@conversation/boba_fett:s_515da73f", "convoscreen7"},--cant somebody else do it?
	}
}

boba_fett_convotemplate:addScreen(boba_fett_convoscreen6);

boba_fett_convoscreen7 = ConvoScreen:new {
	id = "convoscreen7",
	leftDialog = "@conversation/boba_fett:s_6ad7d226",--You won't make any friends...
	stopConversation = "true",
	options = {
	}
}

boba_fett_convotemplate:addScreen(boba_fett_convoscreen7);

boba_fett_convoscreen8 = ConvoScreen:new {
	id = "convoscreen8",
	leftDialog = "@conversation/boba_fett:s_4386e081",--Go away
	stopConversation = "true",
	options = {
	}
}

boba_fett_convotemplate:addScreen(boba_fett_convoscreen8);

addConversationTemplate("boba_fett_convotemplate", boba_fett_convotemplate);
