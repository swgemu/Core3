protocol_droid_tutorial_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	screens = {}
}

protocol_droid_tutorial_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_1", "convoscreen2"},--Cloning
		{"@newbie_tutorial/newbie_convo:convo_2_reply_2", "convoscreen4"},--Insurance
	}
}

protocol_droid_tutorial_convotemplate:addScreen(protocol_droid_tutorial_convoscreen1);

protocol_droid_tutorial_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_cloning",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_3", "convoscreen3"},
	}
}

protocol_droid_tutorial_convotemplate:addScreen(protocol_droid_tutorial_convoscreen2);

protocol_droid_tutorial_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_cloning_2",
	stopConversation = "false",
	options = {
	{"@newbie_tutorial/newbie_convo:convo_2_reply_5", "convoscreen5"},
	}
}

protocol_droid_tutorial_convotemplate:addScreen(protocol_droid_tutorial_convoscreen3);

protocol_droid_tutorial_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_insurance",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_4", "convoscreen6"},
	}
}

protocol_droid_tutorial_convotemplate:addScreen(protocol_droid_tutorial_convoscreen4);

protocol_droid_tutorial_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_cloning_3",
	stopConversation = "false",
	options = {
		{"@skill_teacher:back", "convoscreen1"},
	}
}

protocol_droid_tutorial_convotemplate:addScreen(protocol_droid_tutorial_convoscreen5);

protocol_droid_tutorial_convoscreen6 = ConvoScreen:new {
	id = "convoscreen6",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_insurance_2",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_8", "convoscreen7"},
	}
}

protocol_droid_tutorial_convotemplate:addScreen(protocol_droid_tutorial_convoscreen6);

protocol_droid_tutorial_convoscreen7 = ConvoScreen:new {
	id = "convoscreen7",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_insurance_5",
	stopConversation = "false",
	options = {
		{"@skill_teacher:back", "convoscreen1"},
	}
}

protocol_droid_tutorial_convotemplate:addScreen(protocol_droid_tutorial_convoscreen7);

addConversationTemplate("protocol_droid_tutorial_convotemplate", protocol_droid_tutorial_convotemplate);
