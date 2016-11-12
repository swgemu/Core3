victorQuestpSlumsConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_questp_conv_handler",
	screens = {}
}

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/victor_questp_slums:s_f25283c7", -- I knew you'd come. The story should be told to everyone. It has a good moral to it, I think.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_slums:s_8611417a","convo_start2"}, -- What story?
		{"@conversation/victor_questp_slums:s_aa91e763","questp_notime"}, -- No time for stories.
	 }
}
victorQuestpSlumsConvoTemplate:addScreen(convo_start);

questp_notime = ConvoScreen:new {
	id = "questp_notime",
	leftDialog = "@conversation/victor_questp_slums:s_5a5e0913", -- That's sad. It's a good one. Come back when you're ready to hear it.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(questp_notime);

convo_start2:new {
	id = "convo_start2",
	leftDialog = "@conversation/victor_questp_slums:s_222d159b", -- Listen closely. The Sand People have been attacking the outskirts of the city. For some reason, the Empire has hidden this fact from those who do not live in the slums... not to panic everyone else, I guess. It's hard to live here. One particular night, a couple of months back, the Tuskens came. They killed several of us here. They took my son. I--I just don't want to think about it... about what could have happened that night.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_slums:s_540ac7e9","convo_start3"}, -- Continue.
	}
}
victorQuestpSlumsConvoTemplate:addScreen(convo_start2);

convo_start3 = ConvoScreen:new {
	id = "convo_start3",
	leftDialog = "@conversation/victor_questp_slums:s_41e66644", -- I'm just a poor woman. I'm not significant in this life, or to this city. But Victor Visalis heard of my misfortune and took pity on me. He took his own soldiers and destroyed the Tuskens. He returned my son to me! Can you believe that? I'm so grateful.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_slums:s_d5f19466","convo_start_give"}, -- I need your help.
		{"@conversation/victor_questp_slums:s_a9ac4d51","questp_end"}, -- Nice story. I must be going.
	}
}
victorQuestpSlumsConvoTemplate:addScreen(convo_start3);

convo_start_give = ConvoScreen:new {
	id = "convo_start_give",
	leftDialog = "@conversation/victor_questp_slums:s_41330c9c", -- I will help you as well as I can. What do you need? Oh? I would do anything for Victor. I'd be happy to write my account of the happenings for you. Luckily, I know how to write. Victor funded my education as well. He's done so much for us. Give me a second..
	stopConversation = "false",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(convo_start_give);

no_election = ConvoScreen:new {
	id = "no_election",
	leftDialog = "@conversation/victor_questp_slums:s_f8cdce4", -- I can barely go outside anymore to do my chores. I fear for my child. I don't want him to be kidnapped again. An election should be coming up soon. I'd choose Victor Visalis. He would keep us poor citizens safe.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(no_election);

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/victor_questp_slums:s_dcb207ac", -- I don't recognize you. You don't belong in this part of town. I hear there's a lot of commotion at the capitol. Something about an election. You should go and see what it's all about.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(no_business);

already_has_evidence = ConvoScreen:new {
	id = "already_has_evidence",
	leftDialog = "@conversation/victor_questp_slums:s_4117e563", -- Why are you back? I've already given you my testimony. Why haven't you shown it to the governor? What are you waiting for? She needs to know this.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(already_has_evidence);

noroom = ConvoScreen:new {
	id = "noroom",
	leftDialog = "@conversation/victor_questp_slums:s_4f9d0087", -- Please take this written testimony--oh wait. You don't have enough room to accept it. Hmm... you should come back when you do.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(noroom);

noroom_returned = ConvoScreen:new {
	id = "noroom_returned",
	leftDialog = "@conversation/victor_questp_slums:s_b6d2944c", -- I'm glad you've returned. Did you want your evidence now? I hope you have enough room.
	stopConversation = "false",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(noroom_returned);

noroom_returned_giveitem = ConvoScreen:new {
	id = "noroom_returned_giveitem",
	leftDialog = "@conversation/victor_questp_slums:s_b8dac377", -- I'm so glad! Please take this testimony. I wish you well in your life!
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(noroom_returned_giveitem);

noroom_returned_reply = ConvoScreen:new {
	id = "noroom_returned_reply",
	leftDialog = "@conversation/victor_questp_slums:s_6ec1e03e", -- Okay then, come back later when you have more room.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(noroom_returned_reply);

noroom_returned_noroom = ConvoScreen:new {
	id = "noroom_returned_noroom",
	leftDialog = "@conversation/victor_questp_slums:s_585b9214", -- Oh no. You don't have enough room again. Please come back when you do. I hope to see you soon.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(noroom_returned_noroom);

give_item = ConvoScreen:new {
	id = "give_item",
	leftDialog = "@conversation/victor_questp_slums:s_22977a6d", -- Done! Please take this written testimony. I hope it helps you and, most of all, helps Victor. I hope you have a good day.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(give_item);

questp_end = ConvoScreen:new {
	id = "questp_end",
	leftDialog = "@conversation/victor_questp_slums:s_76f08368", -- I'm glad you liked it! I hope you are well today.
	stopConversation = "true",
	options = {}
}
victorQuestpSlumsConvoTemplate:addScreen(questp_end);

addConversationTemplate("victorQuestpSlumsConvoTemplate", victorQuestpSlumsConvoTemplate);
