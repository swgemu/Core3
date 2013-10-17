old_man_convotemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "old_man_conv_handler",
	screens = {}
}

old_man_init = ConvoScreen:new {
	id = "init",
	leftDialog = "",
	stopConversation = "false",
	options = {
	}
}

old_man_convotemplate:addScreen(old_man_init);

old_man_not_you = ConvoScreen:new {
	id = "not_you",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_c7146ea8", -- I am sorry. I have nothing to discuss with you.
	stopConversation = "true",
	options = {
	}
}

old_man_convotemplate:addScreen(old_man_not_you);

old_man_village_intro = ConvoScreen:new {
	id = "village_intro",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_de9da426", -- Hello. I have been meaning to speak with you for some time. Do you have a moment?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_501448da", "village_connection_force" }, -- Yes, what is it you need?
		{ "@conversation/fs_intro_oldman_initial:s_e0a90395", "village_urgent" } -- I'm sorry.  I really don't have time now.
	}
}

old_man_convotemplate:addScreen(old_man_village_intro);

old_man_village_connection_force = ConvoScreen:new {
	id = "village_connection_force",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_7f8604a5", -- I was wondering if you had ever considered the possibility that you might be connected with the Force?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_a3291a29", "village_force_crystal" }, -- Yes, the thought had crossed my mind a few times.
		{ "@conversation/fs_intro_oldman_initial:s_6b88daf2", "village_no_force" } -- No, I have never thought about it really.
	}
}

old_man_convotemplate:addScreen(old_man_village_connection_force);

old_man_village_force_crystal = ConvoScreen:new {
	id = "village_force_crystal",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_cf55fe01", -- So you sense it as well.  I have a Force crystal here if you are interested in discovering for certain.  Perhaps you could hold onto it and keep it safe? 
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_b81ceeb4", "village_give_crystal" }, -- Yes,  I will keep it safe for you.
		{ "@conversation/fs_intro_oldman_initial:s_c6f70929", "village_another_time2" } -- No, I am not interested.  Thanks.
	}
}

old_man_convotemplate:addScreen(old_man_village_force_crystal);

old_man_village_give_crystal = ConvoScreen:new {
	id = "village_give_crystal",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_3aab754", -- Very good.  Here is the crystal. May the Force be with you.
	stopConversation = "true",
	options = {
	}
}

old_man_convotemplate:addScreen(old_man_village_give_crystal);

old_man_village_urgent = ConvoScreen:new {
	id = "village_urgent",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_383079e", -- Are you sure?  It's a fairly urgent matter.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_aa6a1756", "village_connection_force" }, -- Oh? Very well then.  What is it you wanted to discuss?
		{ "@conversation/fs_intro_oldman_initial:s_fb9e0b93", "village_another_time" } -- No, I am busy right now.  Perhaps another time.
	}
}

old_man_convotemplate:addScreen(old_man_village_urgent);

old_man_village_another_time = ConvoScreen:new {
	id = "village_another_time",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_83e20fb8", -- Very well then.  Perhaps we will meet again at another time.
	stopConversation = "true",
	options = {
	}
}

old_man_convotemplate:addScreen(old_man_village_another_time);

old_man_village_no_force = ConvoScreen:new {
	id = "village_no_force",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_eb24a286", -- Hmmmm.  Perhaps I misjudged you. I have a Force crystal here if you are interested in discovering for certain. Perhaps you could hold onto it and keep it safe?
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_b81ceeb4", "village_give_crystal" }, -- Yes,  I will keep it safe for you.
		{ "@conversation/fs_intro_oldman_initial:s_c6f70929", "village_another_time" } -- No, I am not interested.  Thanks.
	}
}

old_man_convotemplate:addScreen(old_man_village_no_force);

old_man_village_another_time2 = ConvoScreen:new {
	id = "village_another_time2",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_419f8694", -- Very well then.  Perhaps another time.
	stopConversation = "true",
	options = {
	}
}

old_man_convotemplate:addScreen(old_man_village_another_time2);

old_man_mellichae_intro = ConvoScreen:new {
	id = "mellichae_intro",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_958f442", -- Hello again, my friend.  Thank you for all of your help at the village.  The time has come for you to hunt down and destroy Mellichae.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_fbd984c8", "mellichae_who" }, -- Who is Mellichae? Where is his camp located?
		{ "@conversation/fs_intro_oldman_initial:s_477068d1", "mellichae_later" } -- I am busy at the moment.  Perhaps later.
	}
}

old_man_convotemplate:addScreen(old_man_mellichae_intro);

old_man_mellichae_who = ConvoScreen:new {
	id = "mellichae_who",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_31a054f9", -- Mellichae is the leader of the Sith Shadows.  He is responsible for the attacks at the village.  Scouts have reported he has set up camp near here.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_intro_oldman_initial:s_9641e6e", "mellichae_location" }, -- Where is his camp located?
		{ "@conversation/fs_intro_oldman_initial:s_c6f70929", "mellichae_later" } -- No, I am not interested.  Thanks.
	}
}

old_man_convotemplate:addScreen(old_man_mellichae_who);

old_man_mellichae_location = ConvoScreen:new {
	id = "mellichae_location",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_f5c5ace0", -- Although the exact location is still unknown, his camp is relatively close to here.  I have given the approximate location to you as a waypoint.  Be very careful.  You may want to bring some friends. Defeating Mellichae will not be easy... Good luck!
	stopConversation = "true",
	options = {
	}
}

old_man_convotemplate:addScreen(old_man_mellichae_location);

old_man_mellichae_later = ConvoScreen:new {
	id = "mellichae_later",
	leftDialog = "@conversation/fs_intro_oldman_initial:s_ac22e1a3", -- Very well then.  I shall return later. Thanks again for all your help.
	stopConversation = "true",
	options = {
	}
}

old_man_convotemplate:addScreen(old_man_mellichae_later);

addConversationTemplate("old_man_convotemplate", old_man_convotemplate);

