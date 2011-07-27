imperial_officer_2_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	screens = {}
}

imperial_officer_2_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:banker_1_start",
	options = {
		{"@newbie_tutorial/newbie_convo:banker_1_reply_1", ""},
	}
}

imperial_officer_2_convotemplate:addScreen(imperial_officer_2_convoscreen1);

addConversationTemplate("imperial_officer_2_convotemplate", imperial_officer_2_convotemplate);