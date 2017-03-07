padawan_kill_baz_nitch_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_kill_baz_nitch_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_95db8861", -- Ah, perfect. You seem to fit the build of someone capable of handling this most unfortunate of tasks.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_baz_nitch_01:s_2313ac9e", "baz_nitch_infestation"} -- What are you talking about?
	}
}
padawan_kill_baz_nitch_01_convo_template:addScreen(intro);

baz_nitch_infestation = ConvoScreen:new {
	id = "baz_nitch_infestation",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_88122b41", -- 	The Baz Nitch infestation of course! We need you, the most capable of adventurer to help remedy this horrendous epidemic.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_baz_nitch_01:s_983337f5", "curb_infestation"} -- Killing Baz Nitches eh? I'll do what I can.
	}
}
padawan_kill_baz_nitch_01_convo_template:addScreen(baz_nitch_infestation);

curb_infestation = ConvoScreen:new {
	id = "curb_infestation",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_4498c7a3", -- Just what I wanted to hear, killing 20 of them should help curb the infestation.
	stopConversation = "true",
	options = {}
}
padawan_kill_baz_nitch_01_convo_template:addScreen(curb_infestation);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_a8f84c9f", -- Let me know once you have killed 20 Baz Nitches.
	stopConversation = "true",
	options = {}
}
padawan_kill_baz_nitch_01_convo_template:addScreen(intro_in_progress);

intro_reached_goal = ConvoScreen:new {
	id = "intro_reached_goal",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_a7c60196", -- Excellent work! Thanks to you we all have 20 less Baz Nitches to worry about. We can all sleep easier tonight my friend!
	stopConversation = "true",
	options = {}
}
padawan_kill_baz_nitch_01_convo_template:addScreen(intro_reached_goal);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_2b2c13e4", -- It's not just that they are foul creatures, but they also destroy crops... and people.
	stopConversation = "true",
	options = {}
}
padawan_kill_baz_nitch_01_convo_template:addScreen(not_quest_owner);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_70d6b213", -- Thank you so much. That infestation of baz nitches was getting out of hand.
	stopConversation = "true",
	options = {}
}
padawan_kill_baz_nitch_01_convo_template:addScreen(quest_completed);

addConversationTemplate("padawan_kill_baz_nitch_01_convo_template", padawan_kill_baz_nitch_01_convo_template);
