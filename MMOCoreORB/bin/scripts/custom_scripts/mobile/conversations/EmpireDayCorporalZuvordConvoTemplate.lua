EmpireDayCorporalZuvordConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayPuprusLi_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Thank you for coming. There have been spontaneous gatherings of people over this last week, each night this memorial has grown slowly, to what we see today. I reported it to my superiors and they told me to expect you. You're here for this, right?",
	stopConversation = "false",
	options = {
		{"I am, they're hoping to collect as close to life representations of these memorial sites for safe keeping. If you can help me with this recording...", "Response_01"},
		{"Let's work get this done then, if you'll help me here." , "Response_02"},
	}
}
EmpireDayCorporalZuvordConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Yes, hold on a moment... Ahh, yes! This is exactly what you need. The Lieutenant said to head back to her once you are done here.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCorporalZuvordConvoTemplate:addScreen(Response_Accepted)

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "Do you need something?",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCorporalZuvordConvoTemplate:addScreen(Response_Dismiss);

Service_Noted = ConvoScreen:new {
	id = "Service_Noted",
	customDialogText = "Thank you again. May the force be with you.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCorporalZuvordConvoTemplate:addScreen(Service_Noted);

addConversationTemplate("EmpireDayCorporalZuvordConvoTemplate", EmpireDayCorporalZuvordConvoTemplate);