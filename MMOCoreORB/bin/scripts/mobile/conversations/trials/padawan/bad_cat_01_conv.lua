trialsPadawanBadCat01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanBadCat01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_bad_cat_01:s_93b5b885", -- We have a slight problem.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_799aee03", "interested"}, -- Oh we do, do we?
		{"@conversation/padawan_bad_cat_01:s_34fc22c8", "snarky"} -- No, I think you have a problem.
	}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(intro);

interested = ConvoScreen:new {
	id = "interested",
	leftDialog = "@conversation/padawan_bad_cat_01:s_913dffdc", -- My pet, a fairly large cat, was spooked during a live performance earlier this evening. It leapt right at my good friend, who was performing with me, and went for his throat. My friend is in bad shape, however, the real problem is that our cat is on the loose outside the city limits. Could you possibly help me resolve this most unfortunate of accidents?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_8b81f489", "going"}, -- Yes I'll do what I can.
		{"@conversation/padawan_bad_cat_01:s_ecd38d6b", "decline"} -- No. Please. Why would I care?
	}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(interested);

going = ConvoScreen:new {
	id = "going",
	leftDialog = "@conversation/padawan_bad_cat_01:s_3aa5b0e8", -- I don't think the cat meant any harm, but those animals don't realize how much damage they can do.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_908b3b7a", "going_more"} -- What do you want me to do about it?
	}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(going);

going_more = ConvoScreen:new {
	id = "going_more",
	leftDialog = "@conversation/padawan_bad_cat_01:s_5455041", -- Find the cat, and ermm... take the necessary steps to make sure this never happens again. I realize that will mean killing the cat, but I don't know that there are any alternative.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_d36ab1ec", "going_again"} -- Don't worry... I'll do what needs to be done.
	}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(going_more);

going_again = ConvoScreen:new {
	id = "going_again",
	leftDialog = "@conversation/padawan_bad_cat_01:s_ddfbf107", -- Thank you. I have uploaded the cat's last known location to your datapad. Return here once this is all behind us.
	stopConversation = "true",
	options = {}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(going_again);

snarky = ConvoScreen:new {
	id = "snarky",
	leftDialog = "@conversation/padawan_bad_cat_01:s_1ca2724b", -- Too true, well my best friend is the one with the biggest problem. Our tamed cat was spooked during one of our live performances, sending it in a mad fury towards my best friend's throat. That friend is in bad shape, however, the real problem is our cat is loose outside the city limits.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_908b3b7a", "going_more"}, -- What do you want me to do about it?
		{"@conversation/padawan_bad_cat_01:s_ff470431", "decline"} -- As I said, I think this problem is yours alone. I don't care.
	}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(snarky);

decline = ConvoScreen:new {
	id = "decline",
	leftDialog = "@conversation/padawan_bad_cat_01:s_72bfd7f8", -- We did truly need your help. Now I don't know what to do.
	stopConversation = "true",
	options = {}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(decline);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_bad_cat_01:s_5b82e205", -- Have you taken care of our problem?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_6077d5", "notdone_more"}, -- Not yet, but I will.
		{"@conversation/padawan_bad_cat_01:s_ee242807", "decline"} -- No, and I've decided I'm not going to. Deal with it yourself.
	}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(back_notdone);

notdone_more = ConvoScreen:new {
	id = "notdone_more",
	leftDialog = "@conversation/padawan_bad_cat_01:s_d3af9eee", -- Please hurry.
	stopConversation = "true",
	options = {}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(notdone_more);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_bad_cat_01:s_89952c29", -- Tell me it's all over.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_5ffd7e8f", "done_more"} -- It is. The cat has been taken care of.
	}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(back_done);

done_more = ConvoScreen:new {
	id = "done_more",
	leftDialog = "@conversation/padawan_bad_cat_01:s_b4aeaba0", -- [pause] I'm glad it's over. Thank you for your help. I owe you my gratitude.
	stopConversation = "true",
	options = {}
}
trialsPadawanBadCat01ConvoTemplate:addScreen(done_more);

addConversationTemplate("trialsPadawanBadCat01ConvoTemplate", trialsPadawanBadCat01ConvoTemplate);
