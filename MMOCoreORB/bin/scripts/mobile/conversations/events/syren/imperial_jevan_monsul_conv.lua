imperialJevanMonsulConvoTemplate = ConvoTemplate:new {
	initialScreen = "s_228",
	templateType = "Lua",
	luaClassHandler = "imperialJevanMonsulConvoHandler",
	screens = {}
}

s_228 = ConvoScreen:new {
	id = "s_228",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_228", -- Greetings, soldier.  I have a situation that requires my attention and I cannot attend to it properly.  Would you be willing to help me out?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_163", "s_165"} -- Perhaps, if I have more information.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(s_228);

s_165 = ConvoScreen:new {
	id = "s_165",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_165", -- I have just gotten word that a pilot is missing. We have the coordinates of his last known location. It was on Rori. Would you be willing to run out there and see what happened?  He may be hurt or in danger.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_imp_quest:s_167", "s_169"} -- I will go investigate.
	}
}

imperialJevanMonsulConvoTemplate:addScreen(s_165);

s_169 = ConvoScreen:new {
	id = "s_169",
	leftDialog = "@conversation/c_story1_1_imp_quest:s_169", -- Very good.  Go to these coordinates on Rori and see if you can find anything out. Then report back to me. Oh, if he had cargo, maybe you could find out what happened to it.  That would probably help him out a lot.
	stopConversation = "true",
	options = {}
}

imperialJevanMonsulConvoTemplate:addScreen(s_169);

addConversationTemplate("imperialJevanMonsulConvoTemplate", imperialJevanMonsulConvoTemplate);
