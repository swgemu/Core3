rebelSympathizerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rebelSympathizerConvoHandler",
	screens = {}
}

m1_sympathizer_invalid = ConvoScreen:new {
	id = "m1_sympathizer_invalid",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_sympathizer_invalid", -- I'm sorry, I can't chat right now. I'm waiting for a friend to arrive.
	stopConversation = "true",
	options = {}
}

rebelSympathizerConvoTemplate:addScreen(m1_sympathizer_invalid);

m1_sympathizer_greeting = ConvoScreen:new {
	id = "m1_sympathizer_greeting",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_sympathizer_greeting", -- You're from the Alliance? Oh good. Lyda... I mean, Skimmer, told me that someone from the Alliance might try to contact me. She gave me this disk in case something happened to her but it's encoded. She said the Alliance would be able to crack it.
	stopConversation = "true",
	options = {}
}

rebelSympathizerConvoTemplate:addScreen(m1_sympathizer_greeting);

m1_sympathizer_complete = ConvoScreen:new {
	id = "m1_sympathizer_complete",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_sympathizer_complete", -- What are you waiting for. You need to get that disk to the Alliance.
	stopConversation = "true",
	options = {}
}

rebelSympathizerConvoTemplate:addScreen(m1_sympathizer_complete);

addConversationTemplate("rebelSympathizerConvoTemplate", rebelSympathizerConvoTemplate);
