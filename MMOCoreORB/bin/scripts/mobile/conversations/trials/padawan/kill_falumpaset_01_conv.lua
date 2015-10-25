trialsPadawanKillFalumpaset01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanKillFalumpaset01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_82761761", -- Oh dear, we have quite the problem.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_falumpaset_01:s_889a3584", "curious"}, -- What's wrong?
		{"@conversation/padawan_kill_falumpaset_01:s_beb9462d", "not_curious"} -- I assume that is the royal 'we', correct?
	}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(intro);

curious = ConvoScreen:new {
	id = "curious",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_1faee9ae", -- A cargo vessel carrying a shipment of some less than legal merchandise has gotten us all into quite a bad spot. It seems as though this vessel has been leaking chemicals all over the landscape infecting a very large percentage of the local herbivores. We have an idea on how to solve the problem, but we are going to need your help.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_falumpaset_01:s_dedea172", "killing"} -- Sure, what is your plan?
	}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(curious);

killing = ConvoScreen:new {
	id = "killing",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_bd13c42d", -- What I need you to do is kill 20 Falumpaset, those are the creatures who ate up the largest portions of the sludge that was spilt. Once you've taken down 20 of them come back here and let me know.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(killing);

not_curious = ConvoScreen:new {
	id = "not_curious",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_d4307269", -- Not exactly, so are you willing to hear the problem? Or no?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_falumpaset_01:s_25c07049", "curious"}, -- Sure, what can I help you with?
		{"@conversation/padawan_kill_falumpaset_01:s_f3993d68", "declining"} -- No. And I'm sorry I spoke to you in the first place.
	}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(curious);

declining = ConvoScreen:new {
	id = "declining",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_e73e7a7a", -- I see. Well, thanks anyway.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(declining);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_741c2cf1", -- Let me know once you have killed 20 Falumpaset.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(back_notdone);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_3d66a959", -- Excellent work, I think you've cleared it up before any serious consequences could arise.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(back_done);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_kill_falumpaset_01:s_cce54be1", -- Ah those poor creatures. But I suppose it's best to destroy them before this can spread to others.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(noquest_player_talks);

player_already_completed = ConvoScreen:new {
	id = "player_already_completed",
	leftDialog = "conversation/padawan_kill_falumpaset_01:s_761aa5f8", -- Well done. You took to that quite well. Sad business, but necessary. This kind of thing happens from time to time.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillFalumpaset01ConvoTemplate:addScreen(player_already_completed);

addConversationTemplate("trialsPadawanKillFalumpaset01ConvoTemplate", trialsPadawanKillFalumpaset01ConvoTemplate);
