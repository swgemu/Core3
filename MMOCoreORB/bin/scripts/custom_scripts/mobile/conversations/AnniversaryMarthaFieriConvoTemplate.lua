AnniversaryMarthaFieriConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "AnniversaryMarthaFieri_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Looks like someone stuck their hand in the cookie jar again. Yeah, our friend send me a holo message that you were coming. Let me see that chip.",
	stopConversation = "false",
	options = {
		{"Here it is, I'm not sure why you know our 'friend' but sure...let's see what happens.", "Response_Accepted"},
		{"It's time to find out who's behind this.", "Response_Accepted"},
	}
}
AnniversaryMarthaFieriConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "All right, all right. Give me a minute to run this information...Ahh here it is. Here's the waypoint that might lead you to what these thieves were up to. Be safe, stranger.",
	stopConversation = "true",
	options = {
	}
}
AnniversaryMarthaFieriConvoTemplate:addScreen(Response_Accepted);

Service_Noted = ConvoScreen:new {
	id = "Service_Noted",
	customDialogText = "Good luck, I'm not exactly sure what you'll find.",
	stopConversation = "true",
	options = {
	}
}
AnniversaryMarthaFieriConvoTemplate:addScreen(Service_Noted);

Service_Needed = ConvoScreen:new {
	id = "Service_Needed",
	customDialogText = "I don't think I have any more information of value to you at this time.",
	stopConversation = "true",
	options = {
	}
}
AnniversaryMarthaFieriConvoTemplate:addScreen(Service_Needed);

Responce_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "Can I help you?",
	stopConversation = "true",
	options = {
	}
}
AnniversaryMarthaFieriConvoTemplate:addScreen(Responce_Dismiss);

addConversationTemplate("AnniversaryMarthaFieriConvoTemplate", AnniversaryMarthaFieriConvoTemplate);