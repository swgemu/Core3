trialsPadawanOldMusician02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanOldMusician02ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_old_musician_02:s_cefcce06", -- Yes? Are you talking to me?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_83a3fa55", "curious"} -- Do you know an old man by the name of Grizzlo?
	}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(intro);

curious = ConvoScreen:new {
	id = "curious",
	leftDialog = "@conversation/padawan_old_musician_02:s_8593cffc", -- Old Grizzy? Sure, I've heard of him. Didn't he die a few years back?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_71918486", "continue"}, -- No, he is very much alive. Well, sort of.
		{"@conversation/padawan_old_musician_02:s_e9a5dbe", "continue_dark"} -- I'm digging up his past before they start digging his grave.
	}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(curious);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/padawan_old_musician_02:s_c8ad3417", -- Who'da guessed that. Well, what do you need to know about Ol' Grizzy Two Tune?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_3ce5abed", "continue_more"}, -- Grizzy Two Tune?
		{"@conversation/padawan_old_musician_02:s_51ea4418", "continue_stop"} -- Never mind, I don't think I care any more.
	}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(continue);

continue_stop = ConvoScreen:new {
	id = "continue_stop",
	leftDialog = "@conversation/padawan_old_musician_02:s_284c1131", -- Whatever you say. Not like it makes any difference to me.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(continue_stop);

continue_dark = ConvoScreen:new {
	id = "continue_dark",
	leftDialog = "@conversation/padawan_old_musician_02:s_d920c8d", -- You have quite the morbid sense of humor don't yah? Well, what do you need to know about Ol' Grizzy Two Tune?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_3ce5abed", "continue_more"}, -- Grizzy Two Tune?
		{"@conversation/padawan_old_musician_02:s_60181c57", "continue_done"} -- Never mind, I've decided I don't care.
	}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(continue_dark);

continue_done = ConvoScreen:new {
	id = "continue_done",
	leftDialog = "@conversation/padawan_old_musician_02:s_46660c8b", -- Whatever you say. You were the one asking questions.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(continue_done);

continue_more = ConvoScreen:new {
	id = "continue_more",
	leftDialog = "@conversation/padawan_old_musician_02:s_bdb08f0b", -- That's what they used to call him; his band didn't know more than two tunes. Truth is the tunes they did play were something else; I don't think their popularity ever spread off world though. Need to know anything else?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_8db3d0fb", "continue_accept"}, -- Do you know where I can find the other band members?
		{"@conversation/padawan_old_musician_02:s_c7d951f7", "continue_decline"} -- I think I've exceed my interest in this whole thing. Forget about it.
	}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(continue_more);

continue_accept = ConvoScreen:new {
	id = "continue_accept",
	leftDialog = "@conversation/padawan_old_musician_02:s_d80ca537", -- I've heard one or two of them moved to Lok about twenty some years ago, though it's been quite a while since I've heard from any them. I fear age may have caught up with them sooner than our friend Grizzlo. I know a musician at the cantina on Lok near Nym's stronghold. He would know if any of those guys are still around. Look for Vixur Webb there.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(continue_accept);

continue_decline = ConvoScreen:new {
	id = "continue_decline",
	leftDialog = "@conversation/padawan_old_musician_02:s_26888d70", -- It's forgotten. Like you've never been here. Really, who are you?
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(continue_decline);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_old_musician_02:s_58a6b3", -- These stories never change friend. Is that all you needed to know?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_cf3cdb9a", "back_story"} -- Why did they break up if they were so popular?
	}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(back_notdone);

back_story = ConvoScreen:new {
	id = "back_story",
	leftDialog = "@conversation/padawan_old_musician_02:s_b38f136f", -- The band had some sort of falling out, I'm sure it was over a girl. Tad bit cliche, eh?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_fafa8703", "continue_accept"} -- Yeah, but that doesn't surprise me.
	}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(back_story);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_old_musician_02:s_5d25f30f", -- Beep boop bop bop... yeah, play that thing.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician02ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanOldMusician02ConvoTemplate", trialsPadawanOldMusician02ConvoTemplate);
