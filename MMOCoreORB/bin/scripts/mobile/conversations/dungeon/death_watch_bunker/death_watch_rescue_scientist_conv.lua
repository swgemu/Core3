deathWatchRescueScientistConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchRescueScientistConvoHandler",
	screens = {}
}

thanks1 = ConvoScreen:new {
	id = "thanks1",
	leftDialog = "@conversation/death_watch_rescue_scientist:s_d3b5ac87", -- Ah! I'm so glad you've come! I thought I was done for! Here, take this as a symbol of my appreciation. I need to get out of here!
	stopConversation = "true",
	options = {
	}
}
deathWatchRescueScientistConvoTemplate:addScreen(thanks1);

thanks2 = ConvoScreen:new {
	id = "thanks2",
	leftDialog = "@conversation/death_watch_rescue_scientist:s_b4b8c363", -- Whew! Thank you for rescuing me. I appreciate it! I have to get out of here quickly!
	stopConversation = "true",
	options = {
	}
}
deathWatchRescueScientistConvoTemplate:addScreen(thanks2);

thanks3 = ConvoScreen:new {
	id = "thanks3",
	leftDialog = "@conversation/death_watch_rescue_scientist:s_8801c9a5", -- Thank you for rescuing me. I am truly in your debt. Forgive me, but I must get out of here quickly. Thank you again.
	stopConversation = "true",
	options = {
	}
}
deathWatchRescueScientistConvoTemplate:addScreen(thanks3);

return_thanks = ConvoScreen:new {
	id = "return_thanks",
	leftDialog = "@conversation/death_watch_rescue_scientist:s_bbc873d5", -- Thank you for saving me earlier. Getting out is harder than I thought. I'm devising my plan for escape now. You needn't worry about me anymore.
	stopConversation = "true",
	options = {
	}
}
deathWatchRescueScientistConvoTemplate:addScreen(return_thanks);

addConversationTemplate("deathWatchRescueScientistConvoTemplate", deathWatchRescueScientistConvoTemplate);
