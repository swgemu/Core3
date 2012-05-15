insane_miner_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "death_watch_insane_miner_handler",
	screens = {}
}


insane_miner_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_insane_miner:s_21632dd",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_3fb7180e", "convoscreen2"},
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen1);

insane_miner_convoscreen8 = ConvoScreen:new {
	id = "convoscreen8",
	leftDialog = "@conversation/death_watch_insane_miner:s_21632dd",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_3fb7180e", "convoscreen9"},
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen8);

insane_miner_convoscreen9 = ConvoScreen:new {
	id = "convoscreen9",
	leftDialog = "@conversation/death_watch_insane_miner:s_87bb258b",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_42a2316b", "convoscreen7"},
		{"@conversation/death_watch_insane_miner:s_7c3e9069", "convoscreen2_2"},
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen9);

insane_miner_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/death_watch_insane_miner:s_87bb258b",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_16968d33", "convoscreen2_1"},
		{"@conversation/death_watch_insane_miner:s_4fe1bc67", "convoscreen2_2"},--killoption
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen2);

insane_miner_convoscreen2_1 = ConvoScreen:new {
	id = "convoscreen2_1",
	leftDialog = "@conversation/death_watch_insane_miner:s_2ff0df5",
	stopConversation = "true",
	options = {
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen2_1);

insane_miner_convoscreen2_2 = ConvoScreen:new {
	id = "convoscreen2_2",
	leftDialog = "@conversation/death_watch_insane_miner:s_99f3d3be",
	stopConversation = "true",
	options = {
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen2_2);

insane_miner_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/death_watch_insane_miner:s_87bb258b",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_dad50efa", "convoscreen4"},
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen3);

insane_miner_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@conversation/death_watch_insane_miner:s_ea390b92",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_829888a9", "convoscreen7"},
		{"@conversation/death_watch_insane_miner:s_7c3e9069", "convoscreen2_2"},--kill option
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen4);

insane_miner_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@conversation/death_watch_insane_miner:s_ce67a12e",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_7c83bd45", "convoscreen5_1"},
		{"@conversation/death_watch_insane_miner:s_7c3e9069", "convoscreen2_2"},
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen5);

insane_miner_convoscreen5_1 = ConvoScreen:new {
	id = "convoscreen5_1",
	leftDialog = "@conversation/death_watch_insane_miner:s_2efed805",
	stopConversation = "true",
	options = {
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen5_1);

insane_miner_convoscreen6 = ConvoScreen:new {
	id = "convoscreen6",
	leftDialog = "@conversation/death_watch_insane_miner:s_ce67a12e",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_insane_miner:s_42a2316b", "convoscreen7"},
		{"@conversation/death_watch_insane_miner:s_7c3e9069", "convoscreen2_2"},
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen6);

insane_miner_convoscreen7 = ConvoScreen:new {
	id = "convoscreen7",
	leftDialog = "@conversation/death_watch_insane_miner:s_e810685f",
	stopConversation = "true",
	options = {
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen7);

insane_miner_convoscreen8 = ConvoScreen:new {
	id = "convoscreen8",
	leftDialog = "@conversation/death_watch_insane_miner:s_c2b7bf76",
	stopConversation = "true",
	options = {
	}
}

insane_miner_convotemplate:addScreen(insane_miner_convoscreen8);

addConversationTemplate("insane_miner_convotemplate", insane_miner_convotemplate);