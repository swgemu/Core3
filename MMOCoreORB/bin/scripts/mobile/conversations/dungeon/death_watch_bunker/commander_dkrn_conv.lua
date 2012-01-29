commander_dkrn_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "commander_dkrn_handler",
	screens = {}
}

commander_dkrn_notaligned = ConvoScreen:new {
	id = "notaligned",
	leftDialog = "@conversation/death_watch_imperial_herald:s_d441c51a", --Hmm... you dont seem to be one of us
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_notaligned);

commander_dkrn_busy = ConvoScreen:new {
	id = "busy",
	leftDialog = "@conversation/death_watch_imperial_herald:s_2e8ff1b4", --I can't speak right now. ...
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_busy);

commander_dkrn_return_successful = ConvoScreen:new {
	id = "return_successful",
	leftDialog = "@conversation/death_watch_imperial_herald:s_1a897bb0", --You have returned! Were you successful?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_4f1e472e", "finish"}, --Yes, I've...
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_return_successful);

commander_dkrn_finish = ConvoScreen:new {
	id = "finish",
	leftDialog = "@conversation/death_watch_imperial_herald:s_2c258e47", --Excellent! Your reward...
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_finish);

commander_dkrn_return_unsuccessful = ConvoScreen:new {
	id = "return_unsuccessful",
	leftDialog = "@conversation/death_watch_imperial_herald:s_1a897bb0", --You have returned! Were you successful?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_55aa1278", "repeat_information"}, --Where is the hideout again?
		{"@conversation/death_watch_imperial_herald:s_dc839e59", "incomplete"}, --Still looking
		{"@conversation/death_watch_imperial_herald:s_f70821a3", "quit"}, --I quit
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_return_unsuccessful);

commander_dkrn_repeat_information = ConvoScreen:new {
	id = "repeat_information",
	leftDialog = "@conversation/death_watch_imperial_herald:s_622c3f31", --You have returned! Were you successful?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_5bc39fc9", "repeat_location"}, --Where is the hideout again?
		{"@conversation/death_watch_imperial_herald:s_dc839e59", "incomplete"}, --Still looking
		{"@conversation/death_watch_imperial_herald:s_f70821a3", "quit"}, --I quit
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_repeat_information);

commander_dkrn_repeat_location = ConvoScreen:new {
	id = "repeat_location",
	leftDialog = "@conversation/death_watch_imperial_herald:s_4e028860", --The Death Watch Operatives...
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_repeat_location);

commander_dkrn_incomplete = ConvoScreen:new {
	id = "incomplete",
	leftDialog = "@conversation/death_watch_imperial_herald:s_382404f", --I see. Please... 
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_incomplete);

commander_dkrn_quit = ConvoScreen:new {
	id = "quit",
	leftDialog = "@conversation/death_watch_imperial_herald:s_79b531ae", --This distresses me.  
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_quit);

commander_dkrn_return_after_finished = ConvoScreen:new {
	id = "return_after_finished",
	leftDialog = "@conversation/death_watch_imperial_herald:s_68732e54", --Thank you for your help earlier!
	stopConversation = "true",
	options = { 
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_return_after_finished);

commander_dkrn_more_samples = ConvoScreen:new {
	id = "more_samples",
	leftDialog = "@conversation/death_watch_imperial_herald:s_b2cb2cbf", --Thank you for your help earlier!
	stopConversation = "true",
	options = { 
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_more_samples);

commander_dkrn_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_imperial_herald:s_527f9e64", --Finally...
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_8107be6d", "pity"}, --No
		{"@conversation/death_watch_imperial_herald:s_210b4c5b", "rightaway"}, --Yes
		{"@conversation/death_watch_imperial_herald:s_ecc5dd3c", "convoscreen2"}, --Wait, what?
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_convoscreen1);

commander_dkrn_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/death_watch_imperial_herald:s_1b104a9f", --Haven't you heard?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_6decea2a", "excellent"}, --Yes I will
		{"@conversation/death_watch_imperial_herald:s_6405e2a0", "pity"}, --No I can't
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_convoscreen2);

commander_dkrn_excellent = ConvoScreen:new {
	id = "excellent",
	leftDialog = "@conversation/death_watch_imperial_herald:s_126d6e08", --Excellent
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_43908466", "convoscreen3"}, --Why
		{"@conversation/death_watch_imperial_herald:s_e62fc90c", "rightaway"}, --Yes
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_excellent);

commander_dkrn_rightaway = ConvoScreen:new {
	id = "rightaway",
	leftDialog = "@conversation/death_watch_imperial_herald:s_e478107c", --Excellent
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_rightaway);

commander_dkrn_pity = ConvoScreen:new {
	id = "pity",
	leftDialog = "@conversation/death_watch_imperial_herald:s_71f459c7", --Pity...
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_pity);

commander_dkrn_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/death_watch_imperial_herald:s_622c3f31", --One of our ...
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_imperial_herald:s_e62fc90c", "location"}, --Yes
		{"@conversation/death_watch_imperial_herald:s_f61ed984", "convoscreen4"}, --No
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_convoscreen3);

commander_dkrn_location = ConvoScreen:new {
	id = "location",
	leftDialog = "@conversation/death_watch_imperial_herald:s_732f795f", --The hideout is...
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_location);

commander_dkrn_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@conversation/death_watch_imperial_herald:s_2979d13", --Morals? Pah!
	stopConversation = "true",
	options = {
	}
}

commander_dkrn_convotemplate:addScreen(commander_dkrn_convoscreen4);

addConversationTemplate("commander_dkrn_convotemplate", commander_dkrn_convotemplate);
