VisionsRichKosterConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "VisionsRichKoster_convo_handler",
	screens = {}
}

InitialConvo = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Hey you, would you like to help the Empire? We have a need of brave and patriotic loyalists to aid in a vital mission to recover property that belongs to the Empire. Are you interested?",
	stopConversation = "false",
	options = {
		{"I am, what more can you tell me about this mission?", "Response_01"},
		{"I mean, if there's something in it for me, why not? I'm a loyal citizen.", "Response_02"},
		{"I can't help you right now. I am sorry.", "Response_03"},
	}
}
VisionsRichKosterConvoTemplate:addScreen(InitialConvo);

Response_01 = ConvoScreen:new {
	id = "Response_01",
	customDialogText = "I will transmit a waypoint on Yavin IV where you will meet your next contact, she will tell you more once you meet her. Don't be late, time is short!",
	stopConversation = "true",
	options = {
	}
}
VisionsRichKosterConvoTemplate:addScreen(Response_01);

Response_02 = ConvoScreen:new {
	id = "Response_02",
	customDialogText = "I will transmit a waypoint on Yavin IV where you will meet your next contact, she will tell you more once you meet her. Don't be late, time is short!",
	stopConversation = "true",
	options = {
	}
}
VisionsRichKosterConvoTemplate:addScreen(Response_02);

Response_03 = ConvoScreen:new {
	id = "Response_03",
	customDialogText = "If you change your mind, I'll be here until I'm called offworld. The Empire doesn't wait for any of us.",
	stopConversation = "true",
	options = {
	}
}
VisionsRichKosterConvoTemplate:addScreen(Response_03);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "You must hurry to Yavin IV, our officer on the ground is awaiting your arrival!",
	stopConversation = "true",
	options = {
	}
}
VisionsRichKosterConvoTemplate:addScreen(Response_Accepted);

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "Keep walking if you know what is good for you!",
	stopConversation = "true",
	options = {
	}
}
VisionsRichKosterConvoTemplate:addScreen(Deny_Faction);

Service_Noted = ConvoScreen:new {
	id = "Service_Noted",
	customDialogText = "I will be sure to pass word on of your loyal service.",
	stopConversation = "true",
	options = {
	}
}
VisionsRichKosterConvoTemplate:addScreen(Service_Noted);

addConversationTemplate("VisionsRichKosterConvoTemplate", VisionsRichKosterConvoTemplate);
