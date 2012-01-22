imperial_officer_6_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "imperial_officer_6_handler",
	screens = {}
}

imperial_officer_6_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:quarter_1_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:quarter_1_reply_1", "convoscreen2"},
		{"@newbie_tutorial/newbie_convo:quarter_1_reply_2", "convoscreen2"},
	}
}

imperial_officer_6_convotemplate:addScreen(imperial_officer_6_convoscreen1);

imperial_officer_6_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:quarter_1_go",
	stopConversation = "true",
	options = {
	}
}

imperial_officer_6_convotemplate:addScreen(imperial_officer_6_convoscreen2);

imperial_officer_6_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:quarter_nodocs",
	stopConversation = "true",
	options = {
	}
}

imperial_officer_6_convotemplate:addScreen(imperial_officer_6_convoscreen3);

addConversationTemplate("imperial_officer_6_convotemplate", imperial_officer_6_convotemplate);
