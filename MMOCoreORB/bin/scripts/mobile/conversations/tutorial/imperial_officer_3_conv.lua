imperial_officer_3_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "imperial_officer_3_handler",
	screens = {}
}

imperial_officer_3_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_4_reply_1", "convoscreen2"},
		{"@newbie_tutorial/newbie_convo:convo_4_reply_2", "convoscreen4"},
	}
}

imperial_officer_3_convotemplate:addScreen(imperial_officer_3_convoscreen1);

imperial_officer_3_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_explain_1",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_4_reply_3", "convoscreen3"},
		{"@newbie_tutorial/newbie_convo:convo_4_reply_4", "convoscreen5"},
	}
}

imperial_officer_3_convotemplate:addScreen(imperial_officer_3_convoscreen2);

imperial_officer_3_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_explain_3",
	stopConversation = "false",
	options = {
	{"@newbie_tutorial/newbie_convo:convo_4_reply_5", "convoscreen5"},
	}
}

imperial_officer_3_convotemplate:addScreen(imperial_officer_3_convoscreen3);

imperial_officer_3_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_explain_2",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_4_reply_5", "convoscreen5"},
		{"@newbie_tutorial/newbie_convo:convo_4_reply_6", "convoscreen5"},
	}
}

imperial_officer_3_convotemplate:addScreen(imperial_officer_3_convoscreen4);

imperial_officer_3_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_weapon_1",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_4_reply_7", "convoscreen6"},
	}
}

imperial_officer_3_convotemplate:addScreen(imperial_officer_3_convoscreen5);

imperial_officer_3_convoscreen6 = ConvoScreen:new {
	id = "convoscreen6",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_end",
	stopConversation = "true",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_4_reply_7", "convoscreen6"},
	}
}

imperial_officer_3_convotemplate:addScreen(imperial_officer_3_convoscreen6);

imperial_officer_3_convo_altscreen1 = ConvoScreen:new {
	id = "altscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_repeat",
	stopConversation = "true",
	options = {
	}
}

imperial_officer_3_convotemplate:addScreen(imperial_officer_3_convo_altscreen1);

imperial_officer_3_convo_altscreen2 = ConvoScreen:new {
	id = "altscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:good_job",
	stopConversation = "true",
	options = {
	}
}

imperial_officer_3_convotemplate:addScreen(imperial_officer_3_convo_altscreen2);

addConversationTemplate("imperial_officer_3_convotemplate", imperial_officer_3_convotemplate);
