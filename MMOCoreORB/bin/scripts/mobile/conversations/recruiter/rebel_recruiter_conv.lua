rebel_recruiter_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	screens = {}
}

rebel_recruiter_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/faction_recruiter_rebel:s_566",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_580", "convoscreen2"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_convoscreen1);

rebel_recruiter_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/faction_recruiter_rebel:s_584",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_586", "convoscreen3"},
		{"@conversation/faction_recruiter_rebel:s_592", "convoscreen4"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_convoscreen2);

rebel_recruiter_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/faction_recruiter_rebel:s_588",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_590", ""},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_convoscreen3);

rebel_recruiter_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@conversation/faction_recruiter_rebel:s_594",
	stopConversation = "false",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_convoscreen4);

rebel_recruiter_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@conversation/faction_recruiter_rebel:s_448",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_450", "convoscreen6"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_convoscreen5);

rebel_recruiter_convoscreen6 = ConvoScreen:new {
	id = "convoscreen6",
	leftDialog = "@conversation/faction_recruiter_rebel:s_452",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_454", "convoscreen7"},
		{"@conversation/faction_recruiter_rebel:s_458", "convoscreen8"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_convoscreen6);

rebel_recruiter_convoscreen7 = ConvoScreen:new {
	id = "convoscreen7",
	leftDialog = "@conversation/faction_recruiter_rebel:s_456",
	stopConversation = "false",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_convoscreen7);

rebel_recruiter_convoscreen8 = ConvoScreen:new {
	id = "convoscreen8",
	leftDialog = "@conversation/faction_recruiter_rebel:s_460",
	stopConversation = "false",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_convoscreen8);

addConversationTemplate("rebel_recruiter_convotemplate", rebel_recruiter_convotemplate);
