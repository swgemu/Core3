villageQuharekPhase4ConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/quharek_phase_4:s_c3af3465", -- Hi. How go things?
	stopConversation = "false",
	options = {
		{ "@conversation/quharek_phase_4:s_30920b89", "good" }, -- It's going well. I have learned a lot.
		{ "@conversation/quharek_phase_4:s_c9211a00", "engineer" }, -- Do you have any other tasks for me?
	}
}
villageQuharekPhase4ConvoTemplate:addScreen(intro);

good = ConvoScreen:new {
	id = "good",
	leftDialog = "@conversation/quharek_phase_4:s_1fcf4289", -- Good! I am glad we have had some small part in your self-realization and growth. One of the greatest things a sapient can do on their path of life is to enhance the well being of other sapient beings.
	stopConversation = "false",
	options = {
		{ "@conversation/quharek_phase_4:s_8a61b230", "help_others" }, -- I agree. I hope I can return the favor someday.
		{ "@conversation/quharek_phase_4:s_46847c8d", "good_wishes" }, -- Wow, that's pretty sappy!
	}
}
villageQuharekPhase4ConvoTemplate:addScreen(good);

help_others = ConvoScreen:new {
	id = "help_others",
	leftDialog = "@conversation/quharek_phase_4:s_4909db59", -- Personally, I'd be happier if you directed that assistance to others not in this camp. We tend to do ok for ourselves even out in the desolate wilderness. There are those that are still far more in need of help than us.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase4ConvoTemplate:addScreen(help_others);

good_wishes = ConvoScreen:new {
	id = "good_wishes",
	leftDialog = "@conversation/quharek_phase_4:s_3a5501aa", -- Perhaps your 'self-realization and growth' wasn't as pronounced as it could have been. Good wishes to you friend.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase4ConvoTemplate:addScreen(good_wishes);

engineer = ConvoScreen:new {
	id = "engineer",
	leftDialog = "@conversation/quharek_phase_4:s_55ff471a", -- No. Our new Chief engineer is handling all new crafting tasks.
	stopConversation = "false",
	options = {
		{ "@conversation/quharek_phase_4:s_f3f4fde4", "south_wall" }, -- Where can I find the Chief engineer?
	}
}
villageQuharekPhase4ConvoTemplate:addScreen(engineer);

south_wall = ConvoScreen:new {
	id = "south_wall",
	leftDialog = "@conversation/quharek_phase_4:s_cae55dfb", -- Along the South wall near the sensor array. Good luck to you friend.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase4ConvoTemplate:addScreen(south_wall);

addConversationTemplate("villageQuharekPhase4ConvoTemplate", villageQuharekPhase4ConvoTemplate);
