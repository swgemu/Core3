reelo_baruk_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	screens = {}
}

reelo_baruk_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_start",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_1_reply_1", "convoscreen2"},
	}
}

reelo_baruk_convotemplate:addScreen(reelo_baruk_convoscreen1);

reelo_baruk_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_more",
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_1_reply_3", "convoscreen3"},
	}
}

reelo_baruk_convotemplate:addScreen(reelo_baruk_convoscreen2);

reelo_baruk_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_explain",
	stopConversation = "false",
	options = {
			{"@newbie_tutorial/newbie_convo:convo_1_reply_2", "convoscreen4"},
	}
}

reelo_baruk_convotemplate:addScreen(reelo_baruk_convoscreen3);

reelo_baruk_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_stuff",
	stopConversation = "false",
	options = {
	}
}

reelo_baruk_convotemplate:addScreen(reelo_baruk_convoscreen4);

addConversationTemplate("reelo_baruk_convotemplate", reelo_baruk_convotemplate);
