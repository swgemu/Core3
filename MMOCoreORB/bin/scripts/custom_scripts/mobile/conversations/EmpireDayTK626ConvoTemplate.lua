EmpireDayTK626ConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayTK626_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Loyal Citizen, as you might see from your surroundings, we are preparing for Empire Day. I've been asked to task any able-bodied Imperial to report to my superior. He has urgent need of someone of your talents.",
	stopConversation = "false",
	options = {
		{"It's Empire Day already? Of course I'll help! Just tell me where I'm needed.", "Response_01"},
		{"You're not going to have me crammed into one of those tin cans driving it for hours on a desert planet, right?", "Response_02"},
        {"I'm not really going to be of much help, but I'll try to attend the festivities.", "Response_03"}
	}
}
EmpireDayTK626ConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Your dedication is admirable. Take these orders. The Captain will explain more. Now if you'll excuse me, I have a lot to do myself.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayTK626ConvoTemplate:addScreen(Response_Accepted);

Response_Declined = ConvoScreen:new {
	id = "Response_Declined",
	customDialogText = "I'll inform the Captain that you are unable to assist us in this time of need. If you don't mind, I have a lot of work to attend to.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayTK626ConvoTemplate:addScreen(Response_Declined);

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "I'm very busy right now, I cannot help you. Speak with the constables if you need help.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayTK626ConvoTemplate:addScreen(Response_Dismiss);

Faction_Deny = ConvoScreen:new {
	id = "Faction_Deny",
	customDialogText = "I think you best move along, you've seem to have already picked a side in this.",
	stopConversation = "true",
	options = {
	}
}
EmpireDayTK626ConvoTemplate:addScreen(Faction_Deny);

addConversationTemplate("EmpireDayTK626ConvoTemplate", EmpireDayTK626ConvoTemplate);