heroOfTatBountyHunterConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "heroOfTatBountyHunterConvoHandler",
	screens = {}
}

intro_no_hermit = ConvoScreen:new {
	id = "intro_no_hermit",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_3769e5f8", -- 	I don't have time to talk right now. Sorry.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(intro_no_hermit);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_bd2c41cb", -- You there. Do you know any of these smugglers here?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_775eed34", "figured_as_much"}, -- No, can't say as I do.
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_12afde00", "didnt_think_you_would"}, -- Smugglers? Why would I know any smugglers?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_3769e5f8", "leave_me_alone"}, -- I don't have time to talk right now. Sorry.
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(intro);

leave_me_alone = ConvoScreen:new {
	id = "leave_me_alone",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_54e633f8", -- Then leave me alone. I'm busy.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(leave_me_alone);

figured_as_much = ConvoScreen:new {
	id = "figured_as_much",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_7eb6abbe", -- I figured as much. Blast it all. Now what do I do?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_b8f4813d", "need_concrete_info"}, -- Well, that one guy does look kinda familiar.
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_d3412303", "one_is_mark"}, -- What seems to be the problem?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_a49ad86c", "no_help_get_out_of_here"}, -- I don't know, but good luck!
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(figured_as_much);

didnt_think_you_would = ConvoScreen:new {
	id = "didnt_think_you_would",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_60d63ec8", -- No, I didn't think that you would. Curses. Now what do I do?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_b8f4813d", "need_concrete_info"}, -- Well, that one guy does look kinda familiar.
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_d3412303", "one_is_mark"}, -- What seems to be the problem?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_a49ad86c", "no_help_get_out_of_here"}, -- I don't know, but good luck!
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(didnt_think_you_would);

no_help_get_out_of_here = ConvoScreen:new {
	id = "no_help_get_out_of_here",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_86c02324", -- A lotta help you were. Get out of here.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(no_help_get_out_of_here);

need_concrete_info = ConvoScreen:new {
	id = "need_concrete_info",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_dec94c0f", -- I've got no time for 'kinda familiar'. I need concrete information.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_d3412303", "one_is_mark"}, -- What seems to be the problem?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_5fdaa4bb", "no_help_get_out_of_here"}, -- Well, so long then.
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(need_concrete_info);

one_is_mark = ConvoScreen:new {
	id = "one_is_mark",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_250df636", -- One of these smugglers is my mark. I think. I'm not sure. I've been tracking him for some time and just now caught up with him here in this city.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_922dd166", "would_arrest_if_knew"}, -- Then why don't you arrest him?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_eaa5c299", "not_sure_which"}, -- You're not sure?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_dd6f7e", "yea_yea_get_out_of_here"}, -- Good luck with all that!
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(one_is_mark);

yea_yea_get_out_of_here = ConvoScreen:new {
	id = "yea_yea_get_out_of_here",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_624a9b6f", -- Yea, yea. Get out of here.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(yea_yea_get_out_of_here);

not_sure_which = ConvoScreen:new {
	id = "not_sure_which",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_b8bf2aa9", -- Yea, that's the thing. I don't know which one of these smugglers is my mark.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_df981c5e", "stole_some_equipment"}, -- I thought you were tracking him for a long time?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_3ece0ca2", "cut_me_some_slack"}, -- You've got to be the worst bounty hunter ever.
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_239b0909", "yea_yea_get_out_of_here"}, -- Well, I hope you find him. Good-bye!
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(not_sure_which);

would_arrest_if_knew = ConvoScreen:new {
	id = "would_arrest_if_knew",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_d9ec1dc4", -- 'Arrest him'... heh. Yea, I would 'arrest him' but the problem is, I don't know which one of these smugglers he is.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_df981c5e", "stole_some_equipment"}, -- I thought you were tracking him for a long time?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_3ece0ca2", "cut_me_some_slack"}, -- You've got to be the worst bounty hunter ever.
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_239b0909", "yea_yea_get_out_of_here"}, -- Well, I hope you find him. Good-bye!
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(would_arrest_if_knew);

cut_me_some_slack = ConvoScreen:new {
	id = "cut_me_some_slack",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_659bb141", -- Listen up, kid. This stuff isn't as easy as it sounds. Cut me some slack.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_df981c5e", "stole_some_equipment"}, -- I thought you were tracking him for a long time?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_239b0909", "yea_yea_get_out_of_here"}, -- Well, I hope you find him. Good-bye!
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(cut_me_some_slack);

stole_some_equipment = ConvoScreen:new {
	id = "stole_some_equipment",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_ffdc10ae", -- The guy I'm looking for stole some equipment. Nobody got a good look at him, but the crate that he stole had a transponder signal attached to it.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_1fa16fd3", "tracker_went_dead"}, -- Then why not find the one with the transponder?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_5e244342", "yea_yea_get_out_of_here"}, -- I've helped all I can. Good-bye.
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(stole_some_equipment);

tracker_went_dead = ConvoScreen:new {
	id = "tracker_went_dead",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_bebac1d7", -- You must think I'm stupid don't you? A little while after I tracked the signal to this city, it went dead. He must have found it and turned it off.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_dce437b6", "brought_them_here"}, -- Have you questioned all the smugglers here?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_7cf16bce", "yea_yea_get_out_of_here"}, -- Sounds like you have it under control.
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(tracker_went_dead);

brought_them_here = ConvoScreen:new {
	id = "brought_them_here",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_806d4263", -- Questioned them? Yep, I found all the suspected smugglers in the area and brought them here. Questioned them, pushed them around, roughed them up, you name it.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_47482ee2", "little_confused"}, -- What did you find out?
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_1892fb83", "yea_yea_get_out_of_here"}, -- Good for you. So long!
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(brought_them_here);

little_confused = ConvoScreen:new {
	id = "little_confused",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_254a92c6", -- To be honest, I'm a little confused. I know the smuggler captain and I can trust him. But everyone else just blames each other, and I don't know what to do.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_369a8bff", "give_it_a_shot"}, -- Maybe I can find out who your mark is.
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_402e3e9a", "yea_yea_get_out_of_here"}, -- Wow, I wouldn't want to be in your position.
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(little_confused);

give_it_a_shot = ConvoScreen:new {
	id = "give_it_a_shot",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_44f4df", -- You really do think I'm stupid. I can handle this myself... but, uh... if you want to, give it a shot. See what you can find out.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(give_it_a_shot);

intro_completed = ConvoScreen:new {
	id = "intro_completed",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_b932a57a", -- Hey there! Thanks again for helping me find the right mark. You're OK in my book.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(intro_completed);

already_failed = ConvoScreen:new {
	id = "already_failed",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_29ecd548", -- You had your shot, kid. I'm not going to give you another chance. Get out of here.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(already_failed);

intro_hasquest = ConvoScreen:new {
	id = "intro_hasquest",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_faaf7075", -- Did you find out who my mark is?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_1b0651f8", "thats_great"}, -- Yes, I think I know who it is.
		{"@conversation/quest_hero_of_tatooine_bounty_hunter:s_69cdbab1", "let_me_know"}, -- Not yet. I'm still looking.
	}
}
heroOfTatBountyHunterConvoTemplate:addScreen(intro_hasquest);

thats_great = ConvoScreen:new {
	id = "thats_great",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_fc5b59e0", -- That's great! Just point out who you think it is. If your reasoning is justified, I'll take care of the rest.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(thats_great);

let_me_know = ConvoScreen:new {
	id = "let_me_know",
	leftDialog = "@conversation/quest_hero_of_tatooine_bounty_hunter:s_cd33dbbc", -- OK. If you find out who it is, let me know.
	stopConversation = "true",
	options = {}
}
heroOfTatBountyHunterConvoTemplate:addScreen(let_me_know);

addConversationTemplate("heroOfTatBountyHunterConvoTemplate", heroOfTatBountyHunterConvoTemplate);