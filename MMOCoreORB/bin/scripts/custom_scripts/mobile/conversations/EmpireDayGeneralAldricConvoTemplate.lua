EmpireDayGeneralAldricConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayGeneralAldric_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Ah yes, you're the one Captain Carkor radioed me about. I'm General Swithun Aldric. I've been entrusted to oversee the miltiary parade for Empire Day, and to uphold its security. That's one of the reasons you were directed here. Not all rebellions are one man making a stand, but often made up of many, trying to bring discord and chaos to the order this day represents. This is why I need you to intercept a group of rebel scum that we suspect are behind these nefarious activites.",
	stopConversation = "false",
	options = {
		{"Why would they attack a parade representing the miltiary might of the Empire, sir?", "Response_Accepted"},
		{"This seems foolish, even for rebels, right Sir?", "Response_Accepted"},
	}
}
EmpireDayGeneralAldricConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Be that as it may, I still need it looked into before any of this starts. Those are your orders. Return when you've dealt with these fools.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayGeneralAldricConvoTemplate:addScreen(Response_Accepted)

TurnInConvoScreen = ConvoScreen:new {
	id = "TurnInConvo",
	customDialogText = "You've returned, very good. What is your report, solider?",
	stopConversation = "false",
	options = {
		{"Senseless, this violence and to acomplish what? It's sad, but they are dealt with, Sir.", "Turnin_Response_01"},
		{"The threat was removed, Sir. It is done.", "Turnin_Response_02"},
	}
}
EmpireDayGeneralAldricConvoTemplate:addScreen(TurnInConvoScreen);

TurninResponse_Accepted = ConvoScreen:new {
	id = "TurninResponse_Accepted",
	customDialogText = "Very well done. I've already dispatched your information to my superiors. You're being ordered to appear at the Imperial Retreat on Naboo. You've caught the attention of the man organizing the core world celebrations. Don't keep him waiting.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayGeneralAldricConvoTemplate:addScreen(TurninResponse_Accepted)

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "Have you completed your orders yet?",
	stopConversation = "true",
	options = {
	}
}
EmpireDayGeneralAldricConvoTemplate:addScreen(Response_Dismiss);

TurninResponse_Dismiss = ConvoScreen:new {
	id = "TurninResponse_Dismiss",
	customDialogText = "I appreciate your work here, good luck.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayGeneralAldricConvoTemplate:addScreen(TurninResponse_Dismiss);

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "I think you best move along, it seems to have already picked a side in this.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayGeneralAldricConvoTemplate:addScreen(Deny_Faction);
Not_Eligible = ConvoScreen:new {
	id = "Not_Eligble",
	customDialogText = "I am extremely busy with preparations, go away.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayGeneralAldricConvoTemplate:addScreen(Not_Eligible);

addConversationTemplate("EmpireDayGeneralAldricConvoTemplate", EmpireDayGeneralAldricConvoTemplate);