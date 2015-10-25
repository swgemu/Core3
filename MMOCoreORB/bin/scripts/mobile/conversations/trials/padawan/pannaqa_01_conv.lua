trialsPadawanPannaqa01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanPannaqa01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_pannaqa_01:s_41aab3ed", -- I'm sure someone of your ability will be able to assist me. Do you have a second to spare?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_dd5fc3e4", "curious"}, -- Sure, why not. How can I help?
		{"@conversation/padawan_pannaqa_01:s_fd022a50", "not_curious"} -- No, find some sap to bother with your shallow needs.
	}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(intro);

not_curious = ConvoScreen:new {
	id = "not_curious",
	leftDialog = "@conversation/padawan_pannaqa_01:s_24a1738d", -- I see. I thank you for the consideration you've given and trust that you find your way.
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(not_curious);

curious = ConvoScreen:new {
	id = "curious",
	leftDialog = "@conversation/padawan_pannaqa_01:s_53c84ebd", -- I can't leave the village.. there's far too much to be done at the moment. But I also need a replacement part for my vibro-tiller. Without it, farming is much more difficult. As you can see, we have not had much luck of late trying to grow our crops. Between the harsh environment and the constant attacks of Mellichae's thugs, we have our hands full.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_df607c49", "continue"}, -- I'm listening.
		{"@conversation/padawan_pannaqa_01:s_ed2f6bdb", "dont_continue"} -- What kind of mup do you take me for? I'm not doing you menial labor.
	}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(curious);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/padawan_pannaqa_01:s_194a6a4b", -- Shendo, an extremely unreliable acquaintance of mine was supposed to have delivered it many hours ago but has yet to show up. Would you be willing to find him and retrieve the part? 
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_69af28a6", "continue_more"}, -- I would be more than willing to help.
		{"@conversation/padawan_pannaqa_01:s_ad0eb2bb", "dont_continue"} -- Tasks like this are for the servants, bother someone else.
	}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(continue);

continue_more = ConvoScreen:new {
	id = "continue_more",
	leftDialog = "@conversation/padawan_pannaqa_01:s_bbfeec70", -- Thank you kindly, I'll be here when you return.
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(continue_more);

dont_continue = ConvoScreen:new {
	id = "dont_continue",
	leftDialog = "@conversation/padawan_pannaqa_01:s_72d5a837", -- Sorry for bothering, I didn't mean to offend.
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(dont_continue);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_pannaqa_01:s_6d11135b", -- Did you find Shendo with the vibro-tiller part?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_30546869", "notdone_more"}, -- Not yet, but don't worry... I will.
		{"@conversation/padawan_pannaqa_01:s_b336be8b", "dont_continue"} -- I've decided that you're on your own. Find another servant.
	}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(back_notdone);

notdone_more = ConvoScreen:new {
	id = "notdone_more",
	leftDialog = "@conversation/padawan_pannaqa_01:s_52da7aa", -- Ahh, thank you. Please return when you have the part.
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(notdone_more);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_pannaqa_01:s_b2216c3", -- Do you have the part? Did you find Shendo?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_3a3e0d5d", "done_more"}, -- Yes, Shendo wasn't difficult to find... just to deal with.
		{"@conversation/padawan_pannaqa_01:s_b336be8b", "dont_continue"} -- I've decided that you're on your own. Find another servant.
	}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(back_done);

done_more = ConvoScreen:new {
	id = "done_more",
	leftDialog = "@conversation/padawan_pannaqa_01:s_42e0a11e", -- Thank you so much. Hopefully this will help me get the gardens around here into shape.
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(done_more);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_pannaqa_01:s_1843ab7e", -- One dead tree. That's pretty much all I've got to show for my farming skills. As if I should call them skills even. [*sigh*]
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(noquest_player_talks);

quest_player_returns = ConvoScreen:new {
	id = "quest_player_returns",
	leftDialog = "@conversation/padawan_pannaqa_01:s_be0f3920", -- Now maybe instead of just dead trees, I'll grow some vegetables. Or flowers. Or maybe just more trees.
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa01ConvoTemplate:addScreen(quest_player_returns);

addConversationTemplate("trialsPadawanPannaqa01ConvoTemplate", trialsPadawanPannaqa01ConvoTemplate);
