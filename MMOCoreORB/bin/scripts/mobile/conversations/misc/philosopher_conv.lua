philosopherConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "philosopherConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "", -- Determined and set by convo handler
	stopConversation = "true",
	options = {}
}
philosopherConvoTemplate:addScreen(init);

addConversationTemplate("philosopherConvoTemplate", philosopherConvoTemplate);
