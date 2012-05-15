death_watch_rescue_scientist_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "death_watch_rescue_scientist_handler",
	screens = {}
}

death_watch_rescue_scientist_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_rescue_scientist:s_d3b5ac87", --Ah! I'm so glad you've come
	stopConversation = "true",
	options = {
	}
}

death_watch_rescue_scientist_convotemplate:addScreen(death_watch_rescue_scientist_convoscreen1);

death_watch_rescue_scientist_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/death_watch_rescue_scientist:s_d3b5ac87", --Thank you for earlier
	stopConversation = "true",
	options = {
	}
}

death_watch_rescue_scientist_convotemplate:addScreen(death_watch_rescue_scientist_convoscreen2);

death_watch_rescue_scientist_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/death_watch_rescue_scientist:s_8801c9a5", --Thank you
	stopConversation = "true",
	options = {
	}
}

death_watch_rescue_scientist_convotemplate:addScreen(death_watch_rescue_scientist_convoscreen3);

addConversationTemplate("death_watch_rescue_scientist_convotemplate", death_watch_rescue_scientist_convotemplate);
