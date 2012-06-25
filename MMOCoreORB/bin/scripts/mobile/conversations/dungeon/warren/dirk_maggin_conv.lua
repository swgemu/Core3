DirkMagginConversationTemplate = ConvoTemplate:new {
	initialScreen = "loyalist_start",
	templateType = "Normal",
	luaClassHandler = "",
	screens = {}
}

loyalist_start = ConvoScreen:new {
	id = "loyalist_start",
	leftDialog = "@theme_park/warren/warren:loyalist_start", --Wow, the shock must have broken the cyborg circuitry... I can think on my own again... it was horrible, I volunteered to be one of Teraud's Loyalists, but the cyborg device was controlling my mind... Look out for Teraud, he's a megalomaniac, and he thinks he can topple the Emperor...
	stopConversation = "true",
	options = {
	}
}

DirkMagginConversationTemplate:addScreen(loyalist_start);

addConversationTemplate("DirkMagginConversationTemplate", DirkMagginConversationTemplate);