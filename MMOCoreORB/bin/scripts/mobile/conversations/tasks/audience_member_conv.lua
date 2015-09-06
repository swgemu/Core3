audienceMemberConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "audienceMemberConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "", -- Determined and set by convo handler
	stopConversation = "true",
	options = {}
}
audienceMemberConvoTemplate:addScreen(init);

addConversationTemplate("audienceMemberConvoTemplate", audienceMemberConvoTemplate);