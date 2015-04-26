tutorialCommonerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialCommonerConvoHandler",
	screens = {}
}

initCommoner1 = ConvoScreen:new {
	id = "initCommoner1",
	leftDialog = "@newbie_tutorial/newbie_convo:darn_empire",
	stopConversation = "true",
	options = {}
}

tutorialCommonerConvoTemplate:addScreen(initCommoner1);

initCommoner2 = ConvoScreen:new {
	id = "initCommoner2",
	leftDialog = "@newbie_tutorial/newbie_convo:leave_me_alone",
	stopConversation = "true",
	options = {}
}

tutorialCommonerConvoTemplate:addScreen(initCommoner2);

addConversationTemplate("tutorialCommonerConvoTemplate", tutorialCommonerConvoTemplate);
