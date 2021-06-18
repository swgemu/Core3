EmpireDayCaretakerConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayCaretaker_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Welcome to this place. I am told you have something to show me. I think I will be able to help you.",
	stopConversation = "false",
	options = {
		{"Here is the data Lieutenant Lowell had me collect from the locations where people are particpating in this somber day of rememberance.", "Response_Accepted"},
		{"Here is what we collected, I hope it helps people to better understand what we've lost and what we'll need to celebrate." , "Response_Accepted"},
	}
}
EmpireDayCaretakerConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "I'll keep this safe and make sure that all citizens will be able to view it for years to come. We cannot let people forget our history, or surely we shall be doomed to repeat it. Take this, it's a copy of what you uncovered in a small hologram. May the force be with you.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaretakerConvoTemplate:addScreen(Response_Accepted)

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "Never forget what has been lost, hold dear those memories of what came before. May the force be with you.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaretakerConvoTemplate:addScreen(Deny_Faction);

Service_Noted = ConvoScreen:new {
	id = "Service_Noted",
	customDialogText = "May the force be with you.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaretakerConvoTemplate:addScreen(Service_Noted);

General_Greeting = ConvoScreen:new {
	id = "General_Greeting",
	customDialogText = "We will never forget those who have gone on. May the Force be with you.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaretakerConvoTemplate:addScreen(General_Greeting);

addConversationTemplate("EmpireDayCaretakerConvoTemplate", EmpireDayCaretakerConvoTemplate);