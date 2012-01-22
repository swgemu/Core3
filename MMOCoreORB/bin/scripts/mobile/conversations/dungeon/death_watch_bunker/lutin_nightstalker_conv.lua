lutin_nightstalker_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "lutin_nightstalker_handler",
	screens = {}
}

lutin_nightstalker_notaligned = ConvoScreen:new {
	id = "notaligned",
	leftDialog = "@conversation/death_watch_rebel_herald:s_95369855", --Hmm... you dont seem to be one of us
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_notaligned);

lutin_nightstalker_busy = ConvoScreen:new {
	id = "busy",
	leftDialog = "@conversation/death_watch_rebel_herald:s_91db32fc", --I can't speak right now. ...
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_busy);

lutin_nightstalker_return_successful = ConvoScreen:new {
	id = "return_successful",
	leftDialog = "@conversation/death_watch_rebel_herald:s_8361bfd1", --You have returned! Were you successful?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_9b06da0", "finish"}, --Yes, I've...
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_return_successful);

lutin_nightstalker_finish = ConvoScreen:new {
	id = "finish",
	leftDialog = "@conversation/death_watch_rebel_herald:s_37b46abd", --Excellent! Your reward...
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_finish);

lutin_nightstalker_return_unsuccessful = ConvoScreen:new {
	id = "return_unsuccessful",
	leftDialog = "@conversation/death_watch_rebel_herald:s_8361bfd1", --You have returned! Were you successful?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_28f5f7c5", "repeat_location"}, --Where is the hideout again?
		{"@conversation/death_watch_rebel_herald:s_dc839e59", "incomplete"}, --Still looking
		{"@conversation/death_watch_rebel_herald:s_f70821a3", "quit"}, --I quit
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_return_unsuccessful);

lutin_nightstalker_repeat_location = ConvoScreen:new {
	id = "repeat_location",
	leftDialog = "@conversation/death_watch_rebel_herald:s_2d06d9f7", --The Death Watch Operatives...
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_repeat_location);

lutin_nightstalker_incomplete = ConvoScreen:new {
	id = "incomplete",
	leftDialog = "@conversation/death_watch_rebel_herald:s_e99ef1de", --I see. Please... 
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_incomplete);

lutin_nightstalker_quit = ConvoScreen:new {
	id = "quit",
	leftDialog = "@conversation/death_watch_rebel_herald:s_88a6fa7d", --This distresses me.  
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_quit);

lutin_nightstalker_return_after_finished = ConvoScreen:new {
	id = "return_after_finished",
	leftDialog = "@conversation/death_watch_rebel_herald:s_65aa1cd5", --Thank you for your help earlier!
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_c1c188ab", "maytheforce"}, --No problem. bye!
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_return_after_finished);

lutin_nightstalker_maytheforce = ConvoScreen:new {
	id = "maytheforce",
	leftDialog = "@conversation/death_watch_rebel_herald:s_2d4bb338", --May the Force be with you!
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_maytheforce);

lutin_nightstalker_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_rebel_herald:s_bfe5e691", --Finally...
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_a0822589", "convoscreen2"}, --Uh, what?
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_convoscreen1);

lutin_nightstalker_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/death_watch_rebel_herald:s_940cb841", --Haven't you heard?
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_62104343", "convoscreen3"}, --Slow down...
		{"@conversation/death_watch_rebel_herald:s_823eed0c", "excellent"}, --Yes I will
		{"@conversation/death_watch_rebel_herald:s_938e28a4", "pity"}, --No I can't
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_convoscreen2);

lutin_nightstalker_excellent = ConvoScreen:new {
	id = "excellent",
	leftDialog = "@conversation/death_watch_rebel_herald:s_f4474b2c", --Excellent
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_excellent);

lutin_nightstalker_pity = ConvoScreen:new {
	id = "pity",
	leftDialog = "@conversation/death_watch_rebel_herald:s_afdd35a1", --Pity...
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_pity);

lutin_nightstalker_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/death_watch_rebel_herald:s_aa852a2c", --One of our ...
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_6f2c6f44", "convoscreen4"}, --More Information
		{"@conversation/death_watch_rebel_herald:s_5c3cdba4", "location"}, --Yes
		{"@conversation/death_watch_rebel_herald:s_4f240e90", "pity"}, --No
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_convoscreen3);

lutin_nightstalker_location = ConvoScreen:new {
	id = "location",
	leftDialog = "@conversation/death_watch_rebel_herald:s_7089401b", --The hideout is...
	stopConversation = "true",
	options = {
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_location);

lutin_nightstalker_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@conversation/death_watch_rebel_herald:s_37890704", --Very well, a reasonable...
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_rebel_herald:s_5c3cdba4", "maytheforce"}, --Yes
		{"@conversation/death_watch_rebel_herald:s_4f240e90", "pity"}, --No
	}
}

lutin_nightstalker_convotemplate:addScreen(lutin_nightstalker_convoscreen4);

addConversationTemplate("lutin_nightstalker_convotemplate", lutin_nightstalker_convotemplate);
