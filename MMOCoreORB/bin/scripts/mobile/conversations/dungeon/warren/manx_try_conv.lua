ManxTryConversationTemplate = ConvoTemplate:new {
	initialScreen = "researcher_start",
	templateType = "Lua",
	luaClassHandler = "ManxTryConversationHandler",
	screens = {}
}

researcher_start = ConvoScreen:new {
	id = "researcher_start",
	leftDialog = "@theme_park/warren/warren:researcher_start", --It's hopeless!  The reactor core is going to blow!  We'll all die!
	stopConversation = "false",
	options = {
		{"@theme_park/warren/warren:researcher_reply_1", "researcher_1"} --What do we do?
	}
}

ManxTryConversationTemplate:addScreen(researcher_start)

researcher_1 = ConvoScreen:new {
	id = "researcher_1",
	leftDialog = "@theme_park/warren/warren:researcher_1", --The only way to fix it, is to get the spare reactor core rods from the basement... behind the holding pen. The backup system should have taken over, but I think it was manually overridden.
	stopConversation = "false",
	options = {}
}

ManxTryConversationTemplate:addScreen(researcher_1)

researcher_2 = ConvoScreen:new {
	id = "researcher_2",
	leftDialog = "@theme_park/warren/warren:researcher_2", --Good thing the reactor has been disabled!
	stopConversation = "true",
	options = {}
}

ManxTryConversationTemplate:addScreen(researcher_2)

researcher_3 = ConvoScreen:new {
	id = "researcher_3",
	leftDialog = "@theme_park/warren/warren:researcher_3", --Now the reactor core rods need to be put in the reactor core. But the door is locked... there are two manual override switches on this floor... somewhere.
	stopConversation = "true",
	options = {}
}

ManxTryConversationTemplate:addScreen(researcher_3)

addConversationTemplate("ManxTryConversationTemplate", ManxTryConversationTemplate)