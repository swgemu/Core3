padawan_artist_02_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_artist_02_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_artist_02:s_e00a6a73", -- I see she has already found a replacement for me.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_7fb2178f", "told_her_already"} -- I'm just here to get you to return with her supplies.
	}
}
padawan_artist_02_convo_template:addScreen(intro);

told_her_already = ConvoScreen:new {
	id = "told_her_already",
	leftDialog = "@conversation/padawan_artist_02:s_5c12a1a9", -- I've told her already, I'm not fetching her 'mud and refuse' ever again.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_5439ef9", "lost_all_direction"} -- Then why are you digging around in the mud?
	}
}
padawan_artist_02_convo_template:addScreen(told_her_already);

lost_all_direction = ConvoScreen:new {
	id = "lost_all_direction",
	leftDialog = "@conversation/padawan_artist_02:s_70d2d7a8", -- Because... I... I've lost all direction in my life, where do I go from here? There must be something better than fetching dirt and droppings from various places.  But I have nowhere else to go.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_b4b8a975", "dont_have_to_lie"} -- There are plenty of worse professions out there.
	}
}
padawan_artist_02_convo_template:addScreen(lost_all_direction);

dont_have_to_lie = ConvoScreen:new {
	id = "dont_have_to_lie",
	leftDialog = "@conversation/padawan_artist_02:s_f0a76084", -- You don't have to lie to make me feel better.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_b19ae492", "hopes_and_dreams"} -- Sorry...
	}
}
padawan_artist_02_convo_template:addScreen(dont_have_to_lie);

hopes_and_dreams = ConvoScreen:new {
	id = "hopes_and_dreams",
	leftDialog = "@conversation/padawan_artist_02:s_c5493e9b", -- I have hopes and dreams too!  I have talent!
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_cb5a9d1b", "dont_have_it_in_me"} -- Right.. can you just please get back to the delivery?
	}
}
padawan_artist_02_convo_template:addScreen(hopes_and_dreams);

dont_have_it_in_me = ConvoScreen:new {
	id = "dont_have_it_in_me",
	leftDialog = "@conversation/padawan_artist_02:s_e83d11f6", -- No, I don't have it in me.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_artist_02:s_1ed6eefa", "okay_thanks"} -- Then let me return with the paint mixture for you.
	}
}
padawan_artist_02_convo_template:addScreen(dont_have_it_in_me);

okay_thanks = ConvoScreen:new {
	id = "okay_thanks",
	leftDialog = "@conversation/padawan_artist_02:s_26360156", --	Yeah. Okay. Thanks, tell Sathme that I'm sorry.
	stopConversation = "true",
	options = {}
}
padawan_artist_02_convo_template:addScreen(okay_thanks);

no_active_quest = ConvoScreen:new {
	id = "no_active_quest",
	leftDialog = "@conversation/padawan_artist_02:s_a54bac2d", --	I don't care what she thinks... I'm following my own dreams.
	stopConversation = "true",
	options = {}
}
padawan_artist_02_convo_template:addScreen(no_active_quest);

addConversationTemplate("padawan_artist_02_convo_template", padawan_artist_02_convo_template);
