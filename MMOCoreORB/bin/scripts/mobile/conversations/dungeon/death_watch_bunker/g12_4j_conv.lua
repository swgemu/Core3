g12_4j_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	--luaClassHandler = "g12_4j_handler",
	screens = {}
}

g12_4j_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_medical_droid:s_22f2cc9b", 
	stopConversation = "true",
	options = {
		--{"@conversation/g12_4j:s_ab11aabd", "convoscreen2"}, --Okay. Anything else you can tell me?
	}
}

g12_4j_convotemplate:addScreen(g12_4j_convoscreen1);

addConversationTemplate("g12_4j_convotemplate", g12_4j_convotemplate);
