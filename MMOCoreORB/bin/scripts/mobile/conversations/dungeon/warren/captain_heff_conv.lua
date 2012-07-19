CaptainHeffConversationTemplate = ConvoTemplate:new {
	initialScreen = "heff_start",
	templateType = "Lua",
	luaClassHandler = "CaptainHeffConversationHandler",
	screens = {}
}

heff_start = ConvoScreen:new {
	id = "heff_start",
	leftDialog = "@theme_park/warren/warren:heff_start", --What do you want?
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:heff_reply_1", "heff_1"} --I have evidence!
	}
}

CaptainHeffConversationTemplate:addScreen(heff_start)

heff_1 = ConvoScreen:new {
	id = "heff_1",
	leftDialog = "@theme_park/warren/warren:heff_1", --What?  Let me see that!  So... Teraud is a traitor.  Well this is all the evidence I need.  We'll take care of this at once.
	stopConversation = "true",
	options = {}
}

CaptainHeffConversationTemplate:addScreen(heff_1)

heff_done = ConvoScreen:new {
	id = "heff_done",
	leftDialog = "@theme_park/warren/warren:heff_done", --Good to see you again!  No need to worry about Teraud's research lab.  The Empire will take care of THAT place.
	stopConversation = "true",
	options = {}
}

CaptainHeffConversationTemplate:addScreen(heff_done)

heff_bye = ConvoScreen:new {
	id = "heff_bye",
	leftDialog = "@theme_park/warren/warren:heff_bye", --No time to talk to you.  I'm a very busy man.
	stopConversation = "true",
	options = {}
}

CaptainHeffConversationTemplate:addScreen(heff_bye)

addConversationTemplate("CaptainHeffConversationTemplate", CaptainHeffConversationTemplate)