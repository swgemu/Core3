g12_4j_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "death_watch_g12_4j_handler",
	screens = {}
}

g12_4j_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_medical_droid:s_22f2cc9b", 
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_medical_droid:s_82d3782a", "convoscreen2"},
	}
}

g12_4j_convotemplate:addScreen(g12_4j_convoscreen1);

g12_4j_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/death_watch_medical_droid:s_52a263b9", 
	stopConversation = "true",
	options = {
	}
}

g12_4j_convotemplate:addScreen(g12_4j_convoscreen2);

g12_4j_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/death_watch_medical_droid:s_22f2cc9b", 
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_medical_droid:s_ab36bcfc", "convoscreen4"},
	}
}

g12_4j_convotemplate:addScreen(g12_4j_convoscreen3);

g12_4j_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@conversation/death_watch_medical_droid:s_6a6a070d", 
	stopConversation = "true",
	options = {
	}
}

g12_4j_convotemplate:addScreen(g12_4j_convoscreen4);

g12_4j_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@conversation/death_watch_medical_droid:s_46d286cc", 
	stopConversation = "true",
	options = {
	}
}

g12_4j_convotemplate:addScreen(g12_4j_convoscreen5);

addConversationTemplate("g12_4j_convotemplate", g12_4j_convotemplate);
