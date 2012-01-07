imperial_officer_2_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	screens = {}
}

imperial_officer_2_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_1_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_1_reply_1", "convoscreen2"},
		{"@newbie_tutorial/newbie_convo:banker_1_reply_2", "convoscreen6"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen1);

imperial_officer_2_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_2_reply_1", "convoscreen3"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen2);

imperial_officer_2_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_more",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_2_reply_2", "convoscreen4"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen3);

imperial_officer_2_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_2_reply_3", "convoscreen5"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen4);

imperial_officer_2_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain_2",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_1_reply_2", "convoscreen6"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen5);

imperial_officer_2_convoscreen6 = ConvoScreen:new {
	id = "convoscreen6",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain_terminals",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_1_reply_3", "convoscreen7"},
		{"@newbie_tutorial/newbie_convo:banker_1_reply_4", "convoscreen11"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen6);

imperial_officer_2_convoscreen7 = ConvoScreen:new {
	id = "convoscreen7",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain_bank",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_bank_reply_1", "convoscreen8"},
		{"@newbie_tutorial/newbie_convo:banker_2_bank_question", "convoscreen9"},
		{"@newbie_tutorial/newbie_convo:banker_bank_question_2", "convoscreen10"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen7);

imperial_officer_2_convoscreen8 = ConvoScreen:new {
	id = "convoscreen8",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_more_bank",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_2_bank_question", "convoscreen9"},
		{"@newbie_tutorial/newbie_convo:banker_bank_question_2", "convoscreen10"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen8);

imperial_officer_2_convoscreen9 = ConvoScreen:new {
	id = "convoscreen9",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_2_bank_answer",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_bank_reply_1", "convoscreen8"},
		{"@newbie_tutorial/newbie_convo:banker_bank_question_2", "convoscreen10"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen9);

imperial_officer_2_convoscreen10 = ConvoScreen:new {
	id = "convoscreen10",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_bank_answer_2",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_bank_reply_1", "convoscreen8"},
		{"@newbie_tutorial/newbie_convo:banker_2_bank_question", "convoscreen9"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen10);

imperial_officer_2_convoscreen11 = ConvoScreen:new {
	id = "convoscreen11",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_1",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_bazaar_reply_1", "convoscreen12"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen11);

imperial_officer_2_convoscreen12 = ConvoScreen:new {
	id = "convoscreen12",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_2",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_bazaar_reply_2", "convoscreen13"},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen12);

imperial_officer_2_convoscreen13 = ConvoScreen:new {
	id = "convoscreen13",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_3",
	stopConversation = "false",
	options = {
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen13);

addConversationTemplate("imperial_officer_2_convotemplate", imperial_officer_2_convotemplate);
