padawan_kill_falumpaset_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_kill_falumpaset_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_82761761", -- Oh dear, we have quite the problem.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_falumpaset_01:s_889a3584", "cargo_vessel"}, -- What's wrong?
		{"@conversation/padawan_kill_falumpaset_01:s_beb9462d", "not_exactly"} -- I assume that is the royal 'we', correct?
	}
}
padawan_kill_falumpaset_01_convo_template:addScreen(intro);

cargo_vessel = ConvoScreen:new {
	id = "cargo_vessel",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_1faee9ae", -- A cargo vessel carrying a shipment of some less than legal merchandise has gotten us all into quite a bad spot. It seems as though this vessel has been leaking chemicals all over the landscape infecting a very large percentage of the local herbivores. We have an idea on how to solve the problem, but we are going to need your help.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_falumpaset_01:s_dedea172", "need_you_to_do"} -- Sure, what is your plan?
	}
}
padawan_kill_falumpaset_01_convo_template:addScreen(cargo_vessel);

need_you_to_do = ConvoScreen:new {
	id = "need_you_to_do",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_bd13c42d", -- What I need you to do is kill 20 Falumpaset, those are the creatures who ate up the largest portions of the sludge that was spilt. Once you've taken down 20 of them come back here and let me know.
	stopConversation = "true",
	options = {}
}
padawan_kill_falumpaset_01_convo_template:addScreen(need_you_to_do);

not_exactly = ConvoScreen:new {
	id = "not_exactly",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_d4307269", -- Not exactly, so are you willing to hear the problem? Or no?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_falumpaset_01:s_25c07049", "cargo_vessel"}, -- Sure, what can I help you with?
		{"@conversation/padawan_kill_falumpaset_01:s_f3993d68", "thanks_anyway"} -- No. And I'm sorry I spoke to you in the first place.
	}
}
padawan_kill_falumpaset_01_convo_template:addScreen(not_exactly);

thanks_anyway = ConvoScreen:new {
	id = "thanks_anyway",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_e73e7a7a", -- I see. Well, thanks anyway.
	stopConversation = "true",
	options = {}
}
padawan_kill_falumpaset_01_convo_template:addScreen(thanks_anyway);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_741c2cf1", -- Let me know once you have killed 20 Falumpaset.
	stopConversation = "true",
	options = {}
}
padawan_kill_falumpaset_01_convo_template:addScreen(intro_in_progress);

intro_reached_goal = ConvoScreen:new {
	id = "intro_reached_goal",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_3d66a959", -- Excellent work, I think you've cleared it up before any serious consequences could arise.
	stopConversation = "true",
	options = {}
}
padawan_kill_falumpaset_01_convo_template:addScreen(intro_reached_goal);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_cce54be1", -- Ah those poor creatures. But I suppose it's best to destroy them before this can spread to others.
	stopConversation = "true",
	options = {}
}
padawan_kill_falumpaset_01_convo_template:addScreen(not_quest_owner);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_761aa5f8", -- Well done. You took to that quite well. Sad business, but necessary. This kind of thing happens from time to time.
	stopConversation = "true",
	options = {}
}
padawan_kill_falumpaset_01_convo_template:addScreen(quest_completed);

addConversationTemplate("padawan_kill_falumpaset_01_convo_template", padawan_kill_falumpaset_01_convo_template);
