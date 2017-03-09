padawan_the_ring_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_the_ring_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_the_ring_01:s_3924c1a9", -- I'm in a tight spot.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_7b35cfbc", "borrowed_ring"}, -- What is the problem?
		{"@conversation/padawan_the_ring_01:s_7cb3d5a9", "incredible_skills"} -- Should have been more careful.
	}
}
padawan_the_ring_01_convo_template:addScreen(intro);

incredible_skills = ConvoScreen:new {
	id = "incredible_skills",
	leftDialog = "@conversation/padawan_the_ring_01:s_92a6af5a", -- Brilliant! Your incredible skills of deduction amaze me. How much do I owe you for this display of pure ingenious?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_a410e80d", "you_are_listening"}, -- It's free the first time, next time it's going to cost you.
		{"@conversation/padawan_the_ring_01:s_c6898781", "wound_up"} -- I'm sorry, it was just a joke.
	}
}
padawan_the_ring_01_convo_template:addScreen(incredible_skills);

wound_up = ConvoScreen:new {
	id = "wound_up",
	leftDialog = "@conversation/padawan_the_ring_01:s_c2f7ce8", -- It's okay, I'm just a bit wound up. I could truly use your help, if you are willing of course.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_8626b2e6", "borrowed_ring"}, -- Sure, how can I help you?
	}
}
padawan_the_ring_01_convo_template:addScreen(wound_up);

you_are_listening = ConvoScreen:new {
	id = "you_are_listening",
	leftDialog = "@conversation/padawan_the_ring_01:s_dc264acf", -- Fair enough. At least you're listening. You are listening, right?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_8626b2e6", "borrowed_ring"}, -- Sure, how can I help you?
	}
}
padawan_the_ring_01_convo_template:addScreen(you_are_listening);

you_are_listening = ConvoScreen:new {
	id = "you_are_listening",
	leftDialog = "@conversation/padawan_the_ring_01:s_dc264acf", -- Fair enough. At least you're listening. You are listening, right?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_8626b2e6", "borrowed_ring"}, -- Sure, how can I help you?
	}
}
padawan_the_ring_01_convo_template:addScreen(you_are_listening);

borrowed_ring = ConvoScreen:new {
	id = "borrowed_ring",
	leftDialog = "@conversation/padawan_the_ring_01:s_d1457e5b", -- I sort of borrowed my deceased mother in laws wedding ring from my wife, then I sort of lost it when I was out racing my swoop.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_91971db6", "try_to_find_it"}, -- That is a tight spot.
		{"@conversation/padawan_the_ring_01:s_997d67e4", "sure_to_suspect"} -- Why not get it yourself?
	}
}
padawan_the_ring_01_convo_template:addScreen(borrowed_ring);

try_to_find_it = ConvoScreen:new {
	id = "try_to_find_it",
	leftDialog = "@conversation/padawan_the_ring_01:s_6d739213", -- Seriously... If it's not too much to ask do you think you could go out and try to find it for me?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_70c10eb", "last_location"}, -- I would be happy to.
		{"@conversation/padawan_the_ring_01:s_ea66e5db", "rewards_not_monetary"} -- Sounds dangerous. If there's nothing in it for me, forget it.
	}
}
padawan_the_ring_01_convo_template:addScreen(try_to_find_it);

rewards_not_monetary = ConvoScreen:new {
	id = "rewards_not_monetary",
	leftDialog = "@conversation/padawan_the_ring_01:s_b3083e4e", -- Rewards are not always monetary, or even tangible friend. Learning that in life not all of your positive actions result in an immediate personal gain will leave you much more appreciative of the things you already have.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_01_convo_template:addScreen(rewards_not_monetary);

sure_to_suspect = ConvoScreen:new {
	id = "sure_to_suspect",
	leftDialog = "@conversation/padawan_the_ring_01:s_61a3322c", -- If I'm not here when my wife returns she is sure to suspect I've done something wrong. She had no idea I was going out racing, and if she finds out otherwise... Well lets just say she cannot find out otherwise. Do you have time to help?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_70c10eb", "last_location"}, -- I would be happy to.
	}
}
padawan_the_ring_01_convo_template:addScreen(sure_to_suspect);

last_location = ConvoScreen:new {
	id = "last_location",
	leftDialog = "@conversation/padawan_the_ring_01:s_d91ac73", -- Thank you very much, I've uploaded your datapad with the last location I remember having the ring on me.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_01_convo_template:addScreen(last_location);

intro_spoke_to_target = ConvoScreen:new {
	id = "intro_spoke_to_target",
	leftDialog = "@conversation/padawan_the_ring_01:s_112f3596", -- Do you have the ring?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_5056dd2e", "im_doomed"}, -- No, he insisted on fighting for it. You're not worth the trouble.
	}
}
padawan_the_ring_01_convo_template:addScreen(intro_spoke_to_target);

im_doomed = ConvoScreen:new {
	id = "im_doomed",
	leftDialog = "@conversation/padawan_the_ring_01:s_4bbb35f5", -- Coward! Why did I ever think you'd be able to help me anyway. Just go. Maybe I can buy another ring that looks just like it... with the exact same inscription... and... and... ah no. I'm doomed.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_01_convo_template:addScreen(im_doomed);

intro_killed_target = ConvoScreen:new {
	id = "intro_killed_target",
	leftDialog = "@conversation/padawan_the_ring_01:s_70e58d4e", -- You're back. Did you get the ring?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_6fd316c5", "covered_in_blood"}, -- I did, though it wasn't easy.
	}
}
padawan_the_ring_01_convo_template:addScreen(intro_killed_target);

covered_in_blood = ConvoScreen:new {
	id = "covered_in_blood",
	leftDialog = "@conversation/padawan_the_ring_01:s_f7b65eb2", -- Why is it covered in blood?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_1f8ddc7", "go_so_far"}, -- I got it the only way possible, by killing the low life that took it from you.
		{"@conversation/padawan_the_ring_01:s_252ebf4f", "is_he_ok"}, -- Little details like that don't matter.
	}
}
padawan_the_ring_01_convo_template:addScreen(covered_in_blood);

is_he_ok = ConvoScreen:new {
	id = "is_he_ok",
	leftDialog = "@conversation/padawan_the_ring_01:s_d403c577", -- Is he ok?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_b7fd7db8", "is_he_alive"}, -- Not exactly, depends on your definition of ok.
	}
}
padawan_the_ring_01_convo_template:addScreen(is_he_ok);

is_he_alive = ConvoScreen:new {
	id = "is_he_alive",
	leftDialog = "@conversation/padawan_the_ring_01:s_3a25f75a", -- Alive?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_63fcf51c", "go_so_far"}, -- In that case.. No.  He's not quite ok.
		{"@conversation/padawan_the_ring_01:s_9a1d24f0", "literal_sense"}, -- In the literal, or figurative sense?
	}
}
padawan_the_ring_01_convo_template:addScreen(is_he_alive);

literal_sense = ConvoScreen:new {
	id = "literal_sense",
	leftDialog = "@conversation/padawan_the_ring_01:s_f61a9588", -- Literal!
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_b4bf50d7", "go_so_far"}, -- No, if you put it that way.
	}
}
padawan_the_ring_01_convo_template:addScreen(literal_sense);

go_so_far = ConvoScreen:new {
	id = "go_so_far",
	leftDialog = "@conversation/padawan_the_ring_01:s_47749228", -- You... you killed him? Wow, I never thought he'd refuse to return it and fight you for it. Well, I thought he might fight you, but not that he'd go so far. I don't know what to say... thank you, friend. Thank you very much.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_01_convo_template:addScreen(go_so_far);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_the_ring_01:s_c0eab960", -- Why are you back? What's wrong?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_the_ring_01:s_3faed3", "hurry_back"}, -- Nothing's wrong. I just haven't found the ring yet.
		{"@conversation/padawan_the_ring_01:s_23b61565", "would_have_stolen"} -- I've changed my mind. Go get the ring yourself. I've got better things to do.
	}
}
padawan_the_ring_01_convo_template:addScreen(intro_in_progress);

hurry_back = ConvoScreen:new {
	id = "hurry_back",
	leftDialog = "@conversation/padawan_the_ring_01:s_a9ca1cc2", -- No problem friend. Hurry back when you have it.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_01_convo_template:addScreen(hurry_back);

would_have_stolen = ConvoScreen:new {
	id = "would_have_stolen",
	leftDialog = "@conversation/padawan_the_ring_01:s_e20e68ad", -- Hmmph. Probably would have stolen the ring for yourself anyway.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_01_convo_template:addScreen(would_have_stolen);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_the_ring_01:s_d0ed20dc", -- Thank you again, friend. I'm sorry it had to come to violence, but I guess you had no other choice.
	stopConversation = "true",
	options = {}
}
padawan_the_ring_01_convo_template:addScreen(quest_completed);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_the_ring_01:s_16c644b4", -- She'll have my hide. I'm such a fool. How could I have done such a thing... how??!!
	stopConversation = "true",
	options = {}
}
padawan_the_ring_01_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_the_ring_01_convo_template", padawan_the_ring_01_convo_template);
