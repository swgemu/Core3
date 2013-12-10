--If this convo has errors - Loc-nar this is the NPC behind the Fire Spider gives key code to scientist room 51892
biogenic_construction_ConversationTemplate = ConvoTemplate:new {
	initialScreen = "screenconvo1",
	templateType = "Normal",
	luaClassHandler = "",
	screens = {}

}

screenconvo1 = ConvoScreen:new {
	id = "screenconvo1",
	leftDialog = "@conversation/biogenic_construction:s_1df6adfc", -- Thank goodness you got here in time  
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_e4b06f76","screenconvo2"}, -- There's no need, I'm glad you're alright
		{"@conversation/biogenic_construction:s_355bc632","screenconvo3"} -- What were you doing here anyway
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo1);

screenconvo2 = ConvoScreen:new {
	id = "screenconvo2",
	leftDialog = "@conversation/biogenic_construction:s_eb771a95", -- Actually, I don't have much to give you
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_134aacec","screenconvo8"} -- I'm sure you'll think of something
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo2);

screenconvo3 = ConvoScreen:new {
	id = "screenconvo3",
	leftDialog = "@conversation/biogenic_construction:s_75118515", -- I was working on excavationg this passage
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_c30b797d","screenconvo11"} -- Yea, I'm getting out of here too
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo3);

screenconvo4 = ConvoScreen:new {
	id = "screenconvo4",
	leftDialog = "@conversation/biogenic_construction:s_1d440dae", -- No, thank you. If you have a chance
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_de8e8527",""} -- No, thank you. Good-bye friend
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo4);

screenconvo5 = ConvoScreen:new {
	id = "screenconvo5",
	leftDialog = "@conversation/biogenic_construction:s_2453dda8", -- I understand, thanks for killing  those spiders
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_c1d58076",""} -- Good-bye, and good luck
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo5);

screenconvo6 = ConvoScreen:new {
	id = "screenconvo6",
	leftDialog = "@conversation/biogenic_construction:s_575de8f1", -- Htanks for killing those spiders. I'm getting out of here
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_355bc632","screenconvo7"} -- What are you doing here anyway
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo6);

screenconvo7 = ConvoScreen:new {
	id = "screenconvo7",
	leftDialog = "@conversation/biogenic_construction:s_75118515", -- I was working on excavating this passage when an earthquake hit
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_c30b797d","screenconvo9"} -- yea, I'm getting out of here too
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo7);

screenconvo8 = ConvoScreen:new {
	id = "screenconvo8",
	leftDialog = "@conversation/biogenic_construction:s_67f9970", -- If you have a chance #2
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_5fe23666","screenconvo6"} -- OK. Good-bye then
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo8);

screenconvo9 = ConvoScreen:new {
	id = "screenconvo9",
	leftDialog = "@conversation/biogenic_construction:s_dc2d689c", -- Thanks again for killing those spiders
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_82e89d37","screenconvo5"} -- OK, I will try to check it out
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo9);

screenconvo10 = ConvoScreen:new {
	id = "screenconvo10",
	leftDialog = "@conversation/biogenic_construction:s_d8420164", -- Alright, Thanks again for killing those spiders
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_457410bd","screenconvo4"} -- No problem. Good-bye
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo10);

screenconvo11 = ConvoScreen:new {
	id = "screenconvo11",
	leftDialog = "@conversation/biogenic_construction:s_67f9970", -- If you ahve a chance, you might
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_construction:s_add15db6","screenconvo10"} -- I will if I have time
	}
}

biogenic_construction_ConversationTemplate:addScreen(screenconvo11);

addConversationTemplate("biogenic_construction_ConversationTemplate", biogenic_construction_ConversationTemplate);


