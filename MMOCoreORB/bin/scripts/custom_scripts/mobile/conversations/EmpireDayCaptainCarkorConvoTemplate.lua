EmpireDayCaptainCarkorConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayCaptainCarkor_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Ah yes, the Major radioed that you were on the way. I've received suspicions reports that a local group is preparing a terrorist attack on Empire Day. Unfortunately, I've no spare troops to send right now during these most crucial steps. I'm hoping you can investigate and report back as quickly as you can, good citizen.",
	stopConversation = "false",
	options = {
		{"It would be a great honor to help make things run smoothly. Tell me what you have and where I'm needed.", "Response_Accepted"},
		{"Just show me where to go, I'll deal with this situation personally.", "Response_Accepted"},
	}
}
EmpireDayCaptainCarkorConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Excellent, here's their location. Intelligence hasn't identified if they are Rebel or just disgruntled citizens. Use your best judgement.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainCarkorConvoTemplate:addScreen(Response_Accepted)

Awaiting_Completion = ConvoScreen:new {
	id = "Awaiting_Completion",
	customDialogText = "I have not received any reports that the terrorists have been dealt with. Please see to this matter.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainCarkorConvoTemplate:addScreen(Awaiting_Completion)

TurnInConvoScreen = ConvoScreen:new {
	id = "TurnInConvo",
	customDialogText = "Were you able to complete your mission? I could very easily dispatch a squad in a day, but they'll more than likely be long gone by then.",
	stopConversation = "false",
	options = {
		{"These scoundrels won't be a problem for much longer.", "Turnin_Accepted"},
		{"I've dealt with them.", "Turnin_Accepted"},
	}
}
EmpireDayCaptainCarkorConvoTemplate:addScreen(TurnInConvoScreen);

Turnin_Accepted = ConvoScreen:new {
	id = "Turnin_Accepted",
	customDialogText = "Very good news, I can't thank you enough for helping us on such short notice. I do have another request, my contemporary on Naboo has requested extra support. Could I trouble you to check in there as well? It would be most helpful.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainCarkorConvoTemplate:addScreen(Turnin_Accepted)

TurninResponse_Dismiss = ConvoScreen:new {
	id = "TurninResponse_Dismiss",
	customDialogText = "Good luck, thank you for helping make this a safe and successful Empire Day.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainCarkorConvoTemplate:addScreen(TurninResponse_Dismiss);

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "I think you best move along, you've seem to have already picked a side in this.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainCarkorConvoTemplate:addScreen(Deny_Faction);

addConversationTemplate("EmpireDayCaptainCarkorConvoTemplate", EmpireDayCaptainCarkorConvoTemplate);