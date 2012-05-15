imperial_officer_4_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	screens = {}
}

imperial_officer_4_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:off_1_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:off_1_reply_1", "convoscreen2"},
		{"@newbie_tutorial/newbie_convo:off_1_reply_2", "convoscreen3"},
	}
}

imperial_officer_4_convotemplate:addScreen(imperial_officer_4_convoscreen1);

imperial_officer_4_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:off_1_gotrain",
	stopConversation = "true",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_2_reply_1", "convoscreen1"},
	}
}

imperial_officer_4_convotemplate:addScreen(imperial_officer_4_convoscreen2);

imperial_officer_4_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:off_1_gotrain2",
	stopConversation = "true",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_2_reply_2", "convoscreen1"},
	}
}

imperial_officer_4_convotemplate:addScreen(imperial_officer_4_convoscreen3);

addConversationTemplate("imperial_officer_4_convotemplate", imperial_officer_4_convotemplate);
