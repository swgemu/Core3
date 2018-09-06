biogenicRandomConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "biogenicRandomConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "",
	stopConversation = "true",
	options = {	}
}
biogenicRandomConvoTemplate:addScreen(init);

addConversationTemplate("biogenicRandomConvoTemplate", biogenicRandomConvoTemplate);