commoner_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "commoner_handler",
	screens = {}
}

commoner_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:mission_1_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:mission_1_reply_1", "convoscreen2"},
		{"@newbie_tutorial/newbie_convo:mission_1_reply_2", "convoscreen2"},
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen1);

commoner_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:mission_1_waypoint",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen2);

commoner_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:mission_repeat",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen3);

addConversationTemplate("commoner_convotemplate", commoner_convotemplate);
