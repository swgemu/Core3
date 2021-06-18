EmpireDayPuprusLiConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayPuprusLi_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Everyone, hold your fire, but keep them pointed at this one. Got somethin' to say for yourself then, or are you planning to kill more on your vaunted 'Empire Day'? You people disgust me.",
	stopConversation = "false",
	options = {
		{"Throw down your weapons. Turn and run... Scower away and you just might live.", "Response_Accepted"},
		{"Try me, really...You think your group is a problem to the Empire?" , "Response_Accepted"},
	}
}
EmpireDayPuprusLiConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Remeber Alderaan!" ,
	stopConversation = "true",
	options = {
	}
}
EmpireDayPuprusLiConvoTemplate:addScreen(Response_Accepted)

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "Who are you?",
	stopConversation = "true",
	options = {
	}
}
EmpireDayPuprusLiConvoTemplate:addScreen(Response_Dismiss);

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "Listen here, I don't know what's going on, but I shouldn't be near you or anyone for that matter.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayPuprusLiConvoTemplate:addScreen(Deny_Faction);

addConversationTemplate("EmpireDayPuprusLiConvoTemplate", EmpireDayPuprusLiConvoTemplate);