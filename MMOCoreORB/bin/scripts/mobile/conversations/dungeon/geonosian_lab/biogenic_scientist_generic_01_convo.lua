biogenicScientistGeneric01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicScientistGeneric01ConvoHandler",
	screens = {}
}

init_talk = ConvoScreen:new {
	id = "init_talk",
	leftDialog = "@conversation/biogenic_scientist_generic_01:s_a1480651", -- We've got to help them! They're trapped in there!
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_01:s_e2ab2c6d","others_locked_in"}, -- Help who? Who's trapped?
		{"@conversation/biogenic_scientist_generic_01:s_cc366e42","please_get_them"}, -- Relax, I'm here to help.
		{"@conversation/biogenic_scientist_generic_01:s_a5b3f77","theyll_be_dead"}, -- I'm sure they'll be alright.
		{"@conversation/biogenic_scientist_generic_01:s_432d5b3d","they_wont_last"} -- I'll try to find help. Good-bye.
	}
}

biogenicScientistGeneric01ConvoTemplate:addScreen(init_talk);

please_get_them = ConvoScreen:new {
	id = "please_get_them",
	leftDialog = "@conversation/biogenic_scientist_generic_01:s_7c08824f", -- Please get them out. The code 11380 should open the door. Please help them.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_01:s_1e9bb201","thank_you_please_help"}, -- I'll see what I can do.
		{"@conversation/biogenic_scientist_generic_01:s_4d153d91","no_gotta_help"} -- No, I can't. I'm sorry.
	}
}

biogenicScientistGeneric01ConvoTemplate:addScreen(please_get_them);

others_locked_in = ConvoScreen:new {
	id = "others_locked_in",
	leftDialog = "@conversation/biogenic_scientist_generic_01:s_6157f01f", -- The others, in Lab Two. They're locked in, with those monsters!
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_01:s_431dec6f","youll_need_code"}, -- Can we get them out?
		{"@conversation/biogenic_scientist_generic_01:s_4d153d91","no_gotta_help"} -- No, I can't. I'm sorry.
	}
}

biogenicScientistGeneric01ConvoTemplate:addScreen(others_locked_in);

theyll_be_dead = ConvoScreen:new {
	id = "theyll_be_dead",
	leftDialog = "@conversation/biogenic_scientist_generic_01:s_c6a7e0ad", -- No... they'll be dead. Unless we can help. Will you help them?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_01:s_431dec6f","youll_need_code"}, -- Can we get them out?
		{"@conversation/biogenic_scientist_generic_01:s_4d153d91","no_gotta_help"} -- No, I can't. I'm sorry.
	}
}

biogenicScientistGeneric01ConvoTemplate:addScreen(theyll_be_dead);

youll_need_code = ConvoScreen:new {
	id = "youll_need_code",
	leftDialog = "@conversation/biogenic_scientist_generic_01:s_6cabcaaf", -- You'll need the code! 11380... that should open the door. Please go help them!
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_01:s_1e9bb201","thank_you_please_help"}, -- I'll see what I can do.
		{"@conversation/biogenic_scientist_generic_01:s_4d153d91","no_gotta_help"} -- No, I can't. I'm sorry.
	}
}

biogenicScientistGeneric01ConvoTemplate:addScreen(youll_need_code);

thank_you_please_help = ConvoScreen:new {
	id = "thank_you_please_help",
	leftDialog = "@conversation/biogenic_scientist_generic_01:s_2ebb30d8", -- Thank you... thank you. Please help them.
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeneric01ConvoTemplate:addScreen(thank_you_please_help);

no_gotta_help = ConvoScreen:new {
	id = "no_gotta_help",
	leftDialog = "@conversation/biogenic_scientist_generic_01:s_28b15c94", -- No! We've got to.... help them... got to...
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeneric01ConvoTemplate:addScreen(no_gotta_help);

they_wont_last = ConvoScreen:new {
	id = "they_wont_last",
	leftDialog = "@conversation/biogenic_scientist_generic_01:s_295ff7c4", -- No, they won't last... please help them...
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeneric01ConvoTemplate:addScreen(they_wont_last);

addConversationTemplate("biogenicScientistGeneric01ConvoTemplate", biogenicScientistGeneric01ConvoTemplate);