AnniversarySnoopStewartConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "AnniversarySnoopStewart_convo_handler",
	screens = {}
}

InitialConvoScreen = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Hello. Can you help me? While I had my back turned, a thief slipped into my kitchen to steal my secret ingredient! Without this, all is lost, I implore you, if you can help me recover my secret ingredient, I'll let you sample my greatest culinary creation ever made!",
	stopConversation = "false",
	options = {
		{"This better be worth it, I don't have all day to chase down your special sauce.", "Response_Accepted"},
		{"Sounds deliciously spectacular! Count me in.", "Response_Accepted"},
		{"Not my circus, not my problem.", "Response_01"},
	}
}
AnniversarySnoopStewartConvoTemplate:addScreen(InitialConvoScreen);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Oh thank you, thank you, thank you! Your tastebuds won't regret it! I know a man who might be able to give you a lead, hand him this datachip.",
	stopConversation = "true",
	options = {
	}
}
AnniversarySnoopStewartConvoTemplate:addScreen(Response_Accepted);

Response_01 = ConvoScreen:new {
	id = "Response_01",
	customDialogText = "How will I ever be able to finish?",
	stopConversation = "true",
	options = {
	}
}
AnniversarySnoopStewartConvoTemplate:addScreen(Response_01);

TurnInConvoScreen = ConvoScreen:new {
	id = "TurnInConvo",
	customDialogText = "Have you recovered my super special secret ingredient yet?",
	stopConversation = "false",
	options = {
		{"It's this thing right? Are you sure this is ediable?", "TurnInResponse_Accepted"},
		{"Here is your 'super special secret ingredient' you were asking about.", "TurnInResponse_Accepted"},
	}
}
AnniversarySnoopStewartConvoTemplate:addScreen(TurnInConvoScreen);

TurnInResponse_Accepted = ConvoScreen:new {
	id = "TurnInResponse_Accepted",
	customDialogText = "Thank you oh so much, traveller! This will most certainly be worthy of being the best across the galaxy. As promised, here is your reward. You've more than earned it.",
	stopConversation = "true",
	options = {
	}
}
AnniversarySnoopStewartConvoTemplate:addScreen(TurnInResponse_Accepted);

Service_Noted = ConvoScreen:new {
	id = "Service_Noted",
	customDialogText = "Thank you again, I am submitting this at Theed's next Festival of Life. I couldn't have done it without you.",
	stopConversation = "true",
	options = {
	}
}
AnniversarySnoopStewartConvoTemplate:addScreen(Service_Noted);

Time_Wasted = ConvoScreen:new {
	id = "Time_Wasted",
	customDialogText = "Have you found it yet? The whole plate will be ruined unless we find that soon.",
	stopConversation = "true",
	options = {
	}
}
AnniversarySnoopStewartConvoTemplate:addScreen(Time_Wasted);

addConversationTemplate("AnniversarySnoopStewartConvoTemplate", AnniversarySnoopStewartConvoTemplate);