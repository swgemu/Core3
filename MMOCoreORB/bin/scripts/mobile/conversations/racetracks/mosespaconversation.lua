mosespa_conversationtemplate = ConvoTemplate:new {
	initialScreen = "mosespa_initial",
	templateType = "Lua",
	luaClassHandler = "mosespa_racetrack_convo_handler",
	screens = {}
}

mosespa_initial = ConvoScreen:new {
	id = "mosespa_initial",
	leftDialog = "@conversation/racing_mosespa:s_e0de16cc",
	stopConversation = "false",
	options = {
		{"@conversation/racing_mosespa:s_dffdee4b","cs_jsPlumb_1_90"},
		{"@conversation/racing_mosespa:s_1736e216","cs_jsPlumb_1_29"},
		{"@conversation/racing_mosespa:s_838e4ffb","cs_jsPlumb_1_181"},
		{"@conversation/racing_mosespa:s_2492930f","cs_jsPlumb_1_207"}
	}
}
mosespa_conversationtemplate:addScreen(mosespa_initial);
cs_jsPlumb_1_29 = ConvoScreen:new {
	id = "cs_jsPlumb_1_29",
	leftDialog = "@conversation/racing_mosespa:s_cea50112",
	stopConversation = "false",
	options = {
		{"@conversation/racing_mosespa:s_e460e3d3","cs_jsPlumb_1_233"},
		{"@conversation/racing_mosespa:s_fbd55d9d",""}
	}
}
mosespa_conversationtemplate:addScreen(cs_jsPlumb_1_29);
cs_jsPlumb_1_90 = ConvoScreen:new {
	id = "cs_jsPlumb_1_90",
	leftDialog = "@conversation/racing_mosespa:s_d24f3595",
	stopConversation = "false",
	options = {
		{"@conversation/racing_mosespa:s_2528fad7","cs_jsPlumb_1_116"},
		{"@conversation/racing_mosespa:s_262e8687","cs_jsPlumb_1_142"}
	}
}
mosespa_conversationtemplate:addScreen(cs_jsPlumb_1_90);
cs_jsPlumb_1_116 = ConvoScreen:new {
	id = "cs_jsPlumb_1_116",
	leftDialog = "@conversation/racing_mosespa:s_b2acc217",
	stopConversation = "true",
	options = {
	}
}
mosespa_conversationtemplate:addScreen(cs_jsPlumb_1_116);
cs_jsPlumb_1_142 = ConvoScreen:new {
	id = "cs_jsPlumb_1_142",
	leftDialog = "@conversation/racing_mosespa:s_c0918d6",
	stopConversation = "true",
	options = {
	}
}
mosespa_conversationtemplate:addScreen(cs_jsPlumb_1_142);
cs_jsPlumb_1_181 = ConvoScreen:new {
	id = "cs_jsPlumb_1_181",
	leftDialog = "@conversation/racing_mosespa:s_abd9745d",
	stopConversation = "true",
	options = {
	}
}
mosespa_conversationtemplate:addScreen(cs_jsPlumb_1_181);
cs_jsPlumb_1_207 = ConvoScreen:new {
	id = "cs_jsPlumb_1_207",
	leftDialog = "@conversation/racing_mosespa:s_abd9745d",
	stopConversation = "true",
	options = {
	}
}
mosespa_conversationtemplate:addScreen(cs_jsPlumb_1_207);
cs_jsPlumb_1_233 = ConvoScreen:new {
	id = "cs_jsPlumb_1_233",
	leftDialog = "@conversation/racing_mosespa:s_4b4fb2b7",
	stopConversation = "true",
	options = {
	}
}
mosespa_conversationtemplate:addScreen(cs_jsPlumb_1_233);
addConversationTemplate("mosespa_conversationtemplate", mosespa_conversationtemplate);