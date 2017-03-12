padawan_kill_sludge_panther_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_kill_sludge_panther_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_da6f521d", -- It's getting out of control.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_sludge_panther_01:s_7b35cfbc", "bad_meat"} -- What is the problem?
	}
}
padawan_kill_sludge_panther_01_convo_template:addScreen(intro);

bad_meat = ConvoScreen:new {
	id = "bad_meat",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_d35e7542", -- It seems as though some bad Falumpaset meat was sold to some local merchants. Tainted with some kind of chemical the Falumpasets must have eaten. Once these merchants realized the meat was off, they naturally dumped it.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_sludge_panther_01:s_c2a10302", "dumped_meat"} -- Okay, doesn't really seem like it's a problem any more though.
	}
}
padawan_kill_sludge_panther_01_convo_template:addScreen(bad_meat);

dumped_meat = ConvoScreen:new {
	id = "dumped_meat",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_3d2465d5", -- And it wouldn't be except that some sludge panthers devoured the dumped Falumpaset meat and are now in danger of spreading the toxin to other animals. I'm afraid we must try and eliminate the infected sludge panthers before this spreads much further.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_sludge_panther_01:s_16d870fe", "find_and_kill"} -- Consider it done.
	}
}
padawan_kill_sludge_panther_01_convo_template:addScreen(dumped_meat);

find_and_kill = ConvoScreen:new {
	id = "find_and_kill",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_e49afb37", -- Excellent. If you can find and kill 20 sludge panthers, that seems like it should be sufficient.
	stopConversation = "true",
	options = {}
}
padawan_kill_sludge_panther_01_convo_template:addScreen(find_and_kill);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_54cde3f2", -- Let me know once you have killed 20 Sludge Panthers.
	stopConversation = "true",
	options = {}
}
padawan_kill_sludge_panther_01_convo_template:addScreen(intro_in_progress);

intro_reached_goal = ConvoScreen:new {
	id = "intro_reached_goal",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_acb29829", -- Excellent work. I'm positive now we've cleaned up a large enough portion of the infested population to prevent any serious damage to the ecosystem.
	stopConversation = "true",
	options = {}
}
padawan_kill_sludge_panther_01_convo_template:addScreen(intro_reached_goal);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_10a8184c", -- Thanks for your help. It's a shame to have to destroy those animals, but it's better in the long run. Even if they hadn't spread the infection directly, their offsprings would have been at risk.
	stopConversation = "true",
	options = {}
}
padawan_kill_sludge_panther_01_convo_template:addScreen(quest_completed);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_dfb295ef", -- This is going to get worse before it gets better. Unless we can stop it now.
	stopConversation = "true",
	options = {}
}
padawan_kill_sludge_panther_01_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_kill_sludge_panther_01_convo_template", padawan_kill_sludge_panther_01_convo_template);
