padawan_sob_story_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_sob_story_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_sob_story_01:s_4c1008a4", -- Oh good, you are already here.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_36a4e374", "help_find_brother"}, -- Yes, I am.
		{"@conversation/padawan_sob_story_01:s_b7139d72", "im_confused"} -- Where else would I be?
	}
}
padawan_sob_story_01_convo_template:addScreen(intro);

im_confused = ConvoScreen:new {
	id = "im_confused",
	leftDialog = "@conversation/padawan_sob_story_01:s_ab866ec6", -- Now I'm confused.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_2e220ef9", "are_you_here_to_help"}, -- You are not the only one.
	}
}
padawan_sob_story_01_convo_template:addScreen(im_confused);

are_you_here_to_help = ConvoScreen:new {
	id = "are_you_here_to_help",
	leftDialog = "@conversation/padawan_sob_story_01:s_6f0025f1", -- So are you, or are you not, here to help me.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_297f30e9", "yet_to_return"}, -- I'm here, and yes, willing to help you.
		{"@conversation/padawan_sob_story_01:s_d3249f0b", "smarter_than_you_look"}, -- I'm here, but why would I want to help you. Jump off.
	}
}
padawan_sob_story_01_convo_template:addScreen(are_you_here_to_help);

smarter_than_you_look = ConvoScreen:new {
	id = "smarter_than_you_look",
	leftDialog = "@conversation/padawan_sob_story_01:s_ed0b42f4", -- I figured as much, well, you are smarter than you look.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(smarter_than_you_look);

help_find_brother = ConvoScreen:new {
	id = "help_find_brother",
	leftDialog = "@conversation/padawan_sob_story_01:s_dbff867f", -- You are here to help find my brother right?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_390df542", "no_lies"}, -- Um.. yeah.  That is exactly why I'm here.
		{"@conversation/padawan_sob_story_01:s_f89b1ce4", "just_want_blaster"} -- No, not exactly.
	}
}
padawan_sob_story_01_convo_template:addScreen(help_find_brother);

no_lies = ConvoScreen:new {
	id = "no_lies",
	leftDialog = "@conversation/padawan_sob_story_01:s_83d29997", -- Lies don't score you any points.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_291d0c7a", "yet_to_return"}, -- Well, if that's the case, what are you talking about?
		{"@conversation/padawan_sob_story_01:s_8de1965a", "sure_you_do"} -- That's a shame, but I'm off.  I have things to do that I actually care about.
	}
}
padawan_sob_story_01_convo_template:addScreen(no_lies);

yet_to_return = ConvoScreen:new {
	id = "yet_to_return",
	leftDialog = "@conversation/padawan_sob_story_01:s_ae1fd723", -- My brother went out with a group of his friends last week, and has yet to return. Neither have any of his friends.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_d4cfb5b8", "could_care_less"}, -- I will find your brother.
		{"@conversation/padawan_sob_story_01:s_9a6c3b2a", "not_worried"} -- Sounds like he's dead.  Sorry to break the news to you.
	}
}
padawan_sob_story_01_convo_template:addScreen(yet_to_return);

not_worried = ConvoScreen:new {
	id = "not_worried",
	leftDialog = "@conversation/padawan_sob_story_01:s_4f7b1e26", -- That's not what I'm worried about.  He took my father's blaster with him.  I want that thing back.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_5bdbb8de", "somewhere_in_wild"}, -- Where can I find him?
	}
}
padawan_sob_story_01_convo_template:addScreen(not_worried);

could_care_less = ConvoScreen:new {
	id = "could_care_less",
	leftDialog = "@conversation/padawan_sob_story_01:s_182378be", -- Please, I could care less about that waste of space. I just want the blaster he took back. The blaster belonged to my father and he had no right to take it with him, the thing was an antique and didn't even work. To tell you the truth, I would be more surprised if my brother was still alive.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_5bdbb8de", "somewhere_in_wild"}, -- Where can I find him?
		{"@conversation/padawan_sob_story_01:s_9525d947", "would_if_could"} -- So go and get it.
	}
}
padawan_sob_story_01_convo_template:addScreen(could_care_less);

would_if_could = ConvoScreen:new {
	id = "would_if_could",
	leftDialog = "@conversation/padawan_sob_story_01:s_b6e31aa4", -- 	Believe me, I would if I could. Sadly I have other obligations, like standing here sending smart mouthed adventurers out to their most certain doom. You going to help? Or just continue to grace me with your, oh so precious presence... and stench.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_a128b86a", "going_camping"}, -- Your charm has won me over, how can I help?
		{"@conversation/padawan_sob_story_01:s_290ad18b", "wont_be_missed"} -- No, I'm afraid I've had enough of you as well.  Good bye.
	}
}
padawan_sob_story_01_convo_template:addScreen(would_if_could);

wont_be_missed = ConvoScreen:new {
	id = "wont_be_missed",
	leftDialog = "@conversation/padawan_sob_story_01:s_10163a72", -- You will not be missed.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(wont_be_missed);

somewhere_in_wild = ConvoScreen:new {
	id = "somewhere_in_wild",
	leftDialog = "@conversation/padawan_sob_story_01:s_b7015989", -- My brother and his friends were talking all last week about going camping somewhere in the wild. My brother, or his corpse, should be somewhere in the area where they were camping. The blaster should be with him. Get it and bring it back to me.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(somewhere_in_wild);

sure_you_do = ConvoScreen:new {
	id = "sure_you_do",
	leftDialog = "@conversation/padawan_sob_story_01:s_164cf4c2", -- Right, I'm sure you do.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(sure_you_do);

just_want_blaster = ConvoScreen:new {
	id = "just_want_blaster",
	leftDialog = "@conversation/padawan_sob_story_01:s_72071926", -- Good, because I could care less about that wasted soul. I just want the blaster he stole from me back. You willing to help?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_6845d2f7", "going_camping"}, -- Yeah, I have some time to spare.
		{"@conversation/padawan_sob_story_01:s_94c910a4", "forget_i_asked"} -- I would rather kiss a Gamorrean.
	}
}
padawan_sob_story_01_convo_template:addScreen(just_want_blaster);

going_camping = ConvoScreen:new {
	id = "going_camping",
	leftDialog = "@conversation/padawan_sob_story_01:s_be83966b", -- Good. My brother and his friends were talking all last week about going camping somewhere in the wild. My brother, or his corpse, should be somewhere in the area where they were camping. The blaster should be with him. Get it and bring it back to me.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(going_camping);

forget_i_asked = ConvoScreen:new {
	id = "forget_i_asked",
	leftDialog = "@conversation/padawan_sob_story_01:s_360d601b", -- That could be arranged.  Forget I asked.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(forget_i_asked);

intro_found_target = ConvoScreen:new {
	id = "intro_found_target",
	leftDialog = "@conversation/padawan_sob_story_01:s_3d146002", -- Do you have the blaster? Were you able to find it?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_da7087d0", "please_excuse_me"}, -- Yes, I found his remains and the blaster in the area you expected.
	}
}
padawan_sob_story_01_convo_template:addScreen(intro_found_target);

please_excuse_me = ConvoScreen:new {
	id = "please_excuse_me",
	leftDialog = "@conversation/padawan_sob_story_01:s_91b4a77f", -- Good. Good. I... thank you. This is hitting me harder than I thought it would. Please excuse me.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(please_excuse_me);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_sob_story_01:s_45240d04", -- Why are you back without the blaster?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_sob_story_01:s_e6ae286a", "hurry_up"}, -- I'm working on it. Not quite finished yet.
		{"@conversation/padawan_sob_story_01:s_2438dea0", "thanks_for_nothing"} -- I've decided you're a lunatic, lady, and probably don't even have a brother.
	}
}
padawan_sob_story_01_convo_template:addScreen(intro_in_progress);

hurry_up = ConvoScreen:new {
	id = "hurry_up",
	leftDialog = "@conversation/padawan_sob_story_01:s_e2b8c011", -- Just hurry up and get me that blaster before someone else makes off with it.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(hurry_up);

thanks_for_nothing = ConvoScreen:new {
	id = "thanks_for_nothing",
	leftDialog = "@conversation/padawan_sob_story_01:s_5bd31ce", -- I see. Then go. And thanks for nothing.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(thanks_for_nothing);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_sob_story_01:s_1f8a26f8", -- This means quite a lot to me. Thank you.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(quest_completed);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_sob_story_01:s_202dc610", -- More the fool am I. I should have stopped him. Or something. Now he's gone and he took it with him. Yes, quite the fool.
	stopConversation = "true",
	options = {}
}
padawan_sob_story_01_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_sob_story_01_convo_template", padawan_sob_story_01_convo_template);
