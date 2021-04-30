AnniversaryAltonFlayConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "AnniversaryAltonFlay_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "What?! Who and why are you here? You are not the famous food critic I have been waiting for.",
	stopConversation = "false",
	options = {
		{"I've Come to reclaim the secret ingredient you stole!", "Response_01"},
		{"Listen, I get that you guys are at odds, but it's just a ingredient, can't you replace it? I need to return it.", "Response_02"},
	}
}
AnniversaryAltonFlayConvoTemplate:addScreen(InitialConvoScreen);

Response_01 = ConvoScreen:new {
	id = "Response_01",
	customDialogText = "Stolen? STOLEN? Snoop Stewart was the one who stole my opportunity to show off my skills! I'll sooner die than give up my only chance to prove I'm the BEST chef!",
	stopConversation = "true",
	options = {
	}
}
AnniversaryAltonFlayConvoTemplate:addScreen(Response_01);

Response_02 = ConvoScreen:new {
	id = "Response_02",
	customDialogText = "Stolen? STOLEN? Snoop Stewart was the one who stole my opportunity to show off my skills! I'll sooner die than give up my only chance to prove I'm the BEST chef!",
	stopConversation = "true",
	options = {
	}
}
AnniversaryAltonFlayConvoTemplate:addScreen(Response_02);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Stolen? STOLEN? Snoop Stewart was the one who stole my opportunity to show off my skills! I'll sooner die than give up my only chance to prove I'm the BEST chef!",
	stopConversation = "true",
	options = {
	}
}
AnniversaryAltonFlayConvoTemplate:addScreen(Response_Accepted);

Responce_Dismiss = ConvoScreen:new {
	id = "Response_Dismiss",
	customDialogText = "Go away, can't you see I'm busy?!",
	stopConversation = "true",
	options = {
	}
}
AnniversaryAltonFlayConvoTemplate:addScreen(Response_Dismiss);

addConversationTemplate("AnniversaryAltonFlayConvoTemplate", AnniversaryAltonFlayConvoTemplate);