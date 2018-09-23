biogenicRandomConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "BiogenicRandomConvoHandler",
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