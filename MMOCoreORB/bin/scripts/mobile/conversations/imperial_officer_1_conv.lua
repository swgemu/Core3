imperial_officer_1_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	screens = {}
}

imperial_officer_1_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_1_reply_1", "convoscreen2"},
		{"@newbie_tutorial/newbie_convo:convo_1_reply_2", "convoscreen4"},
	}
}

imperial_officer_1_convotemplate:addScreen(imperial_officer_1_convoscreen1);

imperial_officer_1_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_more",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_1_reply_3", "convoscreen3"},
	}
}

imperial_officer_1_convotemplate:addScreen(imperial_officer_1_convoscreen2);

imperial_officer_1_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_explain",
	stopConversation = "false",
	options = {
	}
}

imperial_officer_1_convotemplate:addScreen(imperial_officer_1_convoscreen3);

imperial_officer_1_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_stuff",
	stopConversation = "false",
	options = {
	}
}

imperial_officer_1_convotemplate:addScreen(imperial_officer_1_convoscreen4);

addConversationTemplate("imperial_officer_1_convotemplate", imperial_officer_1_convotemplate);
