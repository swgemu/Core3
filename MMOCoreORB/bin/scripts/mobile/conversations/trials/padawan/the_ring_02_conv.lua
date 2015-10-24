trialsPadawanTheRing02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanTheRing02ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_the_ring_02:s_f42e101f", -- I've got races to win and chumps to scam. Answer the question or get out of my face. What do you want?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_711691ff", "intro_more"} -- I'm looking for a wedding ring, have you seen one?
	}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(intro);

intro_more = ConvoScreen:new {
	id = "intro_more",
	leftDialog = "@conversation/padawan_the_ring_02:s_83f28a20", -- Maybe, what is in it for me?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_443c85ef", "more_joke"} -- Forty million credits and a penthouse apartment in Coruscant.
	}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(intro_more);

more_joke = ConvoScreen:new {
	id = "more_joke",
	leftDialog = "@conversation/padawan_the_ring_02:s_4f77458a", -- Ha... right. That's funny. You mean this ring? The one I took from Keicho? The one he balked on when it came time to place a bet. I won his landspeeder last week, and his wifes wedding gown the week before that. I love that gown. But he wouldn't bet the ring. Couldn't understand why, so I just took it.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_e4815789", "more_again"} -- You took it?
	}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(more_joke);

more_again = ConvoScreen:new {
	id = "more_again",
	leftDialog = "@conversation/padawan_the_ring_02:s_80764fc6", -- Yeah, and I don't plan on giving it up. So unless you are willing test your luck and pry it off my cold dead hands I recommend you go back to Keicho and tell him to find some other chump to do his dirty work.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_157b6369", "more_stuff"}, -- Believe me friend, I have far more than luck on my side.
		{"@conversation/padawan_the_ring_02:s_d38d76e0", "more_accept_too"} -- This does not have to get violent.
	}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(more_again);

more_accept_too = ConvoScreen:new {
	id = "more_accept_too",
	leftDialog = "@conversation/padawan_the_ring_02:s_cdc241bf", -- Well then it doesn't look like you are going to be returning to your good friend with this here ring. Unless...
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_759ab6bb", "more_stuff"} -- Unless what?
	}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(more_accept_too);

more_stuff = ConvoScreen:new {
	id = "more_stuff",
	leftDialog = "@conversation/padawan_the_ring_02:s_860ae378", -- Actually, I've given Keicho enough options. Either you fight me for this here ring, or you go back to him empty handed.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_02:s_36ab201c", "more_fight"}, -- If you insist on a fight, I won't back down.
		{"@conversation/padawan_the_ring_02:s_8514b7c5", "more_gone"} -- I am not willing to solve this with blood shed. Good bye.
	}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(more_stuff);

more_gone = ConvoScreen:new {
	id = "more_gone",
	leftDialog = "@conversation/padawan_the_ring_02:s_cd72f93", -- Good choice.
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(more_gone);

more_fight = ConvoScreen:new {
	id = "more_fight",
	leftDialog = "@conversation/padawan_the_ring_02:s_77a2c8a3", -- We will see about that.
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(more_fight);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_the_ring_02:s_ce804243", -- What? Looking for a fight? Not today, chump, but definitely some other time.
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing02ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanTheRing02ConvoTemplate", trialsPadawanTheRing02ConvoTemplate);
