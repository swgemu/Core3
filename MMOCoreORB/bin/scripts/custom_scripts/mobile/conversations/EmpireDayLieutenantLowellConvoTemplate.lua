EmpireDayLieutenantLowellConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayLieutenantLowell_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Hello, I am Lieutenant Tanya Lowell, I'm in need of your help. I have very limited time to collect vital information that is detrimental to the Rebel Alliance. It's not what you'd expect though, but if you're willing, I will give you your task.",
	stopConversation = "false",
	options = {
		{"What kind of orders?", "Response_Accepted"},
		{"Rather ominoius, but I'll help.", "Response_Accepted"},
        {"I'm sure you can find someone more qualified than me.", "Response_Refuse"}
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "I am a Procurment Specialist for the Alliance. The item I need you to capture is not something that holds some great tangible benefit that you can touch, but I need to you to secure some spontaneous work done on behalf of Rememberance Day. I have a list here as well as the data storage you'll need to capture them holographically. It may not seem like much, but making sure people and places are not forgotten is just as important as fighting with a blaster in this war.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(Response_Accepted);

TurnInConvoScreen = ConvoScreen:new {
	id = "TurnInConvo",
	customDialogText = "Welcome back. Thank you for doing all this, it may not seem important right now, but it will be... That I promise you. I know this is a lot, but I have received a order from one of my contacts who goes by the name Fulcrum. They advised me that there is someone who can help keep safe what we've recorded.",
	stopConversation = "false",
	options = {
		{"I see. I imagine the empire would love to destroy all records of those who remember what they've done. That's the point of celebrating Empire Day isn't it?", "TurninResponse_Accepted"},
		{"Remember Alderaan! Let's make sure nothing here was forgotten.", "TurninResponse_Accepted"},
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(TurnInConvoScreen);

TurninResponse_Accepted = ConvoScreen:new {
	id = "TurninResponse_Accepted",
	customDialogText = "Exactly. Here's the waypoint to the man who can make sure these are kept safe for us, and for those who come after us. Your efforts today have done a great service for the Rebel Alliance, and for all of those who we remember on this day.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(TurninResponse_Accepted)

Response_Declined = ConvoScreen:new {
	id = "Response_Declined",
	customDialogText = "That's unfortunate, but I will continue looking. Remember Alderaan!",
	stopConversation = "true",
	options = {
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(Response_Declined);

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "Once your orders are complete, we can talk.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(Response_Dismiss);

TurninResponse_Dismiss = ConvoScreen:new {
	id = "TurninResponse_Dismiss",
	customDialogText = "Thank you for helping us.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(TurninResponse_Dismiss);

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "I think you should leave. You've made your choices.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(Deny_Faction);

Service_Noted = ConvoScreen:new {
	id = "Service_Noted",
	customDialogText = "I appreicate your assistance in this matter.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayLieutenantLowellConvoTemplate:addScreen(Service_Noted);

addConversationTemplate("EmpireDayLieutenantLowellConvoTemplate", EmpireDayLieutenantLowellConvoTemplate);