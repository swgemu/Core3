stormtrooperFillerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialStormtrooperFillerConvoHandler",
	screens = {}
}

moveAlong = ConvoScreen:new {
	id = "moveAlong",
	leftDialog = "@newbie_tutorial/newbie_convo:trooper_move_along",
	stopConversation = "true",
	options = {
	}
}

stormtrooperFillerConvoTemplate:addScreen(moveAlong);

addConversationTemplate("stormtrooperFillerConvoTemplate", stormtrooperFillerConvoTemplate);
