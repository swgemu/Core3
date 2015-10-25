trialsPadawanKillBazNitch01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanKillBazNitch01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_95db8861", -- Ah, perfect. You seem to fit the build of someone capable of handling this most unfortunate of tasks.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_baz_nitch_01:s_2313ac9e", "curious"} -- What are you talking about?
	}
}
trialsPadawanKillBazNitch01ConvoTemplate:addScreen(intro);

curious = ConvoScreen:new {
	id = "curious",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_88122b41", -- 	The Baz Nitch infestation of course! We need you, the most capable of adventurer to help remedy this horrendous epidemic.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_baz_nitch_01:s_983337f5", "killem"} -- Killing Baz Nitches eh? I'll do what I can.
	}
}
trialsPadawanKillBazNitch01ConvoTemplate:addScreen(curious);

killem = ConvoScreen:new {
	id = "killem",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_4498c7a3", -- Just what I wanted to hear, killing 20 of them should help curb the infestation.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillBazNitch01ConvoTemplate:addScreen(killem);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_a8f84c9f", -- Let me know once you have killed 20 Baz Nitches.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillBazNitch01ConvoTemplate:addScreen(back_notdone);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_a7c60196", -- Excellent work! Thanks to you we all have 20 less Baz Nitches to worry about. We can all sleep easier tonight my friend!
	stopConversation = "true",
	options = {}
}
trialsPadawanKillBazNitch01ConvoTemplate:addScreen(back_done);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_2b2c13e4", -- It's not just that they are foul creatures, but they also destroy crops... and people.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillBazNitch01ConvoTemplate:addScreen(noquest_player_talks);

player_already_completed = ConvoScreen:new {
	id = "player_already_completed",
	leftDialog = "@conversation/padawan_kill_baz_nitch_01:s_70d6b213", -- Thank you so much. That infestation of baz nitches was getting out of hand.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillBazNitch01ConvoTemplate:addScreen(player_already_completed);

addConversationTemplate("trialsPadawanKillBazNitch01ConvoTemplate", trialsPadawanKillBazNitch01ConvoTemplate);
