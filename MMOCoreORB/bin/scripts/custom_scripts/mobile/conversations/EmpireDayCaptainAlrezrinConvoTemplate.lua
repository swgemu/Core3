EmpireDayCaptainAlezrinConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayCaptainAlezrin_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "At ease solider. I was informed of your arrival. I want to personally thank you for your excellence in dealing with these threats to Empire Day. You've outdone our expectations.",
	stopConversation = "false",
	options = {
		{"Thank you. I only wish that it hadn't come to it, but we cannot allow terrorists to stop us from celebrating the order of the Galactic Empire.", "Response_01"},
		{"I was only following direction.", "Response_02"},
	}
}
EmpireDayCaptainAlezrinConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "I've been authorized to give you this for your assistance, and we will make a notation in your record as well. You're welcome to enjoy the festivities while they last. Many will not know what you did to secure them today, but some will.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainAlezrinConvoTemplate:addScreen(Response_Accepted)

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "...",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainAlezrinConvoTemplate:addScreen(Response_Dismiss);

Faction_Deny = ConvoScreen:new {
	id = "Faction_Deny",
	customDialogText = "I think you best move along, you've seem to have already picked a side in this.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayCaptainAlezrinConvoTemplate:addScreen(Faction_Deny);

addConversationTemplate("EmpireDayCaptainAlezrinConvoTemplate", EmpireDayCaptainAlezrinConvoTemplate);