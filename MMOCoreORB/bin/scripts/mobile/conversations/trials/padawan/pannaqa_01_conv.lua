padawan_pannaqa_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_pannaqa_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_pannaqa_01:s_41aab3ed", -- I'm sure someone of your ability will be able to assist me. Do you have a second to spare?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_df607c49", "cant_leave_village"}, -- I'm listening.
		{"@conversation/padawan_pannaqa_01:s_fd022a50", "sorry_for_bothering"} -- No, find some sap to bother with your shallow needs.
	}
}
padawan_pannaqa_01_convo_template:addScreen(intro);

cant_leave_village = ConvoScreen:new {
	id = "cant_leave_village",
	leftDialog = "@conversation/padawan_pannaqa_01:s_53c84ebd", -- 	I can't leave the village.. there's far too much to be done at the moment. But I also need a replacement part for my vibro-tiller. Without it, farming is much more difficult. As you can see, we have not had much luck of late trying to grow our crops. Between the harsh environment and the constant attacks of Mellichae's thugs, we have our hands full.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_dd5fc3e4", "find_shendo"}, -- Sure, why not.  How can I help?
		{"@conversation/padawan_pannaqa_01:s_ed2f6bdb", "sorry_for_bothering"} -- What kind of mup do you take me for? I'm not doing you menial labor.
	}
}
padawan_pannaqa_01_convo_template:addScreen(cant_leave_village);

find_shendo = ConvoScreen:new {
	id = "find_shendo",
	leftDialog = "@conversation/padawan_pannaqa_01:s_194a6a4b", -- Shendo, an extremely unreliable acquaintance of mine was supposed to have delivered it many hours ago but has yet to show up. Would you be willing to find him and retrieve the part?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_69af28a6", "ill_be_here"}, -- I would be more than willing to help.
		{"@conversation/padawan_pannaqa_01:s_ad0eb2bb", "sorry_for_bothering"} -- Tasks like this are for the servants, bother someone else.
	}
}
padawan_pannaqa_01_convo_template:addScreen(find_shendo);

ill_be_here = ConvoScreen:new {
	id = "ill_be_here",
	leftDialog = "@conversation/padawan_pannaqa_01:s_bbfeec70", -- Thank you kindly, I'll be here when you return.
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_01_convo_template:addScreen(ill_be_here);

sorry_for_bothering = ConvoScreen:new {
	id = "sorry_for_bothering",
	leftDialog = "@conversation/padawan_pannaqa_01:s_72d5a837", -- Sorry for bothering, I didn't mean to offend.
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_01_convo_template:addScreen(sorry_for_bothering);

intro_spoke_to_second_npc = ConvoScreen:new {
	id = "intro_spoke_to_second_npc",
	leftDialog = "@conversation/padawan_pannaqa_01:s_b2216c3", -- Do you have the part? Did you find Shendo?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_3a3e0d5d", "gardens_in_shape"}, -- Yes, Shendo wasn't difficult to find... just to deal with.
	}
}
padawan_pannaqa_01_convo_template:addScreen(intro_spoke_to_second_npc);

gardens_in_shape = ConvoScreen:new {
	id = "gardens_in_shape",
	leftDialog = "@conversation/padawan_pannaqa_01:s_42e0a11e", -- Thank you so much. Hopefully this will help me get the gardens around here into shape.
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_01_convo_template:addScreen(gardens_in_shape);

intro_spoke_to_first_npc = ConvoScreen:new {
	id = "intro_spoke_to_first_npc",
	leftDialog = "@conversation/padawan_pannaqa_01:s_b9c3a3be", -- Any luck finding Shendo?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_30546869", "please_return"}, -- Not yet, but don't worry... I will.
		{"@conversation/padawan_pannaqa_01:s_b336be8b", "find_your_way"} -- I've decided that you're on your own. Find another servant.
	}
}
padawan_pannaqa_01_convo_template:addScreen(intro_spoke_to_first_npc);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_pannaqa_01:s_6d11135b", -- Did you find Shendo with the vibro-tiller part?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_01:s_30546869", "please_return"}, -- Not yet, but don't worry... I will.
		{"@conversation/padawan_pannaqa_01:s_387d18ec", "find_your_way"} -- I've decided that I'm done being your slave boy. You're on your own.
	}
}
padawan_pannaqa_01_convo_template:addScreen(intro_in_progress);

please_return = ConvoScreen:new {
	id = "please_return",
	leftDialog = "@conversation/padawan_pannaqa_01:s_52da7aa", -- Ahh, thank you. Please return when you have the part.
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_01_convo_template:addScreen(please_return);

find_your_way = ConvoScreen:new {
	id = "find_your_way",
	leftDialog = "@conversation/padawan_pannaqa_01:s_24a1738d", -- I see. I thank you for the consideration you've given and trust that you find your way.
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_01_convo_template:addScreen(find_your_way);

completed_quest = ConvoScreen:new {
	id = "completed_quest",
	leftDialog = "@conversation/padawan_pannaqa_01:s_be0f3920", -- Now maybe instead of just dead trees, I'll grow some vegetables. Or flowers. Or maybe just more trees.
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_01_convo_template:addScreen(completed_quest);

not_on_quest = ConvoScreen:new {
	id = "not_on_quest",
	leftDialog = "@conversation/padawan_pannaqa_01:s_1843ab7e", -- One dead tree. That's pretty much all I've got to show for my farming skills. As if I should call them skills even. [*sigh*]
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_01_convo_template:addScreen(not_on_quest);

addConversationTemplate("padawan_pannaqa_01_convo_template", padawan_pannaqa_01_convo_template);
