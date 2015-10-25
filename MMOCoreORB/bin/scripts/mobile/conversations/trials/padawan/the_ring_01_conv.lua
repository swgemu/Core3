trialsPadawanTheRing01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanTheRing01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_the_ring_01:s_3924c1a9", -- I'm in a tight spot.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_7b35cfbc", "intro_more"} -- What is the problem?
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(intro);

intro_more = ConvoScreen:new {
	id = "intro_more",
	leftDialog = "@conversation/padawan_the_ring_01:s_d1457e5b", -- I sort of borrowed my deceased mother in laws wedding ring from my wife, then I sort of lost it when I was out racing my swoop.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_91971db6", "more_stuff"}, -- That is a tight spot.
		{"@conversation/padawan_the_ring_01:s_7cb3d5a9", "more_accept_joke"} -- 	Should have been more careful.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(intro_more);

more_accept_joke = ConvoScreen:new {
	id = "more_accept_joke",
	leftDialog = "@conversation/padawan_the_ring_01:s_92a6af5a", -- Brilliant! Your incredible skills of deduction amaze me. How much do I owe you for this display of pure ingenious?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_c6898781", "more_again"} -- I'm sorry, it was just a joke.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(more_accept_joke);

more_again = ConvoScreen:new {
	id = "more_again",
	leftDialog = "@conversation/padawan_the_ring_01:s_c2f7ce8", -- It's okay, I'm just a bit wound up. I could truly use your help, if you are willing of course.
	stopConversation = "false",
	options = {		
		{"@conversation/padawan_the_ring_01:s_997d67e4", "more_accept_too"} -- Why not get it yourself?
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(more_again);

more_accept_too = ConvoScreen:new {
	id = "more_accept_too",
	leftDialog = "@conversation/padawan_the_ring_01:s_61a3322c", -- If I'm not here when my wife returns she is sure to suspect I've done something wrong. She had no idea I was going out racing, and if she finds out otherwise... Well lets just say she cannot find out otherwise. Do you have time to help?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_8626b2e6", "accept_too_again"} -- Sure, how can I help you?
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(more_accept_too);

more_stuff = ConvoScreen:new {
	id = "more_stuff",
	leftDialog = "@conversation/padawan_the_ring_01:s_6d739213", -- 	Seriously... If it's not too much to ask do you think you could go out and try to find it for me?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_70c10eb", "accept_too_again"}, -- I would be happy to.
		{"@conversation/padawan_the_ring_01:s_ea66e5db", "more_decline"} -- Sounds dangerous. If there's nothing in it for me, forget it.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(more_stuff);

accept_too_again = ConvoScreen:new {
	id = "accept_too_again",
	leftDialog = "@conversation/padawan_the_ring_01:s_d91ac73", -- Thank you very much, I've uploaded your datapad with the last location I remember having the ring on me.
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(accept_too_again);

more_decline = ConvoScreen:new {
	id = "more_decline",
	leftDialog = "@conversation/padawan_the_ring_01:s_4bbb35f5", -- Coward! Why did I ever think you'd be able to help me anyway. Just go. Maybe I can buy another ring that looks just like it... with the exact same inscription... and... and... ah no. I'm doomed.
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(more_decline);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_the_ring_01:s_c0eab960", -- Why are you back? What's wrong?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_3faed3", "more_done"}, -- Nothing's wrong. I just haven't found the ring yet.
		{"@conversation/padawan_the_ring_01:s_23b61565", "more_decline"} -- I've changed my mind. Go get the ring yourself. I've got better things to do.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(back_notdone);

more_done = ConvoScreen:new {
	id = "more_done",
	leftDialog = "@conversation/padawan_the_ring_01:s_a9ca1cc2", -- No problem friend. Hurry back when you have it.
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(more_done);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_the_ring_01:s_70e58d4e", -- You're back. Did you get the ring?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_6fd316c5", "done_final_too"}, -- I did, though it wasn't easy.
		{"@conversation/padawan_the_ring_01:s_5056dd2e", "more_decline_too"} -- No, he insisted on fighting for it. You're not worth the trouble.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(back_done);

done_final_too = ConvoScreen:new {
	id = "done_final_too",
	leftDialog = "@conversation/padawan_the_ring_01:s_f7b65eb2", -- Why is it covered in blood?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_252ebf4f", "done_final"}, -- Little details like that don't matter.
		{"@conversation/padawan_the_ring_01:s_1f8ddc7", "done_final_finish"} -- I got it the only way possible, by killing the low life that took it from you.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(done_final_too);

done_final = ConvoScreen:new {
	id = "done_final",
	leftDialog = "@conversation/padawan_the_ring_01:s_d403c577", -- Is he ok?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_b7fd7db8", "done_final_tease"}, -- Not exactly, depends on your definition of ok.
		{"@conversation/padawan_the_ring_01:s_9a1d24f0", "done_final_joke"} -- 	In the literal, or figurative sense?
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(done_final);

done_final_tease = ConvoScreen:new {
	id = "done_final_tease",
	leftDialog = "@conversation/padawan_the_ring_01:s_3a25f75a", -- Alive?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_b4bf50d7", "done_final_finish"} -- No, if you put it that way.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(done_final_tease);

done_final_joke = ConvoScreen:new {
	id = "done_final_joke",
	leftDialog = "@conversation/padawan_the_ring_01:s_f61a9588", -- Literal!
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_63fcf51c", "done_final_finish"} -- In that case.. No. He's not quite ok.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(done_final_joke);

done_final_finish = ConvoScreen:new {
	id = "done_final_finish",
	leftDialog = "@conversation/padawan_the_ring_01:s_47749228", -- You... you killed him? Wow, I never thought he'd refuse to return it and fight you for it. Well, I thought he might fight you, but not that he'd go so far. I don't know what to say... thank you, friend. Thank you very much.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_a410e80d", "done_final_lesson"} -- It's free the first time, next time it's going to cost you.
	}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(done_final_finish);

done_final_lesson = ConvoScreen:new {
	id = "done_final_lesson",
	leftDialog = "@conversation/padawan_the_ring_01:s_b3083e4e", -- Rewards are not always monetary, or even tangible friend. Learning that in life not all of your positive actions result in an immediate personal gain will leave you much more appreciative of the things you already have. 
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(done_final_lesson);

more_decline_too = ConvoScreen:new {
	id = "more_decline_too",
	leftDialog = "@conversation/padawan_the_ring_01:s_e20e68ad", -- Hmmph. Probably would have stolen the ring for yourself anyway.
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(more_decline_too);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_the_ring_01:s_16c644b4", -- She'll have my hide. I'm such a fool. How could I have done such a thing... how??!!
	stopConversation = "true",
	options = {}
}
trialsPadawanTheRing01ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanTheRing01ConvoTemplate", trialsPadawanTheRing01ConvoTemplate);
