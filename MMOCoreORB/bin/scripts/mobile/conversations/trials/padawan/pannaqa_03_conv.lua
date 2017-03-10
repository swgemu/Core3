padawan_pannaqa_03_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_pannaqa_03_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_pannaqa_03:s_70fea75d", -- Um, hello?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_4cc97351", "um_who"} -- Pannaqa has been waiting for you for quite a while, Shendo. He needs that vibro-tiller part.
	}
}
padawan_pannaqa_03_convo_template:addScreen(intro);

um_who = ConvoScreen:new {
	id = "um_who",
	leftDialog = "@conversation/padawan_pannaqa_03:s_9035e1f5", -- Um, who?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_2b0e7d3c", "no_kidding"} -- Pannaqa!  You are already many hours late.
	}
}
padawan_pannaqa_03_convo_template:addScreen(um_who);

no_kidding = ConvoScreen:new {
	id = "no_kidding",
	animation = "tap_head",
	leftDialog = "@conversation/padawan_pannaqa_03:s_6abc7ab9", -- No kidding eh?  I guess I should probably get on that huh?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_7bbf7ffe", "take_part_for_me"}, -- I don't think I can trust you to finish the job.
		{"@conversation/padawan_pannaqa_03:s_b7bc9ab", "give_you_part"} -- At this point I do not care, I've lost all hope.
	}
}
padawan_pannaqa_03_convo_template:addScreen(no_kidding);

take_part_for_me = ConvoScreen:new {
	id = "take_part_for_me",
	leftDialog = "@conversation/padawan_pannaqa_03:s_eb635904", -- So you are going to take the part for me, and I can stay here and drink?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_1a22a5dc", "drinking_and_wandering"}, -- Basically.
	}
}
padawan_pannaqa_03_convo_template:addScreen(take_part_for_me);

drinking_and_wandering = ConvoScreen:new {
	id = "drinking_and_wandering",
	animation = "celebrate1",
	leftDialog = "@conversation/padawan_pannaqa_03:s_b6307da0", -- Deal. Now I can get back to my drinking and wandering. [You stash the vibro-tiller part in a safe place.]
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_03_convo_template:addScreen(drinking_and_wandering);

give_you_part = ConvoScreen:new {
	id = "give_you_part",
	animation = "rub_belly",
	leftDialog = "@conversation/padawan_pannaqa_03:s_e51e11cc", -- Cheer up mate, how about I give you the part, and you take it to Pan.. Paqanna.. Whatever his name was. I'm going to keep my eyes on this bottle of ale for you and make sure it doesn't do whatever it is I think it's going to do. [You stash the vibro-tiller part in a safe place.]
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_03_convo_template:addScreen(give_you_part);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_pannaqa_03:s_552042df", -- Show me the drink to go way. I'm home and I wanna go drink....
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_03_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_pannaqa_03_convo_template", padawan_pannaqa_03_convo_template);
