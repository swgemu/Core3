
aaph_koden_convotemplate = ConvoTemplate:new {
	initialScreen = "cs_jsPlumb_1_1",
	templateType = "Normal",
	luaClassHandler = "",
	screens = {}
}
cs_jsPlumb_1_1 = ConvoScreen:new {
	id = "cs_jsPlumb_1_1",
	leftDialog = "@static_npc/tatooine/aaph_koden:npc_1_1",
	stopConversation = "false",
	options = {
		{"@static_npc/tatooine/aaph_koden:player_2_1","cs_jsPlumb_1_5"},
		{"@static_npc/tatooine/aaph_koden:player_1_3","cs_jsPlumb_1_9"}
	}
}
aaph_koden_convotemplate:addScreen(cs_jsPlumb_1_1);
cs_jsPlumb_1_5 = ConvoScreen:new {
	id = "cs_jsPlumb_1_5",
	leftDialog = "@static_npc/tatooine/aaph_koden:npc_reset_1",
	stopConversation = "true",
	options = {
	}
}
aaph_koden_convotemplate:addScreen(cs_jsPlumb_1_5);
cs_jsPlumb_1_9 = ConvoScreen:new {
	id = "cs_jsPlumb_1_9",
	leftDialog = "@static_npc/tatooine/aaph_koden:npc_2_1",
	stopConversation = "false",
	options = {
		{"@static_npc/tatooine/aaph_koden:player_3_1","cs_jsPlumb_1_13"}
	}
}
aaph_koden_convotemplate:addScreen(cs_jsPlumb_1_9);
cs_jsPlumb_1_13 = ConvoScreen:new {
	id = "cs_jsPlumb_1_13",
	leftDialog = "@static_npc/tatooine/aaph_koden:npc_4_1",
	stopConversation = "true",
	options = {
	}
}
aaph_koden_convotemplate:addScreen(cs_jsPlumb_1_13);
addConversationTemplate("aaph_koden_convotemplate", aaph_koden_convotemplate);

