victorQuestpSlumsConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "victorQuestpSlumsConvoHandler",
	screens = {}
}

init_joined_victor = ConvoScreen:new {
	id = "init_joined_victor",
	leftDialog = "@conversation/victor_questp_slums:s_f25283c7", -- I knew you'd come. The story should be told to everyone. It has a good moral to it, I think.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_slums:s_8611417a", "tuskens_came"}, -- What story?
	}
}
victorQuestpSlumsConvoTemplate:addScreen(init_joined_victor);

tuskens_came = ConvoScreen:new {
	id = "tuskens_came",
	leftDialog = "@conversation/victor_questp_slums:s_222d159b", -- Listen closely. The Sand People have been attacking the outskirts of the city. For some reason, the Empire has hidden this fact from those who do not live in the slums... not to panic everyone else, I guess. It's hard to live here. One particular night, a couple of months back, the Tuskens came. They killed several of us here. They took my son. I--I just don't want to think about it... about what could have happened that night.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_slums:s_540ac7e9", "poor_woman"}, -- Continue.
	}
}
victorQuestpSlumsConvoTemplate:addScreen(tuskens_came);

poor_woman = ConvoScreen:new {
	id = "poor_woman",
	leftDialog = "@conversation/victor_questp_slums:s_41e66644", -- I'm just a poor woman. I'm not significant in this life, or to this city. But Victor Visalis heard of my misfortune and took pity on me. He took his own soldiers and destroyed the Tuskens. He returned my son to me! Can you believe that? I'm so grateful.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_slums:s_d5f19466", "would_do_anything"}, -- I need your help.
	}
}
victorQuestpSlumsConvoTemplate:addScreen(poor_woman);

would_do_anything = ConvoScreen:new {
	id = "would_do_anything",
	leftDialog = "@conversation/victor_questp_slums:s_41330c9c", -- I will help you as well as I can. What do you need? Oh? I would do anything for Victor. I'd be happy to write my account of the happenings for you. Luckily, I know how to write. Victor funded my education as well. He's done so much for us. Give me a second..
	stopConversation = "false",
	options = {
	--{"@conversation/victor_questp_slums:s_67e6df55", ""}, -- Okay.
	}
}
victorQuestpSlumsConvoTemplate:addScreen(would_do_anything);

give_evidence = ConvoScreen:new {
	id = "give_evidence",
	leftDialog = "@conversation/victor_questp_slums:s_22977a6d", -- Done! Please take this written testimony. I hope it helps you and, most of all, helps Victor. I hope you have a good day.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(give_evidence);

inv_full = ConvoScreen:new {
	id = "inv_full",
	leftDialog = "@conversation/victor_questp_slums:s_4f9d0087", -- Please take this written testimony--oh wait. You don't have enough room to accept it. Hmm... you should come back when you do.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(inv_full);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/victor_questp_slums:s_f8cdce4", -- I can barely go outside anymore to do my chores. I fear for my child. I don't want him to be kidnapped again. An election should be coming up soon. I'd choose Victor Visalis. He would keep us poor citizens safe.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(init_office_phase);

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/victor_questp_slums:s_dcb207ac", -- I don't recognize you. You don't belong in this part of town. I hear there's a lot of commotion at the capitol. Something about an election. You should go and see what it's all about.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(init_election_phase);

init_already_has_evidence = ConvoScreen:new {
	id = "init_already_has_evidence",
	leftDialog = "@conversation/victor_questp_slums:s_4117e563", -- Why are you back? I've already given you my testimony. Why haven't you shown it to the governor? What are you waiting for? She needs to know this.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(init_already_has_evidence);

init_inv_was_full = ConvoScreen:new {
	id = "init_inv_was_full",
	leftDialog = "@conversation/victor_questp_slums:s_b6d2944c", -- I'm glad you've returned. Did you want your evidence now? I hope you have enough room.
	stopConversation = "false",
	options = {
	--{"@conversation/victor_questp_slums:s_ee6997ba", "great_man"}, -- I do, thank you.
	--{"@conversation/victor_questp_slums:s_76cc19da", "come_back_later"}, -- No, I still don't have room.
	}
}
victorQuestpSlumsConvoTemplate:addScreen(init_inv_was_full);

was_full_give_evidence = ConvoScreen:new {
	id = "was_full_give_evidence",
	leftDialog = "@conversation/victor_questp_slums:s_b8dac377", -- I'm so glad! Please take this testimony. I wish you well in your life!
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(was_full_give_evidence);

inv_still_full = ConvoScreen:new {
	id = "inv_still_full",
	leftDialog = "@conversation/victor_questp_slums:s_585b9214", -- Oh no. You don't have enough room again. Please come back when you do. I hope to see you soon.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(inv_still_full);

come_back_later = ConvoScreen:new {
	id = "come_back_later",
	leftDialog = "@conversation/victor_questp_slums:s_6ec1e03e", -- Okay then, come back later when you have more room.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(come_back_later);

addConversationTemplate("victorQuestpSlumsConvoTemplate", victorQuestpSlumsConvoTemplate);
