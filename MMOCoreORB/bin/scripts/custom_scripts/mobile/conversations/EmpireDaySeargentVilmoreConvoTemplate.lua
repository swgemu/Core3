EmpireDaySeargentVilmoreConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDaySeargentVilmore_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "So you're the one they sent over for this? I'm part of the detachment keeping an eye on the base here and assisting what assets remain on planet. I can't say exactly who made this, other than it could have been some of our people, but I loathe to disturb it either way.",
	stopConversation = "false",
	options = {
		{"The Lieutenant wanted me to record it, I guess for posterity right?", "Response_Accepted"},
		{"Where do I record it?" , "Response_Accepted"},
	}
}
EmpireDaySeargentVilmoreConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Ah yes, I'll handle that for you, just give me a moment...It is recorded on the datapad he gave you. Hold on, it looks like she has another location to dispatch you to. Here's the information.",
	stopConversation = "true",
	options = {
	}
}
EmpireDaySeargentVilmoreConvoTemplate:addScreen(Response_Accepted)

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "Can I help you?",
	stopConversation = "true",
	options = {
	}
}
EmpireDaySeargentVilmoreConvoTemplate:addScreen(Response_Dismiss);

Faction_Deny = ConvoScreen:new {
	id = "Faction_Deny",
	customDialogText = "I think you best move along, you've seem to have already picked a side in this.",
	stopConversation = "true",
	options = {
	}
}
EmpireDaySeargentVilmoreConvoTemplate:addScreen(Faction_Deny);

Service_Noted = ConvoScreen:new {
	id = "Service_Noted",
	customDialogText = "Thank you again. May the force be with you.",
	stopConversation = "true",
	options = {
	}
}
EmpireDaySeargentVilmoreConvoTemplate:addScreen(Service_Noted);

addConversationTemplate("EmpireDaySeargentVilmoreConvoTemplate", EmpireDaySeargentVilmoreConvoTemplate);