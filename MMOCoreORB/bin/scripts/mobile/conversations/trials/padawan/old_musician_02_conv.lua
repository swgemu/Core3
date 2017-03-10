padawan_old_musician_02_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_old_musician_02_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_old_musician_02:s_cefcce06", -- Yes? Are you talking to me?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_83a3fa55", "heard_of_him"} -- Do you know an old man by the name of Grizzlo?
	}
}
padawan_old_musician_02_convo_template:addScreen(intro);

heard_of_him = ConvoScreen:new {
	id = "heard_of_him",
	leftDialog = "@conversation/padawan_old_musician_02:s_8593cffc", -- Old Grizzy?  Sure, I've heard of him.  Didn't he die a few years back?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_71918486", "whoda_guessed"}, -- No, he is very much alive. Well, sort of.
		{"@conversation/padawan_old_musician_02:s_e9a5dbe", "morbid_humor"} -- I'm digging up his past before they start digging his grave.
	}
}
padawan_old_musician_02_convo_template:addScreen(heard_of_him);

whoda_guessed = ConvoScreen:new {
	id = "whoda_guessed",
	leftDialog = "@conversation/padawan_old_musician_02:s_c8ad3417", -- Who'da guessed that.  Well, what do you need to know about Ol' Grizzy Two Tune?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_91a67d52", "moved_to_lok"}, -- Do you know where I can find any of his band mates?
		{"@conversation/padawan_old_musician_02:s_3ce5abed", "used_to_call_him"}, -- Grizzy Two Tune?
		{"@conversation/padawan_old_musician_02:s_51ea4418", "makes_any_difference"} -- Never mind, I've decided I don't care.
	}
}
padawan_old_musician_02_convo_template:addScreen(whoda_guessed);

morbid_humor = ConvoScreen:new {
	id = "morbid_humor",
	leftDialog = "@conversation/padawan_old_musician_02:s_d920c8d", -- You have quite the morbid sense of humor don't yah? Well, what do you need to know about Ol' Grizzy Two Tune?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_79a946b4", "moved_to_lok"}, -- Know the current location of any of his band mates?
		{"@conversation/padawan_old_musician_02:s_3ce5abed", "used_to_call_him"}, -- Grizzy Two Tune?
		{"@conversation/padawan_old_musician_02:s_51ea4418", "whatever_you_say"} -- Never mind, I don't think I care any more.
	}
}
padawan_old_musician_02_convo_template:addScreen(morbid_humor);

used_to_call_him = ConvoScreen:new {
	id = "used_to_call_him",
	leftDialog = "@conversation/padawan_old_musician_02:s_bdb08f0b", -- That's what they used to call him; his band didn't know more than two tunes. Truth is the tunes they did play were something else; I don't think their popularity ever spread off world though. Need to know anything else?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_8db3d0fb", "moved_to_lok"}, -- Do you know where I can find the other band members?
		{"@conversation/padawan_old_musician_02:s_cf3cdb9a", "falling_out"}, -- Why did they break up if they were so popular?
	}
}
padawan_old_musician_02_convo_template:addScreen(used_to_call_him);

falling_out = ConvoScreen:new {
	id = "falling_out",
	leftDialog = "@conversation/padawan_old_musician_02:s_b38f136f", -- The band had some sort of falling out, I'm sure it was over a girl.  Tad bit cliche, eh?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_fafa8703", "stories_never_change"}, -- Yeah, but that doesn't surprise me.
		{"@conversation/padawan_old_musician_02:s_1e50f991", "makes_any_difference"}, -- Sadly, I've lost interest in this..
	}
}
padawan_old_musician_02_convo_template:addScreen(falling_out);

stories_never_change = ConvoScreen:new {
	id = "stories_never_change",
	leftDialog = "@conversation/padawan_old_musician_02:s_58a6b3", -- These stories never change friend.  Is that all you needed to know?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_02:s_8db3d0fb", "moved_to_lok"}, -- Do you know where I can find the other band members?
		{"@conversation/padawan_old_musician_02:s_c7d951f7", "never_been_here"}, -- I think I've exceed my interest in this whole thing. Forget about it.
	}
}
padawan_old_musician_02_convo_template:addScreen(stories_never_change);

moved_to_lok = ConvoScreen:new {
	id = "moved_to_lok",
	leftDialog = "@conversation/padawan_old_musician_02:s_c7b21593", -- I've heard one or two of them moved to Lok about twenty some years ago, though it's been quite a while since I've heard from any them. I fear age may have caught up with them sooner than our friend Grizzlo. I know a musician at the cantina on Lok near Nym's stronghold. He would know if any of those guys are still around. Look for Vixur Webb there.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_02_convo_template:addScreen(moved_to_lok);

never_been_here = ConvoScreen:new {
	id = "never_been_here",
	leftDialog = "@conversation/padawan_old_musician_02:s_26888d70", -- It's forgotten. Like you've never been here. Really, who are you?
	stopConversation = "true",
	options = {}
}
padawan_old_musician_02_convo_template:addScreen(never_been_here);

makes_any_difference = ConvoScreen:new {
	id = "makes_any_difference",
	leftDialog = "@conversation/padawan_old_musician_02:s_284c1131", -- Whatever you say. Not like it makes any difference to me.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_02_convo_template:addScreen(makes_any_difference);

whatever_you_say = ConvoScreen:new {
	id = "whatever_you_say",
	leftDialog = "@conversation/padawan_old_musician_02:s_46660c8b", -- Whatever you say. You were the one asking questions.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_02_convo_template:addScreen(whatever_you_say);

not_on_quest = ConvoScreen:new {
	id = "not_on_quest",
	leftDialog = "@conversation/padawan_old_musician_02:s_5d25f30f", -- Beep boop bop bop... yeah, play that thing.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_02_convo_template:addScreen(not_on_quest);

addConversationTemplate("padawan_old_musician_02_convo_template", padawan_old_musician_02_convo_template);
