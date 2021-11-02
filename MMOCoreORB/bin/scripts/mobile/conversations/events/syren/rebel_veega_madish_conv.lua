rebelVeegaMadishConvoTemplate = ConvoTemplate:new {
	initialScreen = "s_161",
	templateType = "Lua",
	luaClassHandler = "rebelVeegaMadishConvoHandler",
	screens = {}
}

s_161 = ConvoScreen:new {
	id = "s_161",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_161", -- I need your help!  I have a situation that requires my attention and I cannot attend to it properly.  Would you be willing to help me out?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_reb_quest:s_163", "s_165"} -- Perhaps, if I have more information.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(s_161);

s_165 = ConvoScreen:new {
	id = "s_165",
	leftDialog = "@conversation/c_story1_1_reb_quest:s_165", -- I have just gotten word that a pilot is missing. We have the coordinates of his last known location. It was on Rori. Would you be willing to run out there and see what happened?  He may be hurt or in danger.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:s_167", "s_169"} -- I will go investigate.
	}
}

rebelVeegaMadishConvoTemplate:addScreen(s_165);

s_169 = ConvoScreen:new {
	id = "s_169",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:s_169", -- Very good.  Go to these coordinates on Rori and see if you can find anything out. Then report back to me. Oh, if he had cargo, maybe you could find out what happened to it.  That would probably help him out a lot.
	stopConversation = "true",
	options = {}
}

rebelVeegaMadishConvoTemplate:addScreen(s_169);

addConversationTemplate("rebelVeegaMadishConvoTemplate", rebelVeegaMadishConvoTemplate);
