trialsPadawanSpiceMom01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanSpiceMom01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_spice_mom_01:s_4f24860b", -- Hello dear, I'm a single mother and could use all the help I can get. You wouldn't mind helping out an old mother now would you?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_16ec7737", "intro_more"}, -- No, not at all Miss, how may I help?
		{"@conversation/padawan_spice_mom_01:s_d4ade5e3", "intro_not"} -- Ask one of your kids to do it. I'm busy.
	}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(intro);

intro_more = ConvoScreen:new {
	id = "intro_more",
	leftDialog = "@conversation/padawan_spice_mom_01:s_6a11e41a", -- I've run short on some supplies around the house, and could use a healthy person like you to run out and pick them up for me. I know it's not the most glamorous of tasks, but I have no one else to ask. Would you mind?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_d471cdd", "more_done"}, -- I would be happy to help.
		{"@conversation/padawan_spice_mom_01:s_d4ade5e3", "intro_not"} -- Ask one of your kids to do it. I'm busy.
	}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(intro_more);

intro_not = ConvoScreen:new {
	id = "intro_not",
	leftDialog = "@conversation/padawan_spice_mom_01:s_b40d662", -- I see, well sorry for bothering dear. Good day.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(intro_not);

more_done = ConvoScreen:new {
	id = "more_done",
	leftDialog = "@conversation/padawan_spice_mom_01:s_93965747", -- Oh good! You are a dear, here is the waypoint to my good friend Evif Sulp, he has what I need. Tell him Sola sent you.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(more_done);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_spice_mom_01:s_b638139d", -- Did you speak with Evif?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_42c15c5", "continue_on"}, -- Not yet, but I'm on my way.
		{"@conversation/padawan_spice_mom_01:s_8a806d30", "intro_not"} -- No and even thinking about doing so was a mistake.
	}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(back_notdone);

continue_on = ConvoScreen:new {
	id = "continue_on",
	leftDialog = "@conversation/padawan_spice_mom_01:s_238c7ac2", -- Oh very good. Hurry back now, dear.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(continue_on);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_spice_mom_01:s_98244955", -- Have you got my supplies.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_9b2292c8", "back_done_more"}, -- Yes, I have them.
		{"@conversation/padawan_spice_mom_01:s_8a806d30", "intro_not"} -- No and even thinking about doing so was a mistake.
	}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(back_done);

back_done_more = ConvoScreen:new {
	id = "back_done_more",
	leftDialog = "@conversation/padawan_spice_mom_01:s_cf8c69f5", -- Oh good, hand them over please.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_829888a9", "back_done_give"}, -- Here you go.
		{"@conversation/padawan_spice_mom_01:s_85da54b7", "back_done_hmm"} -- Are you sure you want these?
	}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(back_done_more);

back_done_hmm = ConvoScreen:new {
	id = "back_done_hmm",
	leftDialog = "@conversation/padawan_spice_mom_01:s_dcecfc37", -- Hand them over dear, or so help me I will make sure the rest of your existence is one of pain and misery.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_72b6d639", "back_done_okay"}, -- Wow, here you go.
		{"@conversation/padawan_spice_mom_01:s_a3b22c35", "back_done_too"}, -- Oh my. What did I do to provoke such an outburst?!
		{"@conversation/padawan_spice_mom_01:s_d1aec57f", "back_hmm_again"}, -- Don't say anything you are going to regret.
		{"@conversation/padawan_spice_mom_01:s_8a806d30", "not_give"} -- No and even thinking about doing so was a mistake.
	}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(back_done_hmm);

back_done_too = ConvoScreen:new {
	id = "back_done_too",
	leftDialog = "@conversation/padawan_spice_mom_01:s_bf3942ab", -- Please believe that I know what I'm doing, and that this is the best that can be done for my son.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_829888a9", "back_done_give"}, -- Here you go.
		{"@conversation/padawan_spice_mom_01:s_a8241eb1", "not_give"} -- I don't care what you use it for... you're no better than a spice peddler.
	}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(back_done_too);

back_hmm_again = ConvoScreen:new {
	id = "back_hmm_again",
	leftDialog = "@conversation/padawan_spice_mom_01:s_a687a0a6", -- I don't regret anything anymore. Now give that spice here! My son is in horrible pain, and nothing seems to work better than the calming hallucinations he gets from that spice. As much as I hate giving it to him, he needs it to make his painful existence bearable.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_spice_mom_01:s_829888a9", "back_done_give"}, -- Here you go.
		{"@conversation/padawan_spice_mom_01:s_a8241eb1", "not_give"} -- I don't care what you use it for... you're no better than a spice peddler.
	}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(back_hmm_again);

not_give = ConvoScreen:new {
	id = "not_give",
	leftDialog = "@conversation/padawan_spice_mom_01:s_751ed2f1", -- May my son's pain be passed to you. Maybe then you'd see that the world is not so clearly good and bad. That spice would have brought peace to my son. To my mind, that good is worth the price.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(not_give);

back_done_give = ConvoScreen:new {
	id = "back_done_give",
	leftDialog = "@conversation/padawan_spice_mom_01:s_dc552ff6", -- Thank you dear, my son will be very grateful. The calming hallucinations this spice gives him help ease his mind of the lingering pain he still suffers from after he was in a horrible swoop accident as a child.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(back_done_give);

back_done_okay = ConvoScreen:new {
	id = "back_done_okay",
	leftDialog = "@conversation/padawan_spice_mom_01:s_78f7bd03", -- Thank you dear, these spices will help my son through another week or so.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(back_done_okay);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_spice_mom_01:s_2aa97a99", -- Oh my poor son. Whatever will I do if I cannot ease his pain and suffering.
	stopConversation = "true",
	options = {}
}
trialsPadawanSpiceMom01ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanSpiceMom01ConvoTemplate", trialsPadawanSpiceMom01ConvoTemplate);
