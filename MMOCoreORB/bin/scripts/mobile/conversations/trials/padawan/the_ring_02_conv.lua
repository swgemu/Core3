padawan_the_ring_02_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_the_ring_02_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_the_ring_02:s_6a1562ad", -- What do you want?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_711691ff", "in_it_for_me"}, -- I'm looking for a wedding ring, have you seen one?
		{"@conversation/padawan_the_ring_02:s_443c85ef", "races_to_win"} -- Forty million credits and a penthouse apartment in Coruscant.
	}
}
padawan_the_ring_02_convo_template:addScreen(intro);

races_to_win = ConvoScreen:new {
	id = "races_to_win",
	leftDialog = "@conversation/padawan_the_ring_02:s_f42e101f", -- I've got races to win and chumps to scam.  Answer the question or get out of my face.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_711691ff", "in_it_for_me"}, -- I'm looking for a wedding ring, have you seen one?
	}
}
padawan_the_ring_02_convo_template:addScreen(races_to_win);

in_it_for_me = ConvoScreen:new {
	id = "in_it_for_me",
	leftDialog = "@conversation/padawan_the_ring_02:s_83f28a20", -- Maybe, what is in it for me?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_443c85ef", "thats_funny"}, -- Forty million credits and a penthouse apartment in Coruscant.
	}
}
padawan_the_ring_02_convo_template:addScreen(in_it_for_me);

thats_funny = ConvoScreen:new {
	id = "thats_funny",
	leftDialog = "@conversation/padawan_the_ring_02:s_4f77458a", -- Ha... right. That's funny. You mean this ring? The one I took from Keicho? The one he balked on when it came time to place a bet. I won his landspeeder last week, and his wifes wedding gown the week before that. I love that gown. But he wouldn't bet the ring. Couldn't understand why, so I just took it.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_e4815789", "test_your_luck"}, -- You took it?
	}
}
padawan_the_ring_02_convo_template:addScreen(thats_funny);

test_your_luck = ConvoScreen:new {
	id = "test_your_luck",
	leftDialog = "@conversation/padawan_the_ring_02:s_80764fc6", -- Yeah, and I don't plan on giving it up.  So unless you are willing test your luck and pry it off my cold dead hands I recommend you go back to Keicho and tell him to find some other chump to do his dirty work.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_d38d76e0", "not_getting_ring"}, -- This does not have to get violent.
		{"@conversation/padawan_the_ring_02:s_157b6369", "we_will_see"}, -- Believe me friend, I have far more than luck on my side.
	}
}
padawan_the_ring_02_convo_template:addScreen(test_your_luck);

not_getting_ring = ConvoScreen:new {
	id = "not_getting_ring",
	leftDialog = "@conversation/padawan_the_ring_02:s_cdc241bf", -- Well then it doesn't look like you are going to be returning to your good friend with this here ring.  Unless...
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_759ab6bb", "enough_options"}, -- Unless what?
	}
}
padawan_the_ring_02_convo_template:addScreen(not_getting_ring);

enough_options = ConvoScreen:new {
	id = "enough_options",
	leftDialog = "@conversation/padawan_the_ring_02:s_860ae378", -- Actually, I've given Keicho enough options. Either you fight me for this here ring, or you go back to him empty handed.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_8514b7c5", "good_choice"}, -- I am not willing to solve this with blood shed.  Good bye.
		{"@conversation/padawan_the_ring_02:s_36ab201c", "we_will_see"}, -- If you insist on a fight, I won't back down.
	}
}
padawan_the_ring_02_convo_template:addScreen(enough_options);

we_will_see = ConvoScreen:new {
	id = "we_will_see",
	leftDialog = "@conversation/padawan_the_ring_02:s_77a2c8a3", -- We will see about that.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_02_convo_template:addScreen(we_will_see);

good_choice = ConvoScreen:new {
	id = "good_choice",
	leftDialog = "@conversation/padawan_the_ring_02:s_cd72f93", -- Good choice.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_02_convo_template:addScreen(good_choice);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_the_ring_02:s_ce804243", -- What? Looking for a fight? Not today, chump, but definitely some other time.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_02_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_the_ring_02_convo_template", padawan_the_ring_02_convo_template);
