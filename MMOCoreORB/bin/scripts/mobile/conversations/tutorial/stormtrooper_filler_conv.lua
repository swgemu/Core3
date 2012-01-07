stormtrooper_filler_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	screens = {}
}

stormtrooper_filler_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:trooper_move_along",
	stopConversation = "true",
	options = {
	}
}

stormtrooper_filler_convotemplate:addScreen(stormtrooper_filler_convoscreen1);

addConversationTemplate("stormtrooper_filler_convotemplate", stormtrooper_filler_convotemplate);
