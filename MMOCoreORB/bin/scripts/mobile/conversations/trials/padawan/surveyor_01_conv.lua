trialsPadawanSurveyor01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanSurveyor01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_surveyor_01:s_95cc5c27", -- I can't believe he expects me to gather resources for him THERE.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_80783f21", "intro_more"}, -- Who? What? When and where?
		{"@conversation/padawan_surveyor_01:s_e01d4e3a", "intro_not"} -- I can't believe you think I am INTERESTED.
	}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(intro);

intro_more = ConvoScreen:new {
	id = "intro_more",
	leftDialog = "@conversation/padawan_surveyor_01:s_4f0a7816", -- Good questions. My boss employs me to go out and gather samples for him from around the galaxy. He recently asked me to go out and gather some from a fairly dangerous area. I mean, there's a sharnaff bull there. Those things are HUGE. Actually, maybe you could help me.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_df1f4d74", "more_accept"}, -- Sure, I'm willing to help you out.
		{"@conversation/padawan_surveyor_01:s_6f9237a3", "intro_not"} -- Yeah, right. Like that's gonna happen.
	}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(intro_more);

intro_not = ConvoScreen:new {
	id = "intro_not",
	leftDialog = "@conversation/padawan_surveyor_01:s_268abe", -- I can't much blame you; I'd rather not as well.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_88563437", "not_more"} -- Doesn't much matter to me, either way it looks like it's not getting done.
	}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(intro_not);

not_more = ConvoScreen:new {
	id = "not_more",
	leftDialog = "@conversation/padawan_surveyor_01:s_2f57a101", -- But... but. Fine. Maybe I can get work scooping sludge out of ditches.
	stopConversation = "true",
	options = {}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(not_more);

more_accept = ConvoScreen:new {
	id = "more_accept",
	leftDialog = "@conversation/padawan_surveyor_01:s_1a4fb5a7", -- Excellent, here is the waypoint my boss gave me. Once you've gotten rid of the sharnaff bull, come back and let me know so I can go do my thing. Thanks! I really appreciate this.
	stopConversation = "true",
	options = {}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(more_accept);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_surveyor_01:s_cc8d7500", -- Back so soon? Wow, I'm impressed.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_bed3977c", "more_done"}, -- Not so fast... I'm not actually finished yet. Give me a bit more time.
		{"@conversation/padawan_surveyor_01:s_f78dd868", "intro_not"} -- Speaking of fast, watch how quickly I tell you I'm not doing it.
	}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(back_notdone);

more_done = ConvoScreen:new {
	id = "more_done",
	leftDialog = "@conversation/padawan_surveyor_01:s_29df11d8", -- Not a problem. Just let me know when it's safe.
	stopConversation = "true",
	options = {}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(more_done);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_surveyor_01:s_723b6d0e", -- Have you cleared the area? Is that sharnaff bull gone?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_14d76798", "done_final"} -- Yes. It's safe there now.
	}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(back_done);

done_final = ConvoScreen:new {
	id = "done_final",
	leftDialog = "@conversation/padawan_surveyor_01:s_a9fb608b", -- Oh thank you so much. I'm terribly afraid of large animals. Whew. That's a relief.
	stopConversation = "true",
	options = {}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(done_final);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_surveyor_01:s_63bacc6c", -- I'm not going. No chance. I'll simply get a new job. A much worse job, I'm sure. But at least I'll be alive.
	stopConversation = "true",
	options = {}
}
trialsPadawanSurveyor01ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanSurveyor01ConvoTemplate", trialsPadawanSurveyor01ConvoTemplate);
