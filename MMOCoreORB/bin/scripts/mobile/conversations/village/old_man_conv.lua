oldManIntroConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "oldManIntroConvoHandler",
	screens = {}
}

nothing_to_discuss = ConvoScreen:new {
	id = "nothing_to_discuss",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_c7146ea8", -- I am sorry. I have nothing to discuss with you.
	stopConversation = "true",
	options = {}
}

oldManIntroConvoTemplate:addScreen(nothing_to_discuss);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_de9da426", -- Hello. I have been meaning to speak with you for some time. Do you have a moment?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_501448da", "connected_to_force" }, -- Yes, what is it you need?
		{ "@conversation/fs_intro_oldman_initial:s_e0a90395", "fairly_urgent_matter" } -- I'm sorry.  I really don't have time now.
	}
}

oldManIntroConvoTemplate:addScreen(intro);

connected_to_force = ConvoScreen:new {
	id = "connected_to_force",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_7f8604a5", -- I was wondering if you had ever considered the possibility that you might be connected with the Force?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_a3291a29", "you_sense_as_well" }, -- Yes, the thought had crossed my mind a few times.
		{ "@conversation/fs_intro_oldman_initial:s_6b88daf2", "misjudged_you" } -- No, I have never thought about it really.
	}
}

oldManIntroConvoTemplate:addScreen(connected_to_force);

you_sense_as_well = ConvoScreen:new {
	id = "you_sense_as_well",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_cf55fe01", -- So you sense it as well.  I have a Force crystal here if you are interested in discovering for certain.  Perhaps you could hold onto it and keep it safe?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_b81ceeb4", "here_is_the_crystal" }, -- Yes,  I will keep it safe for you.
		{ "@conversation/fs_intro_oldman_initial:s_c6f70929", "perhaps_another_time" } -- No, I am not interested.  Thanks.
	}
}

oldManIntroConvoTemplate:addScreen(you_sense_as_well);

here_is_the_crystal = ConvoScreen:new {
	id = "here_is_the_crystal",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_3aab754", -- Very good.  Here is the crystal. May the Force be with you.
	stopConversation = "true",
	options = {}
}

oldManIntroConvoTemplate:addScreen(here_is_the_crystal);

fairly_urgent_matter = ConvoScreen:new {
	id = "fairly_urgent_matter",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_383079e", -- Are you sure?  It's a fairly urgent matter.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_aa6a1756", "connected_to_force" }, -- Oh? Very well then.  What is it you wanted to discuss?
		{ "@conversation/fs_intro_oldman_initial:s_fb9e0b93", "perhaps_meet_again" } -- No, I am busy right now.  Perhaps another time.
	}
}

oldManIntroConvoTemplate:addScreen(fairly_urgent_matter);

perhaps_meet_again = ConvoScreen:new {
	id = "perhaps_meet_again",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_83e20fb8", -- Very well then.  Perhaps we will meet again at another time.
	stopConversation = "true",
	options = {
	}
}

oldManIntroConvoTemplate:addScreen(perhaps_meet_again);

misjudged_you = ConvoScreen:new {
	id = "misjudged_you",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_eb24a286", -- Hmmmm.  Perhaps I misjudged you. I have a Force crystal here if you are interested in discovering for certain. Perhaps you could hold onto it and keep it safe?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_b81ceeb4", "here_is_the_crystal" }, -- Yes,  I will keep it safe for you.
		{ "@conversation/fs_intro_oldman_initial:s_c6f70929", "perhaps_another_time" } -- No, I am not interested.  Thanks.
	}
}

oldManIntroConvoTemplate:addScreen(misjudged_you);

perhaps_another_time = ConvoScreen:new {
	id = "perhaps_another_time",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_419f8694", -- Very well then.  Perhaps another time.
	stopConversation = "true",
	options = {}
}

oldManIntroConvoTemplate:addScreen(perhaps_another_time);

intro_mellichae = ConvoScreen:new {
	id = "intro_mellichae",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_958f442", -- Hello again, my friend. Thank you for all of your help at the village. The time has come for you to hunt down and destroy Mellichae.
	stopConversation = "false",
	options = {
	{ "@conversation/fs_intro_oldman_initial:s_9641e6e", "where_camp"}, -- Where is his camp located?
	{ "@conversation/fs_intro_oldman_initial:s_fbd984c8", "where_camp_detail"} 	--Who is Mellichae? Where is his camp located?
	}
}

oldManIntroConvoTemplate:addScreen(intro_mellichae);

where_camp = ConvoScreen:new {
	id = "where_camp",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_f5c5ace0", -- Although the exact location is still unknown, his camp is relatively close to here. I have given the approximate location to you as a waypoint. Be very careful. You may want to bring some friends. Defeating Mellichae will not be easy... Good luck!
	stopConversation = "true",
	options = {}
}

oldManIntroConvoTemplate:addScreen(where_camp);

where_camp_detail = ConvoScreen:new {
	id = "where_camp_detail",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_31a054f9", -- Mellichae is the leader of the Sith Shadows. He is responsible for the attacks at the village. Scouts have reported he has set up camp near here.
	stopConversation = "false",
	options = {
	{ "@conversation/fs_intro_oldman_initial:s_9641e6e", "where_camp"}, -- Where is his camp located?
	}
}

oldManIntroConvoTemplate:addScreen(where_camp_detail);


addConversationTemplate("oldManIntroConvoTemplate", oldManIntroConvoTemplate);

