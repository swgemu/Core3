kailaMinConvoTemplate = ConvoTemplate:new {
	initialScreen = "start",
	templateType = "Lua",
	luaClassHandler = "kailaMinConvoHandler",
	screens = {}
}

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/c_story1_2_mole:s_25", -- Why hello there! Is there something that I can do for you?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_2_mole:s_27", "tell_more"}, -- You can tell me about that pilot you saw.
		{"@conversation/c_story1_2_mole:s_31", "lovely_lady"}, -- I just wanted to say 'hello' to a lovely lady.
		{"@conversation/c_story1_2_mole:s_41", "someone_else"}, -- Nothing.  I thought you were someone else.
	}
}

kailaMinConvoTemplate:addScreen(start);

start_not_ready = ConvoScreen:new {
	id = "start_not_ready",
	leftDialog = "@conversation/c_story1_2_mole:s_25", -- Why hello there! Is there something that I can do for you?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_2_mole:s_31", "lovely_lady"}, -- I just wanted to say 'hello' to a lovely lady.
		{"@conversation/c_story1_2_mole:s_41", "someone_else"}, -- Nothing.  I thought you were someone else.
	}
}

kailaMinConvoTemplate:addScreen(start_not_ready);

start_ambushed = ConvoScreen:new {
	id = "start_ambushed",
	leftDialog = "@conversation/c_story1_2_mole:s_25", -- Why hello there! Is there something that I can do for you?
	stopConversation = "false",
	options = {
		{"You led me into an ambush!", "ambush"},
		{"@conversation/c_story1_2_mole:s_31", "lovely_lady"}, -- I just wanted to say 'hello' to a lovely lady.
		{"@conversation/c_story1_2_mole:s_41", "someone_else"}, -- Nothing.  I thought you were someone else.
	}
}

kailaMinConvoTemplate:addScreen(start_ambushed);

tell_more = ConvoScreen:new {
	id = "tell_more",
	leftDialog = "@conversation/c_story1_2_mole:s_29", -- Ah, I know who you are now.  I'm glad you came to see me.  I was beginning to wonder if you would.  Listen carefully, head directly northeast.  It's north of some ruins and west of a statue head. Here are coordinates if you prefer that.
	stopConversation = "true",
	options = {}
}

kailaMinConvoTemplate:addScreen(tell_more);

lovely_lady = ConvoScreen:new {
	id = "lovely_lady",
	leftDialog = "@conversation/c_story1_2_mole:s_33", -- You are very sweet, but I'm waiting for someone.
	stopConversation = "true",
	options = {}
}

kailaMinConvoTemplate:addScreen(lovely_lady);

someone_else = ConvoScreen:new {
	id = "someone_else",
	leftDialog = "@conversation/c_story1_2_mole:s_43", -- All right.  We all make mistakes.
	stopConversation = "true",
	options = {}
}

kailaMinConvoTemplate:addScreen(someone_else);

ambush = ConvoScreen:new {
	id = "ambush",
	leftDialog = "@static_npc/naboo/kima_nazith:npc_breech_2", -- If you mess with me, you flirt with death! Sssss!
	stopConversation = "true",
	options = {}
}

kailaMinConvoTemplate:addScreen(ambush);

addConversationTemplate("kailaMinConvoTemplate", kailaMinConvoTemplate);
