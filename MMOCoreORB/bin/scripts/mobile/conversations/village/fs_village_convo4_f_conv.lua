fsVillageConvo4FemaleTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_village_convo4_f:s_21bb400d", -- Everybody is running around with important things to do. Nobody has time for the crops. I'm going to try and get as much planted today as I can. Did you want to help?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo4_f:s_3f5944d5", "got_in_way" }, -- Not me, I'm not really the farmer type. 
		{ "@conversation/fs_village_convo4_f:s_34b7d87e", "on_second_thought" }, -- Sure, I'd be glad to help.
	}
}
fsVillageConvo4FemaleTemplate:addScreen(intro);

on_second_thought = ConvoScreen:new {
	id = "on_second_thought",
	leftDialog = "@conversation/fs_village_convo4_f:s_c3a7b9e4", -- On second thought, maybe you should go see what the elder needs. Last thing I need is following some urbanite around fixing all their mistakes.
	stopConversation = "true",
	options = {}
}
fsVillageConvo4FemaleTemplate:addScreen(on_second_thought);

got_in_way = ConvoScreen:new {
	id = "got_in_way",
	leftDialog = "@conversation/fs_village_convo4_f:s_62809d8c", -- Yea, I could tell that. You probably would have just gotten in the way.
	stopConversation = "true",
	options = {}
}
fsVillageConvo4FemaleTemplate:addScreen(got_in_way);

addConversationTemplate("fsVillageConvo4FemaleTemplate", fsVillageConvo4FemaleTemplate);
