trialsPadawanArchitect01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanArchitect01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_architect_01:s_7637308a", -- I have a quick job for you friend. I'm an architect and could use someone of your skill to clear some unwelcome inhabitants off of some land I just recently purchased. Does this sound like something you could help me with?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_architect_01:s_a1ef941b", "yes_accept"}, -- Yes, I'm here to help.
		{"@conversation/padawan_architect_01:s_cc9db25e", "no_decline"} -- Stop! I'm not interested in your petty little problems.
	}
}
trialsPadawanArchitect01ConvoTemplate:addScreen(intro);

yes_accept = ConvoScreen:new {
	id = "yes_accept",
	leftDialog = "@conversation/padawan_architect_01:s_ea2c487d", -- Excellent, thank you very much. I do appreciate this. Here is a waypoint to the location I need you to scout out. Please remove any squatters who are loitering there. I'll be here waiting for you once you've finished.
	stopConversation = "true",
	options = {}
}
trialsPadawanArchitect01ConvoTemplate:addScreen(yes_accept);

no_decline = ConvoScreen:new {
	id = "no_decline",
	leftDialog = "@conversation/padawan_architect_01:s_f2d3daf1", -- Wha... if you do not wish to help, then so be it. But there is no call for being rude.
	stopConversation = "true",
	options = {}
}
trialsPadawanArchitect01ConvoTemplate:addScreen(no_decline);

not_yet_done = ConvoScreen:new {
	id = "not_yet_done",
	leftDialog = "@conversation/padawan_architect_01:s_25d34a1e", -- Sorry friend... can't talk. I'm losing money every day we fail to begin construction.
	stopConversation = "true",
	options = {}
}
trialsPadawanArchitect01ConvoTemplate:addScreen(not_yet_done);

done_with_task = ConvoScreen:new {
	id = "done_with_task",
	leftDialog = "@conversation/padawan_architect_01:s_91e6aa00", -- Is the area cleared?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_architect_01:s_f0d9878f", "yes_kill_fail"}, -- Yes, it is. I'm proud to say that the gungan claiming to own the land is dead.
		{"@conversation/padawan_architect_01:s_88ac3394", "back_chose_success"} -- That land already has an owner. You have no right to take it from them.
	}
}
trialsPadawanArchitect01ConvoTemplate:addScreen(done_with_task);

yes_kill_fail = ConvoScreen:new {
	id = "yes_kill_fail",
	leftDialog = "@conversation/padawan_architect_01:s_50bf04b1", -- I'm glad to hear that, construction can now begin. Thank you for your hard work.
	stopConversation = "true",
	options = {}
}
trialsPadawanArchitect01ConvoTemplate:addScreen(yes_kill_fail);

back_chose_success = ConvoScreen:new {
	id = "back_chose_success",
	leftDialog = "@conversation/padawan_architect_01:s_8bf180e7", -- An owner?! That family may occupy that land, but I am it's owner. Your sympathy is sickening.
	stopConversation = "true",
	options = {}
}
trialsPadawanArchitect01ConvoTemplate:addScreen(back_chose_success);

over_sour_success = ConvoScreen:new {
	id = "over_sour_success",
	leftDialog = "@conversation/padawan_architect_01:s_ac5709b0", -- Bah... I'll just find someone else who can clear that land for me. Leave me alone.
	stopConversation = "true",
	options = {}
}
trialsPadawanArchitect01ConvoTemplate:addScreen(over_sour_success);

addConversationTemplate("trialsPadawanArchitect01ConvoTemplate", trialsPadawanArchitect01ConvoTemplate);
