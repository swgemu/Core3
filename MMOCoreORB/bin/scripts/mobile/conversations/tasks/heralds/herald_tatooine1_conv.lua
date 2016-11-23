heraldTatooine1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "multi_dest_herald_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/heraldtatooine1:s_70ffe9b9", -- You seem a bit... weak. Are you a petty commoner? You must be. Otherwise, you'd have enough sense to stay away from a bounty hunter. What do you want, then?
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_7481bfea", "every_reason"}, -- There's no need to be rude, ma'am.
		{"@conversation/heraldtatooine1:s_11c73436", "youre_daft"}, -- Watch your tone!
	}
}
heraldTatooine1ConvoTemplate:addScreen(init);

every_reason = ConvoScreen:new {
	id = "every_reason",
	leftDialog = "@conversation/heraldtatooine1:s_7133e831", -- I have every reason to be. You have not suffered like I have suffered.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_8026269", "painful_subject"}, -- How have you suffered?
		{"@conversation/heraldtatooine1:s_e03237fd", "desert_worms"}, -- I don't have time for this. Bye!
	}
}
heraldTatooine1ConvoTemplate:addScreen(every_reason);

desert_worms = ConvoScreen:new {
	id = "desert_worms",
	leftDialog = "@conversation/heraldtatooine1:s_74f40f3a", -- May the desert worms rot your soul.
	stopConversation = "true",
	options = {}
}
heraldTatooine1ConvoTemplate:addScreen(desert_worms);

youre_daft = ConvoScreen:new {
	id = "youre_daft",
	leftDialog = "@conversation/heraldtatooine1:s_c5e5fb33", -- Excuse me? You are daft, aren't you? In fact, I'd bet you're so daft you'd be allied with those Tuskens. Tell me I'm right. Please.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_3cf68ea6", "tired_bh"}, -- You're trying to blame something on me.
		{"@conversation/heraldtatooine1:s_d00b322a", "more_sense"}, -- Filthy Tuskens? Never!
	}
}
heraldTatooine1ConvoTemplate:addScreen(youre_daft);

tired_bh = ConvoScreen:new {
	id = "tired_bh",
	leftDialog = "@conversation/heraldtatooine1:s_c7330dee", -- I'm a tired bounty hunter and my patience is lacking. I've been so consumed with killing the Tuskens that I've been left empty, exhausted. But I must destroy them... it is my destiny.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_e3ce72c0", "painful_subject"}, -- Why do you hate them so much?
	}
}
heraldTatooine1ConvoTemplate:addScreen(tired_bh);

painful_subject = ConvoScreen:new {
	id = "painful_subject",
	leftDialog = "@conversation/heraldtatooine1:s_65daca4c", -- It's a painful subject, but if you must know: the Tuskens destroyed my family and I have brought it upon myself to rid Tatooine of their worthless existence.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_14495ea", "how_could_you"}, -- Let me help.
		{"@conversation/heraldtatooine1:s_f48827a8", "shallow_sentiments"}, -- Sad story. I wish I could help.
	}
}
heraldTatooine1ConvoTemplate:addScreen(painful_subject);

shallow_sentiments = ConvoScreen:new {
	id = "shallow_sentiments",
	leftDialog = "@conversation/heraldtatooine1:s_1421ed7f", -- Yeah, thanks. Your sentiments are shallow. Get lost before your fate is like that of the Tuskens... friend.
	stopConversation = "true",
	options = {}
}
heraldTatooine1ConvoTemplate:addScreen(shallow_sentiments);

how_could_you = ConvoScreen:new {
	id = "how_could_you",
	leftDialog = "@conversation/heraldtatooine1:s_21aa21ca", -- How could you help? Unless... you help me fight them. I have two locations in which I heavily hunt these desert fiends. Fort Tusken and the Tusken Village.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_39f16ceb", "loc1"}, -- Where is Fort Tusken?
		{"@conversation/heraldtatooine1:s_66f743cb", "loc2"}, -- Where is the Tusken Village?
	}
}
heraldTatooine1ConvoTemplate:addScreen(how_could_you);

loc1 = ConvoScreen:new {
	id = "loc1", -- Fort Tusken
	leftDialog = "@conversation/heraldtatooine1:s_845c935e", -- I'll download the information into your datapad. It's the most simple of explanations. It should be the exact location. I could find the place with my eyes closed.
	stopConversation = "true",
	options = {}
}
heraldTatooine1ConvoTemplate:addScreen(loc1);

loc2 = ConvoScreen:new {
	id = "loc2", -- Tusken Village
	leftDialog = "@conversation/heraldtatooine1:s_ef7c85cf", -- The information will be downloaded into your datapad. If you find the place, don't bother to come back. I have no reward for you. Good bye.
	stopConversation = "true",
	options = {}
}
heraldTatooine1ConvoTemplate:addScreen(loc2);

more_sense = ConvoScreen:new {
	id = "more_sense",
	leftDialog = "@conversation/heraldtatooine1:s_fd76ac2c", -- You may actually have more sense than a kreetle. All right. I suppose I'll let you live. Filthy Tuskens, you say? I have information regarding the whereabouts of several. Interested?
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_9dbca073", "nothing"}, -- What will it cost me?
		{"@conversation/heraldtatooine1:s_36a4e374", "which_loc"}, -- Yes, I am.
	}
}
heraldTatooine1ConvoTemplate:addScreen(more_sense);

nothing = ConvoScreen:new {
	id = "nothing",
	leftDialog = "@conversation/heraldtatooine1:s_b88d9d9f", -- Nothing. I despise the Tuskens with every moment of my existence. I wouldn't mind hiring a few commoners to ease my woes in destroying them.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_c370ec78", "leave_now"}, -- Fight your own battles.
		{"@conversation/heraldtatooine1:s_1ca645a4", "made_glad"}, -- I suppose I can help.
	}
}
heraldTatooine1ConvoTemplate:addScreen(nothing);

leave_now = ConvoScreen:new {
	id = "leave_now",
	leftDialog = "@conversation/heraldtatooine1:s_68c8ab4e", -- If you do not leave quickly, my next battle will be with you. Leave. Now.
	stopConversation = "true",
	options = {}
}
heraldTatooine1ConvoTemplate:addScreen(leave_now);

which_loc = ConvoScreen:new {
	id = "which_loc",
	leftDialog = "@conversation/heraldtatooine1:s_67880d8b", -- Which location? Tusken Village? Or the bigger target, Fort Tusken.
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_8ac3feb5", "loc2"}, -- Tusken Village.
		{"@conversation/heraldtatooine1:s_dca89f7e", "loc1"}, -- Fort Tusken.
	}
}
heraldTatooine1ConvoTemplate:addScreen(which_loc);

made_glad = ConvoScreen:new {
	id = "made_glad",
	leftDialog = "@conversation/heraldtatooine1:s_886ada99", -- You've made a tired bounty hunter glad. Which location do you wish to hear of? Tusken Village or Fort Tusken?
	stopConversation = "false",
	options = {
		{"@conversation/heraldtatooine1:s_8ac3feb5", "loc2"}, -- Tusken Village.
		{"@conversation/heraldtatooine1:s_dca89f7e", "loc1"}, -- Fort Tusken.
	}
}
heraldTatooine1ConvoTemplate:addScreen(made_glad);

addConversationTemplate("heraldTatooine1ConvoTemplate", heraldTatooine1ConvoTemplate);
