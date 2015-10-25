trialsPadawanChef01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanChef01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_chef_01:s_58e01006", -- He took it.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_a7c3aea6", "intrigued"}, -- Who took what?
		{"@conversation/padawan_chef_01:s_9bcbdc35", "ignored"} -- Good for him.
	}
}
trialsPadawanChef01ConvoTemplate:addScreen(intro);

intrigued = ConvoScreen:new {
	id = "intrigued",
	leftDialog = "@conversation/padawan_chef_01:s_959fc17d", -- Some random thug came by here, and took my latest creation. It was a fantastic pie, and I won't be able to make another of its grandeur for quite some time. I put my heart and soul into that pie.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_94e89675", "sympathy"}, -- That is one sad story.
		{"@conversation/padawan_chef_01:s_1ba9c89d", "ignored_again"} -- I don't care, I'm glad he took it.
	}
}
trialsPadawanChef01ConvoTemplate:addScreen(intrigued);

ignored = ConvoScreen:new {
	id = "ignored",
	leftDialog = "@conversation/padawan_chef_01:s_56b146aa", -- Now, that was uncalled for.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_78228c87", "intrigued"}, -- You are right, I'm sorry. Who took what?
		{"@conversation/padawan_chef_01:s_1ba9c89d", "ignored_again"} -- I don't care, I'm glad he took it.
	}
}
trialsPadawanChef01ConvoTemplate:addScreen(ignored);

ignored_again = ConvoScreen:new {
	id = "ignored_again",
	leftDialog = "@conversation/padawan_chef_01:s_8cddb8eb", -- Arrrgh. You... you're just cruel. Taking pleasure in another's misfortune.
	stopConversation = "true",
	options = {}
}
trialsPadawanChef01ConvoTemplate:addScreen(ignored_again);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_chef_01:s_e15ebf39", -- It's not fair. Not at all. I hate everyone.
	stopConversation = "true",
	options = {}
}
trialsPadawanChef01ConvoTemplate:addScreen(noquest_player_talks);

sympathy = ConvoScreen:new {
	id = "sympathy",
	leftDialog = "@conversation/padawan_chef_01:s_8a0862a1", -- It sure is. The pie is long gone, I can feel it in my blood. What I want is revenge. Revenge is the only thing that will taste as sweet as my precious lost pie. Are you willing to help?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_d70dba34", "accept"}, -- Yes.
		{"@conversation/padawan_chef_01:s_4c695dbd", "decline"} -- No.
	}
}
trialsPadawanChef01ConvoTemplate:addScreen(sympathy);

accept = ConvoScreen:new {
	id = "accept",
	leftDialog = "@conversation/padawan_chef_01:s_b654720c", -- I chased the thug all the way to the edge of town. He ran off into the wilderness, and I quickly lost sight of him. But I managed to at least tag him with a small burst tracking device, so I know where you can find the bum. Destroy him.
	stopConversation = "true",
	options = {}
}
trialsPadawanChef01ConvoTemplate:addScreen(accept);

decline = ConvoScreen:new {
	id = "decline",
	leftDialog = "@conversation/padawan_chef_01:s_f68302e8", -- But you must... you have no choice, don't you see. Help me get my revenge. I need revenge! You must!! Arrrrrrgggh...
	stopConversation = "true",
	options = {}
}
trialsPadawanChef01ConvoTemplate:addScreen(decline);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_chef_01:s_39d844c", -- Is it over? Has that thug paid the price I asked?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_bc5c7c4a", "notdone_more"}, -- Not just yet. I'm still working on it.
		{"@conversation/padawan_chef_01:s_3f4dfda1", "decline_again"} -- No but I'm done. I'm not going to help you seek revenge.
	}
}
trialsPadawanChef01ConvoTemplate:addScreen(back_notdone);

notdone_more = ConvoScreen:new {
	id = "notdone_more",
	leftDialog = "@conversation/padawan_chef_01:s_d5ab69d1", -- Okay. Don't waste too much time I don't know how long until he discovers that tracking device.
	stopConversation = "true",
	options = {}
}
trialsPadawanChef01ConvoTemplate:addScreen(notdone_more);

decline_again = ConvoScreen:new {
	id = "decline_again",
	leftDialog = "@conversation/padawan_chef_01:s_7c44e561", -- What?? I can't... ah no, my sweet revenge!??!
	stopConversation = "true",
	options = {}
}
trialsPadawanChef01ConvoTemplate:addScreen(decline_again);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_chef_01:s_236213e1", -- So? Tell me what happened. Did he die painfully?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_01:s_53e26aec", "refused"}, -- No. I didn't hurt him. I'll not exact your petty revenge.
		{"@conversation/padawan_chef_01:s_7c9388b6", "killed"} -- Yes. He died screaming like a newborn bantha and begging for his life.
	}
}
trialsPadawanChef01ConvoTemplate:addScreen(back_done);

refused = ConvoScreen:new {
	id = "refused",
	leftDialog = "@conversation/padawan_chef_01:s_9bf6042f", -- But?!! No!!!! I want my revenge! I must have it! My precious vengeance! Who are you to stand in my way. Well, drat.
	stopConversation = "true",
	options = {}
}
trialsPadawanChef01ConvoTemplate:addScreen(refused);

killed = ConvoScreen:new {
	id = "killed",
	leftDialog = "@conversation/padawan_chef_01:s_edc10a84", -- My hero. Ah sweet and glorious day!
	stopConversation = "true",
	options = {}
}
trialsPadawanChef01ConvoTemplate:addScreen(killed);

addConversationTemplate("trialsPadawanChef01ConvoTemplate", trialsPadawanChef01ConvoTemplate);
