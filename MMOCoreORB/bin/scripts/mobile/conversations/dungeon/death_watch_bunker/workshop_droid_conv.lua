workshop_droid_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "death_watch_workshop_droid_handler",
	screens = {}
}


workshop_droid_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_treadwell:s_9208410d",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_treadwell:s_8e9e4ef9", "convoscreen2"},
	}
}

workshop_droid_convotemplate:addScreen(workshop_droid_convoscreen1);

workshop_droid_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/death_watch_treadwell:s_9208410d",
	stopConversation = "true",
	options = {
	}
}

workshop_droid_convotemplate:addScreen(workshop_droid_convoscreen2);

workshop_droid_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/death_watch_treadwell:s_9208410d",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_treadwell:s_4fcd015f", "convoscreen4"},
	}
}

workshop_droid_convotemplate:addScreen(workshop_droid_convoscreen3);

workshop_droid_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@conversation/death_watch_treadwell:s_9208410d",
	stopConversation = "true",
	options = {
	}
}

workshop_droid_convotemplate:addScreen(workshop_droid_convoscreen4);

addConversationTemplate("workshop_droid_convotemplate", workshop_droid_convotemplate);