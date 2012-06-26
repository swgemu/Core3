MirlaConversationTemplate = ConvoTemplate:new {
	initialScreen = "mirla_start",
	templateType = "Lua",
	luaClassHandler = "MirlaConversationHandler",
	screens = {}
}

mirla_start = ConvoScreen:new {
	id = "mirla_start",
	leftDialog = "@theme_park/warren/warren:mirla_start", --(sob) What... what do you want?
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:mirla_reply_1", "mirla_1"}, --What's wrong?
	}
}

MirlaConversationTemplate:addScreen(mirla_start);

mirla_1 = ConvoScreen:new {
	id = "mirla_1",
	leftDialog = "@theme_park/warren/warren:mirla_1", --How can you ask...
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:mirla_1_reply_1", "mirla_2"}, --I have some bad news
		{"@theme_park/warren/warren:mirla_1_reply_2", "mirla_3"} --Don't worry
	}
}

MirlaConversationTemplate:addScreen(mirla_1);

mirla_2 = ConvoScreen:new {
	id = "mirla_2",
	leftDialog = "@theme_park/warren/warren:mirla_2", --My husband is dead?
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:mirla_1_reply_2", "mirla_3"}, --Don't worry
		{"@theme_park/warren/warren:mirla_2_reply_1", "mirla_4"}, --I will
	}
}

MirlaConversationTemplate:addScreen(mirla_2);

mirla_3 = ConvoScreen:new {
	id = "mirla_3",
	leftDialog = "@theme_park/warren/warren:mirla_3", --Oh I do hope so... but I have a bad feeling. Please leave me alone.
	stopConversation = "true",
	options = {}
}

MirlaConversationTemplate:addScreen(mirla_3);

mirla_4 = ConvoScreen:new {
	id = "mirla_4",
	leftDialog = "@theme_park/warren/warren:mirla_4", --The first thing you should do is to get to the Inquisitor. Teraud's men captured her and put her in a cell upstairs. You'll need the passcode to unlock the cell door, but I can tell you what that is.
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:mirla_1_reply_2", "mirla_3"}, --Don't worry
		{"@theme_park/warren/warren:mirla_4_reply_1", "mirla_password"}, --What is it?
	}
}

MirlaConversationTemplate:addScreen(mirla_4);

mirla_password = ConvoScreen:new {
	id = "mirla_password",
	leftDialog = "@theme_park/warren/warren:mirla_password", --The password is - %TO - just speak that near the cell door to unlock it. Good luck.
	stopConversation = "true",
	options = {}
}

MirlaConversationTemplate:addScreen(mirla_password);

mirla_done = ConvoScreen:new {
	id = "mirla_done",
	leftDialog = "@theme_park/warren/warren:mirla_done", --I can't thank you enough for the compassion you've shown me.  And you've exposed Teraud's evil plans to the Empire.  I know the Emperor will take care of that mad scientist and this terrible place now.
	stopConversation = "true",
	options = {}
}

MirlaConversationTemplate:addScreen(mirla_done);


mirla_get_teraud = ConvoScreen:new {
	id = "mirla_get_teraud",
	leftDialog = "@theme_park/warren/warren:mirla_get_teraud", --We know that Teraud is a madman, but the Empire will require proof of his treachery.  You've got to collect evidence against him and take it to the proper authorities.  Please!  Before it is too late!
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:mirla_1_reply_2", "mirla_3"}, --Don't worry
		{"@theme_park/warren/warren:mirla_2_reply_1", "mirla_4"} --I will
	}
}

MirlaConversationTemplate:addScreen(mirla_get_teraud);

addConversationTemplate("MirlaConversationTemplate", MirlaConversationTemplate);