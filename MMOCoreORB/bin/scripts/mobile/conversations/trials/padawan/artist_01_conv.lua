padawan_artist_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_artist_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_artist_01:s_c4960c85", -- Who are you?  Never mind, I think we both know that doesn't matter.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_a51658ea", "aspiring_artist"} -- Excuse me?
	}
}
padawan_artist_01_convo_template:addScreen(intro);

aspiring_artist = ConvoScreen:new {
	id = "aspiring_artist",
	leftDialog = "@conversation/padawan_artist_01:s_76f9d659", -- I'm an aspiring artist working on some paintings using natural materials as the base for my paints.  The texture and brilliance of the colors I get using them echoes the emotions I try to express in my work. 
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_bdf1fbc8", "need_supplies"} -- Sounds... interesting.
	}
}
padawan_artist_01_convo_template:addScreen(aspiring_artist);

need_supplies = ConvoScreen:new {
	id = "need_supplies",
	leftDialog = "@conversation/padawan_artist_01:s_5e1dfbcd", -- Yes... you see if I don't get the supplies I need to make the paints I'm afraid I will not be able to finish my paintings.  Which means my patrons will not receive those paintings and will therefore not pay me. This in turn means I won't be able to pay my bills.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_f9a16624", "meet_assistant"}, -- I get the picture. What can I do to help?
		{"@conversation/padawan_artist_01:s_81192d80", "forget_i_asked"} -- Lady, you're a freak. Get a real job and leave the rest of us alone.
	}
}
padawan_artist_01_convo_template:addScreen(need_supplies);

meet_assistant = ConvoScreen:new {
	id = "meet_assistant",
	leftDialog = "@conversation/padawan_artist_01:s_8bed149", -- My assistant is out collecting a mixture of mud and refuse that is just right for the colors I need.  If you could please meet him there and assist him in returning safely I would be ever appreciative.
	stopConversation = "true",
	options = {}
}
padawan_artist_01_convo_template:addScreen(meet_assistant);

forget_i_asked = ConvoScreen:new {
	id = "forget_i_asked",
	leftDialog = "@conversation/padawan_artist_01:s_a8a01106", -- Your excuses are as transparent as a Twi'lek entertainers clothing.  Lets both just forget I asked.
	stopConversation = "true",
	options = {}
}
padawan_artist_01_convo_template:addScreen(forget_i_asked);

intro_spoke_to_target = ConvoScreen:new {
	id = "intro_spoke_to_target",
	leftDialog = "@conversation/padawan_artist_01:s_aad1f131", -- Where is my assistant?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_705f9dd1", "why_i_bothered"}, -- I haven't been able to find your assistant.
		{"@conversation/padawan_artist_01:s_a2c41722", "not_first_time"} -- I'm afraid your assistant will not be coming back... but I have your supplies.
	}
}
padawan_artist_01_convo_template:addScreen(intro_spoke_to_target);

why_i_bothered = ConvoScreen:new {
	id = "why_i_bothered",
	leftDialog = "@conversation/padawan_artist_01:s_cc45360d", -- Did you even try? I'm not sure why I bothered to ask for your help.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_cc45360d", "spoke_hastily"}, -- I did get your supplies though.
	}
}
padawan_artist_01_convo_template:addScreen(why_i_bothered);

spoke_hastily = ConvoScreen:new {
	id = "spoke_hastily",
	leftDialog = "@conversation/padawan_artist_01:s_ec321028", -- Oh. Maybe I spoke hastily. But how did you know what to get? [check the supplies] Yes, these all look correct. I'm impressed. Ever think about becoming an artist's assistant?
	stopConversation = "true",
	options = {}
}
padawan_artist_01_convo_template:addScreen(spoke_hastily);

not_first_time = ConvoScreen:new {
	id = "not_first_time",
	leftDialog = "@conversation/padawan_artist_01:s_4f3396fb", -- Oh no, he will.  Sorry for not bringing this up before, but it is not the first time he has done this.  I know it's not the most glamorous job in the world, but I think a part of him sort of enjoys it.
	stopConversation = "true",
	options = {}
}
padawan_artist_01_convo_template:addScreen(not_first_time);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_artist_01:s_a1ae198d", -- Have you found my assistant yet?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_01:s_593d8ed6", "let_me_know"}, -- Not yet. I'm still working on it.
		{"@conversation/padawan_artist_01:s_a0e28661", "true_colors"} -- No and I'm not going to. Find him yourself.
	}
}
padawan_artist_01_convo_template:addScreen(intro_in_progress);

true_colors = ConvoScreen:new {
	id = "true_colors",
	leftDialog = "@conversation/padawan_artist_01:s_a95dd416", -- What? But... you... I see. Very well. I see how your true colors now.
	stopConversation = "true",
	options = {}
}
padawan_artist_01_convo_template:addScreen(true_colors);

let_me_know = ConvoScreen:new {
	id = "let_me_know",
	leftDialog = "@conversation/padawan_artist_01:s_78bd6c2", -- Thank you. Let me know when you find him.
	stopConversation = "true",
	options = {}
}
padawan_artist_01_convo_template:addScreen(let_me_know);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_artist_01:s_28225432", -- Where is my assistant with those supplies. Arrgh, this is becoming annoying.
	stopConversation = "true",
	options = {}
}
padawan_artist_01_convo_template:addScreen(not_quest_owner);

completed_quest = ConvoScreen:new {
	id = "completed_quest",
	leftDialog = "@conversation/padawan_artist_01:s_35c6bce6", -- Thank you so much for retrieving my supplies. I'm not sure what I'll do about getting another assistant, but that's something I can worry about later.
	stopConversation = "true",
	options = {}
}
padawan_artist_01_convo_template:addScreen(completed_quest);

addConversationTemplate("padawan_artist_01_convo_template", padawan_artist_01_convo_template);
