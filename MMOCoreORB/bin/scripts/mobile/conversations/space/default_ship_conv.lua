default_ship_convo_template = ConvoTemplate:new {
	initialScreen = "default_taunt",
	templateType = "Lua",
	luaClassHandler = "defaultShipConvoHandler",
	screens = {}
}

-- Default Greeting
default_taunt = ConvoScreen:new {
	id = "default_taunt",
	leftDialog = "",
	stopConversation = "true",
	options = {}
}
default_ship_convo_template:addScreen(default_taunt);

addConversationTemplate("default_ship_convo_template", default_ship_convo_template);
