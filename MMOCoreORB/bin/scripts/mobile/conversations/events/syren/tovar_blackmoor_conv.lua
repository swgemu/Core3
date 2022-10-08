tovarBlackmoorConvoTemplate = ConvoTemplate:new {
	initialScreen = "start",
	templateType = "Lua",
	luaClassHandler = "tovarBlackmoorConvoHandler",
	screens = {}
}

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/c_story1_2_chemist:s_4", -- Please don't kill me!  I have information that you probably want.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_2_chemist:s_38", "tell_more"}, -- Go on then, talk.
		{"@conversation/c_story1_2_chemist:s_40", "tell_more"}, -- I won't kill you, but what can you offer me?
	}
}

tovarBlackmoorConvoTemplate:addScreen(start);

start_finished = ConvoScreen:new {
	id = "start_finished",
	leftDialog = "@conversation/c_story1_2_chemist:s_98", -- And?
	stopConversation = "true",
	options = {}
}

tovarBlackmoorConvoTemplate:addScreen(start_finished);

start_not_ready = ConvoScreen:new {
	id = "start_not_ready",
	leftDialog = "@conversation/c_story1_2_mole:s_25", -- Why hello there! Is there something that I can do for you?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_2_mole:s_41", "someone_else"}, -- Nothing.  I thought you were someone else.
	}
}

tovarBlackmoorConvoTemplate:addScreen(start_not_ready);

tell_more = ConvoScreen:new {
	id = "tell_more",
	leftDialog = "@conversation/c_story1_2_chemist:s_39", -- I have been analyzing the spice that you have.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_2_chemist:s_96", "what_spice"}, -- What spice?
	}
}

tovarBlackmoorConvoTemplate:addScreen(tell_more);

what_spice = ConvoScreen:new {
	id = "what_spice",
	leftDialog = "@conversation/c_story1_2_chemist:s_100", -- I know that you found a spice sample, the local Black Sun leaders were talking about it earlier today.  That's why they set up that trap for you.   They want a piece of the action. I don't know the name of this spice, but it seems to be medicinal in nature, and rare.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_2_chemist:s_104", "blacksun"}, -- What does the Black Sun want with it? Most rare medicines are publically available.
	}
}

tovarBlackmoorConvoTemplate:addScreen(what_spice);

blacksun = ConvoScreen:new {
	id = "blacksun",
	leftDialog = "@conversation/c_story1_2_chemist:s_106", -- Not this kind.  That's what you don't understand.  It's being smuggled and hoarded by the Rebel Alliance.  They must know where it comes from and are keeping it for themselves.  The pilot that you are looking for was smuggling the spice for them.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_2_chemist:s_110", "reward"}, -- Doesn't surprise me in the least.  Those rock-sucking terrorists would do anything.
	}
}

tovarBlackmoorConvoTemplate:addScreen(blacksun);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/c_story1_2_chemist:s_118", --Believe it.  The Black Sun will actually let the average person get a hold of this life-sustaining spice...once I know what it does...for a price. I gave you more information than I probably should.  Take this and go.
	stopConversation = "true",
	options = {}
}

tovarBlackmoorConvoTemplate:addScreen(reward);

someone_else = ConvoScreen:new {
	id = "someone_else",
	leftDialog = "@conversation/c_story1_2_mole:s_43", --All right.  We all make mistakes.
	stopConversation = "true",
	options = {}
}

tovarBlackmoorConvoTemplate:addScreen(someone_else);

addConversationTemplate("tovarBlackmoorConvoTemplate", tovarBlackmoorConvoTemplate);
