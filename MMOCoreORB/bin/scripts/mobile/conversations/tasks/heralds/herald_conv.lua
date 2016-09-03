heraldConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "herald_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "",
	stopConversation = "false",
	options = {
	}
}
heraldConvoTemplate:addScreen(init);

npc_1_1 = ConvoScreen:new {
	id = "npc_1_1",
	leftDialog = ":npc_1_1",
	stopConversation = "false",
	options = {
		{ ":player_1_1", "npc_2_1" },
		{ ":player_2_1", "npc_3_1" },
		{ ":player_3_1", "npc_4_1" }
	}
}
heraldConvoTemplate:addScreen(npc_1_1);

npc_2_1 = ConvoScreen:new {
	id = "npc_2_1",
	leftDialog = ":npc_2_1",
	stopConversation = "true",
	options = {}
}
heraldConvoTemplate:addScreen(npc_2_1);

npc_3_1 = ConvoScreen:new {
	id = "npc_3_1",
	leftDialog = ":npc_3_1",
	stopConversation = "true",
	options = {}
}
heraldConvoTemplate:addScreen(npc_3_1);

npc_4_1 = ConvoScreen:new {
	id = "npc_4_1",
	leftDialog = ":npc_4_1",
	stopConversation = "false",
	options = {
		{ ":player_1_1", "npc_2_1" },
		{ ":player_2_1", "npc_3_1" }
	}
}
heraldConvoTemplate:addScreen(npc_4_1);

npc_work_1 = ConvoScreen:new {
	id = "npc_work_1",
	leftDialog = ":npc_work_1",
	stopConversation = "false",
	options = {
		{ ":player_reset", "npc_backtowork_1" },
		{ ":player_sorry", "npc_reset" }
	}
}
heraldConvoTemplate:addScreen(npc_work_1);

npc_backtowork_1 = ConvoScreen:new {
	id = "npc_backtowork_1",
	leftDialog = ":npc_backtowork_1",
	stopConversation = "true",
	options = {}
}
heraldConvoTemplate:addScreen(npc_backtowork_1);

npc_reset = ConvoScreen:new {
	id = "npc_reset",
	leftDialog = ":npc_reset",
	stopConversation = "true",
	options = {}
}
heraldConvoTemplate:addScreen(npc_reset);

addConversationTemplate("heraldConvoTemplate", heraldConvoTemplate);