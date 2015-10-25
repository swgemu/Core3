trialsPadawanSobStory01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanSobStory01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_sob_story_01:s_4c1008a4", -- Oh good, you are already here.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_36a4e374", "intro_more"} -- Yes, I am.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(intro);

intro_more = ConvoScreen:new {
	id = "intro_more",
	leftDialog = "@conversation/padawan_sob_story_01:s_dbff867f", -- You are here to help find my brother right?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_390df542", "more_done"}, -- Um.. yeah. That is exactly why I'm here.
		{"@conversation/padawan_sob_story_01:s_f89b1ce4", "maybe_more"}, -- No, not exactly.
		{"@conversation/padawan_sob_story_01:s_d3249f0b", "not_more"} -- I'm here, but why would I want to help you. Jump off.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(intro_more);

more_done = ConvoScreen:new {
	id = "more_done",
	leftDialog = "@conversation/padawan_sob_story_01:s_83d29997", -- Lies don't score you any points.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(more_done);

not_more = ConvoScreen:new {
	id = "not_more",
	leftDialog = "@conversation/padawan_sob_story_01:s_5bd31ce", -- I see. Then go. And thanks for nothing.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(not_more);

maybe_more = ConvoScreen:new {
	id = "maybe_more",
	leftDialog = "@conversation/padawan_sob_story_01:s_72071926", -- Good, because I could care less about that wasted soul. I just want the blaster he stole from me back. You willing to help?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_1cf278e9", "maybe_more_too"}, -- I will help you find your brother.
		{"@conversation/padawan_sob_story_01:s_297f30e9", "more_too"}, -- I'm here, and yes, willing to help you.
		{"@conversation/padawan_sob_story_01:s_94c910a4", "maybe_more_not"} -- I would rather kiss a Gamorrean.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(maybe_more);

more_too = ConvoScreen:new {
	id = "more_too",
	leftDialog = "@conversation/padawan_sob_story_01:s_986473", -- My brother went out with a group of his friends last week, and has yet to return. Neither has any of his friends.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_9a6c3b2a", "more_too_again"} -- Sounds like he's dead. Sorry to break the news to you.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(more_too);

more_too_again = ConvoScreen:new {
	id = "more_too_again",
	leftDialog = "@conversation/padawan_sob_story_01:s_4f7b1e26", -- That's not what I'm worried about. He took my father's blaster with him. I want that thing back.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_9525d947", "more_more_again"} -- So go and get it.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(more_too_again);

more_more_again = ConvoScreen:new {
	id = "more_more_again",
	leftDialog = "@conversation/padawan_sob_story_01:s_b6e31aa4", -- Believe me, I would if I could. Sadly I have other obligations, like standing here sending smart mouthed adventurers out to their most certain doom. You going to help? Or just continue to grace me with your, oh so precious presence... and stench.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_a128b86a", "maybe_more_more"}, -- Your charm has won me over, how can I help?
		{"@conversation/padawan_sob_story_01:s_290ad18b", "not_more"} -- No, I'm afraid I've had enough of you as well. Good bye.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(more_more_again);

maybe_more_not = ConvoScreen:new {
	id = "maybe_more_not",
	leftDialog = "@conversation/padawan_sob_story_01:s_360d601b", -- That could be arranged. Forget I asked.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(maybe_more_not);

maybe_more_too = ConvoScreen:new {
	id = "maybe_more_too",
	leftDialog = "@conversation/padawan_sob_story_01:s_182378be", -- Please, I could care less about that waste of space. I just want the blaster he took back. The blaster belonged to my father and he had no right to take it with him, the thing was an antique and didn't even work. To tell you the truth, I would be more surprised if my brother was still alive.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_ab866ec6", "maybe_more_again"} -- Now I'm confused.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(maybe_more_too);

maybe_more_again = ConvoScreen:new {
	id = "maybe_more_again",
	leftDialog = "@conversation/padawan_sob_story_01:s_6f0025f1", -- So are you, or are you not, here to help me.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_6845d2f7", "maybe_more_more"}, -- Yeah, I have some time to spare.
		{"@conversation/padawan_sob_story_01:s_2438dea0", "not_more_again"} -- I've decided you're a lunatic, lady, and probably don't even have a brother.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(maybe_more_again);

maybe_more_more = ConvoScreen:new {
	id = "maybe_more_more",
	leftDialog = "@conversation/padawan_sob_story_01:s_be83966b", -- Good. My brother and his friends were talking all last week about going camping somewhere in the wild. My brother, or his corpse, should be somewhere in the area where they were camping. The blaster should be with him. Get it and bring it back to me.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(maybe_more_more);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_sob_story_01:s_45240d04", -- Why are you back without the blaster?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_b7139d72", "continue_on"}, -- Where else would I be?
		{"@conversation/padawan_sob_story_01:s_e6ae286a", "continue_on"}, -- I'm working on it. Not quite finished yet.
		{"@conversation/padawan_sob_story_01:s_2438dea0", "not_more_too"} -- I've decided you're a lunatic, lady, and probably don't even have a brother.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(back_notdone);

not_more_too = ConvoScreen:new {
	id = "not_more_too",
	leftDialog = "@conversation/padawan_sob_story_01:s_10163a72", -- You will not be missed.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(not_more_too);

not_more_again = ConvoScreen:new {
	id = "not_more_again",
	leftDialog = "@conversation/padawan_sob_story_01:s_2e220ef9", -- You are not the only one.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(not_more_again);

continue_on = ConvoScreen:new {
	id = "continue_on",
	leftDialog = "@conversation/padawan_sob_story_01:s_e2b8c011", -- Just hurry up and get me that blaster before someone else makes off with it.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(continue_on);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_sob_story_01:s_3d146002", -- Do you have the blaster? Were you able to find it?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_da7087d0", "back_done_more"} -- Yes, I found his remains and the blaster in the area you expected.
	}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(back_done);

back_done_more = ConvoScreen:new {
	id = "back_done_more",
	leftDialog = "@conversation/padawan_sob_story_01:s_ed0b42f4", -- I figured as much, well, you are smarter than you look. See you around.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(back_done_more);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_sob_story_01:s_202dc610", -- More the fool am I. I should have stopped him. Or something. Now he's gone and he took it with him. Yes, quite the fool.
	stopConversation = "true",
	options = {}
}
trialsPadawanSobStory01ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanSobStory01ConvoTemplate", trialsPadawanSobStory01ConvoTemplate);
