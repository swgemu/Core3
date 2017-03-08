padawan_spice_mom_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_spice_mom_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_spice_mom_01:s_4f24860b", -- Hello dear, I'm a single mother and could use all the help I can get. You wouldn't mind helping out an old mother now would you?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_16ec7737", "short_on_supplies"}, -- No, not at all Miss, how may I help?
		{"@conversation/padawan_spice_mom_01:s_d4ade5e3", "sorry_for_bothering"} -- Ask one of your kids to do it. I'm busy.
	}
}
padawan_spice_mom_01_convo_template:addScreen(intro);

short_on_supplies = ConvoScreen:new {
	id = "short_on_supplies",
	leftDialog = "@conversation/padawan_spice_mom_01:s_6a11e41a", -- I've run short on some supplies around the house, and could use a healthy person like you to run out and pick them up for me. I know it's not the most glamorous of tasks, but I have no one else to ask. Would you mind?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_d471cdd", "here_is_waypoint"}, -- I would be happy to help.
		{"@conversation/padawan_spice_mom_01:s_d4ade5e3", "sorry_for_bothering"} -- Ask one of your kids to do it. I'm busy.
	}
}
padawan_spice_mom_01_convo_template:addScreen(short_on_supplies);

here_is_waypoint = ConvoScreen:new {
	id = "here_is_waypoint",
	leftDialog = "@conversation/padawan_spice_mom_01:s_93965747", -- Oh good!  You are a dear, here is the waypoint to my good friend Evif Sulp, he has what I need.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(here_is_waypoint);

sorry_for_bothering = ConvoScreen:new {
	id = "sorry_for_bothering",
	leftDialog = "@conversation/padawan_spice_mom_01:s_b40d662", -- I see, well sorry for bothering dear.  Good day.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(sorry_for_bothering);

intro_talked_to_target = ConvoScreen:new {
	id = "intro_talked_to_target",
	leftDialog = "@conversation/padawan_spice_mom_01:s_98244955", -- Have you got my supplies.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_9b2292c8", "hand_them_over"}, -- Yes, I have them.
	}
}
padawan_spice_mom_01_convo_template:addScreen(intro_talked_to_target);

hand_them_over = ConvoScreen:new {
	id = "hand_them_over",
	leftDialog = "@conversation/padawan_spice_mom_01:s_cf8c69f5", -- Oh good, hand them over please.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_829888a9", "grateful_son"}, -- Here you go.
		{"@conversation/padawan_spice_mom_01:s_85da54b7", "pain_and_misery"} -- Are you sure you want these?
	}
}
padawan_spice_mom_01_convo_template:addScreen(hand_them_over);

pain_and_misery = ConvoScreen:new {
	id = "pain_and_misery",
	leftDialog = "@conversation/padawan_spice_mom_01:s_dcecfc37", -- Hand them over dear, or so help me I will make sure the rest of your existence is one of pain and misery.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_72b6d639", "grateful_son"}, -- Wow, here you go.
		{"@conversation/padawan_spice_mom_01:s_d1aec57f", "dont_regret_anything"} -- Don't say anything you are going to regret.
	}
}
padawan_spice_mom_01_convo_template:addScreen(pain_and_misery);

dont_regret_anything = ConvoScreen:new {
	id = "dont_regret_anything",
	leftDialog = "@conversation/padawan_spice_mom_01:s_a687a0a6", -- 	I don't regret anything anymore. Now give that spice here! My son is in horrible pain, and nothing seems to work better than the calming hallucinations he gets from that spice. As much as I hate giving it to him, he needs it to make his painful existence bearable.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_1aa2a6e6", "through_another_week"}, -- Oh, I'm sorry for causing trouble.  Here is the spice.
		{"@conversation/padawan_spice_mom_01:s_a8241eb1", "good_and_bad"} -- I don't care what you use it for... you're no better than a spice peddler.
	}
}
padawan_spice_mom_01_convo_template:addScreen(dont_regret_anything);

good_and_bad = ConvoScreen:new {
	id = "good_and_bad",
	leftDialog = "@conversation/padawan_spice_mom_01:s_751ed2f1", -- 	May my son's pain be passed to you. Maybe then you'd see that the world is not so clearly good and bad. That spice would have brought peace to my son. To my mind, that good is worth the price.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(good_and_bad);

through_another_week = ConvoScreen:new {
	id = "through_another_week",
	leftDialog = "@conversation/padawan_spice_mom_01:s_78f7bd03", -- 	Thank you dear, these spices will help my son through another week or so.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(through_another_week);

grateful_son = ConvoScreen:new {
	id = "grateful_son",
	leftDialog = "@conversation/padawan_spice_mom_01:s_dc552ff6", -- Thank you dear, my son will be very grateful. The calming hallucinations this spice gives him help ease his mind of the lingering pain he still suffers from after he was in a horrible swoop accident as a child.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(grateful_son);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_spice_mom_01:s_b638139d", -- Did you speak with Evif?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_42c15c5", "hurry_back"}, -- Not yet, but I'm on my way.
		{"@conversation/padawan_spice_mom_01:s_8a806d30", "sorry_for_bothering"} -- No and even thinking about doing so was a mistake.
	}
}
padawan_spice_mom_01_convo_template:addScreen(intro_in_progress);

hurry_back = ConvoScreen:new {
	id = "hurry_back",
	leftDialog = "@conversation/padawan_spice_mom_01:s_238c7ac2", -- Oh very good. Hurry back now, dear.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(hurry_back);

what_did_i_do = ConvoScreen:new {
	id = "what_did_i_do",
	leftDialog = "@conversation/padawan_spice_mom_01:s_a3b22c35", -- Oh my. What did I do to provoke such an outburst?!
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(what_did_i_do);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_spice_mom_01:s_bf3942ab", -- Please believe that I know what I'm doing, and that this is the best that can be done for my son.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(quest_completed);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_spice_mom_01:s_2aa97a99", -- Oh my poor son. Whatever will I do if I cannot ease his pain and suffering.
	stopConversation = "true",
	options = {}
}
padawan_spice_mom_01_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_spice_mom_01_convo_template", padawan_spice_mom_01_convo_template);
