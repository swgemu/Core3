padawan_surveyor_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_surveyor_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_surveyor_01:s_95cc5c27", -- I can't believe he expects me to gather resources for him THERE.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_80783f21", "good_questions"}, -- Who? What? When and where?
		{"@conversation/padawan_surveyor_01:s_e01d4e3a", "doesnt_matter_much"} -- I can't believe you think I am INTERESTED.
	}
}
padawan_surveyor_01_convo_template:addScreen(intro);

good_questions = ConvoScreen:new {
	id = "good_questions",
	leftDialog = "@conversation/padawan_surveyor_01:s_4f0a7816", -- Good questions. My boss employs me to go out and gather samples for him from around the galaxy. He recently asked me to go out and gather some from a fairly dangerous area. I mean, there's a sharnaff bull there. Those things are HUGE. Actually, maybe you could help me.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_df1f4d74", "here_is_waypoint"}, -- Sure, I'm willing to help you out.
		{"@conversation/padawan_surveyor_01:s_6f9237a3", "cant_blame_you"} -- Yeah, right. Like that's gonna happen.
	}
}
padawan_surveyor_01_convo_template:addScreen(good_questions);

here_is_waypoint = ConvoScreen:new {
	id = "here_is_waypoint",
	leftDialog = "@conversation/padawan_surveyor_01:s_1a4fb5a7", -- Excellent, here is the waypoint my boss gave me. Once you've gotten rid of the sharnaff bull, come back and let me know so I can go do my thing. Thanks! I really appreciate this.
	stopConversation = "true",
	options = {}
}
padawan_surveyor_01_convo_template:addScreen(here_is_waypoint);

cant_blame_you = ConvoScreen:new {
	id = "cant_blame_you",
	leftDialog = "@conversation/padawan_surveyor_01:s_268abe", -- I can't much blame you; I'd rather not as well.
	stopConversation = "true",
	options = {}
}
padawan_surveyor_01_convo_template:addScreen(cant_blame_you);

doesnt_matter_much = ConvoScreen:new {
	id = "doesnt_matter_much",
	leftDialog = "@conversation/padawan_surveyor_01:s_88563437", -- Doesn't much matter to me, either way it looks like it's not getting done.
	stopConversation = "true",
	options = {}
}
padawan_surveyor_01_convo_template:addScreen(doesnt_matter_much);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_surveyor_01:s_cc8d7500", -- Back so soon? Wow, I'm impressed.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_bed3977c", "not_a_problem"}, -- Not so fast... I'm not actually finished yet. Give me a bit more time.
		{"@conversation/padawan_surveyor_01:s_f78dd868", "scooping_sludge"} -- Speaking of fast, watch how quickly I tell you I'm not doing it.
	}
}
padawan_surveyor_01_convo_template:addScreen(intro_in_progress);

not_a_problem = ConvoScreen:new {
	id = "not_a_problem",
	leftDialog = "@conversation/padawan_surveyor_01:s_29df11d8", -- Not a problem. Just let me know when it's safe.
	stopConversation = "true",
	options = {}
}
padawan_surveyor_01_convo_template:addScreen(not_a_problem);

scooping_sludge = ConvoScreen:new {
	id = "scooping_sludge",
	leftDialog = "@conversation/padawan_surveyor_01:s_2f57a101", -- But... but. Fine. Maybe I can get work scooping sludge out of ditches.
	stopConversation = "true",
	options = {}
}
padawan_surveyor_01_convo_template:addScreen(scooping_sludge);

intro_target_killed = ConvoScreen:new {
	id = "intro_target_killed",
	leftDialog = "@conversation/padawan_surveyor_01:s_723b6d0e", -- Have you cleared the area? Is that sharnaff bull gone?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_surveyor_01:s_14d76798", "hope_not_difficult"}, -- Yes. It's safe there now.
	}
}
padawan_surveyor_01_convo_template:addScreen(intro_target_killed);

hope_not_difficult = ConvoScreen:new {
	id = "hope_not_difficult",
	leftDialog = "@conversation/padawan_surveyor_01:s_f547f53", -- 	Great, I hope it wasn't too difficult. Thanks again.
	stopConversation = "true",
	options = {}
}
padawan_surveyor_01_convo_template:addScreen(hope_not_difficult);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_surveyor_01:s_a9fb608b", -- Oh thank you so much. I'm terribly afraid of large animals. Whew. That's a relief.
	stopConversation = "true",
	options = {}
}
padawan_surveyor_01_convo_template:addScreen(quest_completed);

not_quest_owner = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_surveyor_01:s_63bacc6c", -- I'm not going. No chance. I'll simply get a new job. A much worse job, I'm sure. But at least I'll be alive.
	stopConversation = "true",
	options = {}
}
padawan_surveyor_01_convo_template:addScreen(noquest_player_talks);

addConversationTemplate("padawan_surveyor_01_convo_template", padawan_surveyor_01_convo_template);
