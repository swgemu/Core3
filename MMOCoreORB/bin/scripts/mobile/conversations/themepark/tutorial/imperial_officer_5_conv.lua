imperial_officer_5_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "imperial_officer_5_handler",
	screens = {}
}

imperial_officer_5_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:mission_1_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:mission_1_reply_1", "convoscreen2"},
		{"@newbie_tutorial/newbie_convo:mission_1_reply_2", "convoscreen2"},
	}
}

imperial_officer_5_convotemplate:addScreen(imperial_officer_5_convoscreen1);

imperial_officer_5_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:mission_1_waypoint",
	stopConversation = "true",
	options = {
	}
}

imperial_officer_5_convotemplate:addScreen(imperial_officer_5_convoscreen2);

imperial_officer_5_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:mission_repeat",
	stopConversation = "true",
	options = {
	}
}

imperial_officer_5_convotemplate:addScreen(imperial_officer_5_convoscreen3);

imperial_officer_5_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@newbie_tutorial/newbie_convo:trainer_grunt",
	stopConversation = "true",
	options = {
	}
}

imperial_officer_5_convotemplate:addScreen(imperial_officer_5_convoscreen4);

addConversationTemplate("imperial_officer_5_convotemplate", imperial_officer_5_convotemplate);
