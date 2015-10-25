trialsPadawanKillSludgePanther01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanKillSludgePanther01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_dfb295ef", -- This is going to get worse before it gets better. Unless we can stop it now.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_sludge_panther_01:s_7b35cfbc", "curious"} -- What is the problem?
	}
}
trialsPadawanKillSludgePanther01ConvoTemplate:addScreen(intro);

curious = ConvoScreen:new {
	id = "curious",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_d35e7542", -- It seems as though some bad Falumpaset meat was sold to some local merchants. Tainted with some kind of chemical the Falumpasets must have eaten. Once these merchants realized the meat was off, they naturally dumped it. 
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_sludge_panther_01:s_c2a10302", "kill_it"} -- Okay, doesn't really seem like it's a problem any more though.
	}
}
trialsPadawanKillSludgePanther01ConvoTemplate:addScreen(curious);

kill_it = ConvoScreen:new {
	id = "kill_it",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_3d2465d5", -- And it wouldn't be except that some sludge panthers devoured the dumped Falumpaset meat and are now in danger of spreading the toxin to other animals. I'm afraid we must try and eliminate the infected sludge panthers before this spreads much further.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_kill_sludge_panther_01:s_16d870fe", "kill_it_more"} -- Consider it done.
	}
}
trialsPadawanKillSludgePanther01ConvoTemplate:addScreen(kill_it);

kill_it_more = ConvoScreen:new {
	id = "kill_it_more",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_e49afb37", -- Excellent. If you can find and kill 20 sludge panthers, that seems like it should be sufficient.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillSludgePanther01ConvoTemplate:addScreen(kill_it_more);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_54cde3f2", -- Let me know once you have killed 20 Sludge Panthers.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillSludgePanther01ConvoTemplate:addScreen(back_notdone);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_acb29829", -- Excellent work. I'm positive now we've cleaned up a large enough portion of the infested population to prevent any serious damage to the ecosystem.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillSludgePanther01ConvoTemplate:addScreen(back_done);

player_already_completed = ConvoScreen:new {
	id = "player_already_completed",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_10a8184c", -- Thanks for your help. It's a shame to have to destroy those animals, but it's better in the long run. Even if they hadn't spread the infection directly, their offsprings would have been at risk.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillSludgePanther01ConvoTemplate:addScreen(player_already_completed);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_kill_sludge_panther_01:s_da6f521d", -- It's getting out of control.
	stopConversation = "true",
	options = {}
}
trialsPadawanKillSludgePanther01ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanKillSludgePanther01ConvoTemplate", trialsPadawanKillSludgePanther01ConvoTemplate);
