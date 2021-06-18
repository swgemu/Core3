EmpireDayPeetyJoeConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "EmpireDayPeetyJoe_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Wait...who the freakin' frack are you? What do you want with me and mine?",
	stopConversation = "false",
	options = {
		{"I know you're looking to cause a commotion. We both know you won't get far, best turn back now and we can all go home safely.", "Response_Accepted"},
		{"You're the terrorist! For your crimes against the Empire, I'm taking you in... Dead or alive!" , "Response_Agressive"},
	}
}
EmpireDayPeetyJoeConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Fine. Just don't come after me, ya hear!" ,
	stopConversation = "true",
	options = {
	}
}
EmpireDayPeetyJoeConvoTemplate:addScreen(Response_Accepted)

Response_Agressive = ConvoScreen:new {
	id = "Response_Agressive",
	customDialogText = "Ugh...",
	stopConversation = "true",
	options = {
	}
}
EmpireDayPeetyJoeConvoTemplate:addScreen(Response_Agressive);

Response_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "I get it...I get it! I'm out of here!",
	stopConversation = "true",
	options = {
	}
}
EmpireDayPeetyJoeConvoTemplate:addScreen(Response_Dismiss);

Response_Annoyed = ConvoScreen:new {
	id = "Response_Annoyed",
	customDialogText = "It would be best if you walked away...",
	stopConversation = "true",
	options = {
	}
}
EmpireDayPeetyJoeConvoTemplate:addScreen(Response_Annoyed);

addConversationTemplate("EmpireDayPeetyJoeConvoTemplate", EmpireDayPeetyJoeConvoTemplate);