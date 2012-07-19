OevittPiboiConversationTemplate = ConvoTemplate:new {
	initialScreen = "escapee_start",
	templateType = "Lua",
	luaClassHandler = "OevittPiboiConversationHandler",
	screens = {}
}

escapee_start = ConvoScreen:new {
	id = "escapee_start",
	leftDialog = "@theme_park/warren/warren:escapee_start", --I can't believe I escaped that terrible place!
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:escapee_reply_1", "escapee_1"}, --What place?
	}
}

OevittPiboiConversationTemplate:addScreen(escapee_start);

escapee_haskey = ConvoScreen:new {
	id = "escapee_haskey",
	leftDialog = "@theme_park/warren/warren:escapee_haskey", --I already told you!  I even gave you a passkey to get inside!  Won't you at least TRY to put a stop to the horrible experiments there?
	stopConversation = "true",
	options = {}
}

OevittPiboiConversationTemplate:addScreen(escapee_haskey);

escapee_1 = ConvoScreen:new {
	id = "escapee_1",
	leftDialog = "@theme_park/warren/warren:escapee_1", --The Warren!  It's a terrible place!  The horrors!
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:escapee_1_reply_1", "escapee_2"} --Where is that?
	}
}

OevittPiboiConversationTemplate:addScreen(escapee_1);

escapee_2 = ConvoScreen:new {
	id = "escapee_2",
	leftDialog = "@theme_park/warren/warren:escapee_2", --Here... Here's a waypoint that leads to the dreadful place.  I'll give you the passkey to get in as well.  Maybe you can put a stop to the horrible experiments that happen there.
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:escapee_1_reply_2", "escapee_3"} --What's so bad about it?
	}
}

OevittPiboiConversationTemplate:addScreen(escapee_2);

escapee_3 = ConvoScreen:new {
	id = "escapee_3",
	leftDialog = "@theme_park/warren/warren:escapee_3", --Oh the horrors committed there are unspeakable.  Some sort of research... on people's BRAINS!
	stopConversation = "true",
	options = {}
}

OevittPiboiConversationTemplate:addScreen(escapee_3);


addConversationTemplate("OevittPiboiConversationTemplate", OevittPiboiConversationTemplate);
