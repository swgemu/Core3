trialsPadawanArtist02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanArtist02ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_artist_02:s_e00a6a73", -- I see she has already found a replacement for me.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_e83d11f6", "continued"} -- No, I don't have it in me.
	}
}
trialsPadawanArtist02ConvoTemplate:addScreen(intro);

continued = ConvoScreen:new {
	id = "continued",
	leftDialog = "@conversation/padawan_artist_02:s_f0a76084", -- You don't have to lie to make me feel better.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_7fb2178f", "continued_too"} -- I'm just here to get you to return with her supplies.
	}
}
trialsPadawanArtist02ConvoTemplate:addScreen(continued);

continued_too = ConvoScreen:new {
	id = "continued_too",
	leftDialog = "@conversation/padawan_artist_02:s_5c12a1a9", -- I've told her already, I'm not fetching her 'mud and refuse' ever again.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_5439ef9", "continued_more"} -- Then why are you digging around in the mud?
	}
}
trialsPadawanArtist02ConvoTemplate:addScreen(continued_too);

continued_more = ConvoScreen:new {
	id = "continued_more",
	leftDialog = "@conversation/padawan_artist_02:s_70d2d7a8", -- Because... I... I've lost all direction in my life, where do I go from here? There must be something better than fetching dirt and droppings from various places. But I have nowhere else to go.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_b19ae492", "continued_again"} -- Sorry...
	}
}
trialsPadawanArtist02ConvoTemplate:addScreen(continued_more);

continued_again = ConvoScreen:new {
	id = "continued_again",
	leftDialog = "@conversation/padawan_artist_02:s_a54bac2d", -- I don't care what she thinks... I'm following my own dreams.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_b4b8a975", "continued_ending"} -- There are plenty of worse professions out there.
	}
}
trialsPadawanArtist02ConvoTemplate:addScreen(continued_again);

continued_ending = ConvoScreen:new {
	id = "continued_ending",
	leftDialog = "@conversation/padawan_artist_02:s_c5493e9b", -- I have hopes and dreams too! I have talent!
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_1ed6eefa", "continued_final"} -- 	Then let me return with the paint mixture for you.
	}
}
trialsPadawanArtist02ConvoTemplate:addScreen(continued_ending);

continued_final = ConvoScreen:new {
	id = "continued_final",
	leftDialog = "@conversation/padawan_artist_02:s_26360156", -- Yeah. Okay. Thanks, tell Sathme that I'm sorry. [You take the painting supplies, but decide putting them in your inventory could result in a big mess. So instead you store them someplace safer.]
	stopConversation = "true",
	options = {}
}
trialsPadawanArtist02ConvoTemplate:addScreen(continued_final);

addConversationTemplate("trialsPadawanArtist02ConvoTemplate", trialsPadawanArtist02ConvoTemplate);
