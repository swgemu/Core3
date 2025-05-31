tutorialRoomOneGreeterConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialRoomOneGreeterConvoHandler",
	screens = {}
}

greeter1_bark1 = ConvoScreen:new {
	id = "greeter1_bark1",
	leftDialog = "@newbie_tutorial/newbie_convo:greeter1_bark1", -- Ah, I see we have another refugee from the freighter.
	stopConversation = "true",
	options = {
	}
}
tutorialRoomOneGreeterConvoTemplate:addScreen(greeter1_bark1);

greeter1_bark2 = ConvoScreen:new {
	id = "greeter1_bark2",
	leftDialog = "@newbie_tutorial/newbie_convo:greeter1_bark2", -- Well, you're one of the lucky ones. Most of the passengers didn't survive.
	stopConversation = "true",
	options = {
	}
}
tutorialRoomOneGreeterConvoTemplate:addScreen(greeter1_bark2);

greeter1_bark3 = ConvoScreen:new {
	id = "greeter1_bark3",
	leftDialog = "@newbie_tutorial/newbie_convo:greeter1_bark3", -- You should know better than to take passage with criminals.
	stopConversation = "true",
	options = {
	}
}
tutorialRoomOneGreeterConvoTemplate:addScreen(greeter1_bark3);

addConversationTemplate("tutorialRoomOneGreeterConvoTemplate", tutorialRoomOneGreeterConvoTemplate);
