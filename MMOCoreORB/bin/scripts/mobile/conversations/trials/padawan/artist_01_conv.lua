trialsPadawanArtist01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanArtist01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_artist_01:s_28225432", -- Where is my assistant with those supplies. Arrgh, this is becoming annoying.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_a51658ea", "wonder_greet"} -- Excuse me?
	}
}
trialsPadawanArtist01ConvoTemplate:addScreen(intro);

wonder_greet = ConvoScreen:new {
	id = "wonder_greet",
	leftDialog = "@conversation/padawan_artist_01:s_76f9d659", -- I'm an aspiring artist working on some paintings using natural materials as the base for my paints. The texture and brilliance of the colors I get using them echoes the emotions I try to express in my work. I sent my assistant out to retrieve some more supplies but he has yet to return.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_bdf1fbc8", "choose_help"}, -- Sounds... interesting.
		{"@conversation/padawan_artist_01:s_81192d80", "choose_hate"} -- Lady, you're a freak. Get a real job and leave the rest of us alone.
	}
}
trialsPadawanArtist01ConvoTemplate:addScreen(wonder_greet);

choose_help = ConvoScreen:new {
	id = "choose_help",
	leftDialog = "@conversation/padawan_artist_01:s_5e1dfbcd", -- Yes... you see if I don't get the supplies I need to make the paints I'm afraid I will not be able to finish my paintings. Which means my patrons will not receive those paintings and will therefore not pay me. This in turn means I won't be able to pay my bills.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_f9a16624", "choose_help_too"}, -- I get the picture. What can I do to help?
		{"@conversation/padawan_artist_01:s_a8a01106", "choose_hate"} -- Your excuses are as transparent as a Twi'lek entertainers clothing. Lets both just forget I asked.
	}
}
trialsPadawanArtist01ConvoTemplate:addScreen(choose_help);

choose_hate = ConvoScreen:new {
	id = "choose_hate",
	leftDialog = "@conversation/padawan_artist_01:s_a95dd416", -- What? But... you... I see. Very well. I see how your true colors now.
	stopConversation = "true",
	options = {}
}
trialsPadawanArtist01ConvoTemplate:addScreen(choose_hate);

choose_help_too = ConvoScreen:new {
	id = "choose_help_too",
	leftDialog = "@conversation/padawan_artist_01:s_8bed149", -- My assistant is out collecting a mixture of mud and refuse that is just right for the colors I need. If you could please meet him there and assist him in returning safely I would be ever appreciative. I have given you a waypoint to his location. Please hurry.
	stopConversation = "true",
	options = {}
}
trialsPadawanArtist01ConvoTemplate:addScreen(choose_help_too);

back_not_done = ConvoScreen:new {
	id = "back_not_done",
	leftDialog = "@conversation/padawan_artist_01:s_a1ae198d", -- Have you found my assistant yet?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_593d8ed6", "helping_still"}, -- Not yet. I'm still working on it.
		{"@conversation/padawan_artist_01:s_a0e28661", "choose_hate"} -- No and I'm not going to. Find him yourself.
	}
}
trialsPadawanArtist01ConvoTemplate:addScreen(back_not_done);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_artist_01:s_aad1f131", -- Where is my assistant?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_705f9dd1", "helped_but"}, -- I haven't been able to find your assistant.
		{"@conversation/padawan_artist_01:s_a2c41722", "helped_but_too"} -- I'm afraid your assistant will not be coming back... but I have your supplies.
	}
}
trialsPadawanArtist01ConvoTemplate:addScreen(back_done);

helped_but = ConvoScreen:new {
	id = "helped_but",
	leftDialog = "@conversation/padawan_artist_01:s_cc45360d", -- Did you even try? I'm not sure why I bothered to ask for your help.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_d21432e3", "helped_but_calm"} -- I did get your supplies though.
	}
}
trialsPadawanArtist01ConvoTemplate:addScreen(helped_but);

helped_but_calm = ConvoScreen:new {
	id = "helped_but_calm",
	leftDialog = "@conversation/padawan_artist_01:s_ec321028", -- Oh. Maybe I spoke hastily. But how did you know what to get? [check the supplies] Yes, these all look correct. I'm impressed. Ever think about becoming an artist's assistant?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_bdf1fbc8", "helped_success"} -- Sounds... interesting.
	}
}
trialsPadawanArtist01ConvoTemplate:addScreen(helped_but_calm);

helping_still = ConvoScreen:new {
	id = "helping_still",
	leftDialog = "@conversation/padawan_artist_01:s_78bd6c2", -- Thank you. Let me know when you find him.
	stopConversation = "true",
	options = {}
}
trialsPadawanArtist01ConvoTemplate:addScreen(helping_still);

helped_success = ConvoScreen:new {
	id = "helped_success",
	leftDialog = "@conversation/padawan_artist_01:s_35c6bce6", -- Thank you so much for retrieving my supplies. I'm not sure what I'll do about getting another assistant, but that's something I can worry about later.
	stopConversation = "true",
	options = {}
}
trialsPadawanArtist01ConvoTemplate:addScreen(helped_success);

helped_but_too = ConvoScreen:new {
	id = "helped_but_too",
	leftDialog = "@conversation/padawan_artist_01:s_4f3396fb", -- Oh no, he will. Sorry for not bringing this up before, but it is not the first time he has done this. I know it's not the most glamorous job in the world, but I think a part of him sort of enjoys it. Anyway, thank you for your help and for bringing my supplies.
	stopConversation = "true",
	options = {}
}
trialsPadawanArtist01ConvoTemplate:addScreen(helped_but_too);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_artist_01:s_c4960c85", -- Who are you? Never mind, I think we both know that doesn't matter.
	stopConversation = "true",
	options = {}
}
trialsPadawanArtist01ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanArtist01ConvoTemplate", trialsPadawanArtist01ConvoTemplate);
