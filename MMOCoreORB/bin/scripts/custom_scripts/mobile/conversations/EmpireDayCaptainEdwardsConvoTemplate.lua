EmpireDayCaptainEdwardsConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayCaptainEdwards_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "May I see that datapad? Yes, I see. I'm Captain Cheri Edwards. I'm with the command staff here at this outpost. We noticed this memorial was put up without anyone's knowledge over the last twenty-four hours. Rori hasn't seen the worst of this war, but many people make passage between here and far more treacherous planets. I can understand why people do this, I just wish there was a better way to pay homage to the friends, family and comrades that we've lost during these trying times.",
	stopConversation = "false",
	options = {
		{"I see what you are saying, at least we can record them for now. Maybe something more can be done later.", "Response_Accepted"},
		{"Here's the datapad. We'll collect what we can. That's all we can do." , "Response_Accepted"},
	}
}
EmpireDayCaptainEdwardsConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "You are right. Let me see this holo-recorder...okay...yeah that should do it. Here's the datapad back. I did get word that you're wanted at another location. I'll add the information to your datapad. Good luck.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainEdwardsConvoTemplate:addScreen(Response_Accepted)

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "Do you have something else to report?",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainEdwardsConvoTemplate:addScreen(Response_Dismiss);

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "I think you best move along, you've made your bed, time to sleep in it.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainEdwardsConvoTemplate:addScreen(Deny_Faction);

Service_Noted = ConvoScreen:new {
	id = "Service_Noted",
	customDialogText = "I appreicate your assistance in this matter.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainEdwardsConvoTemplate:addScreen(Service_Noted);

addConversationTemplate("EmpireDayCaptainEdwardsConvoTemplate", EmpireDayCaptainEdwardsConvoTemplate);