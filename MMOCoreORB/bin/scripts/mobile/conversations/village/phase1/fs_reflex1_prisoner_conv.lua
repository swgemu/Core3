villageFsReflex1PrisonerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageFsReflex1PrisonerConvoHandler",
	screens = {}
}

intro_wrongplayer = ConvoScreen:new {
	id = "intro_wrongplayer",
	leftDialog = "@conversation/fs_reflex1_prisoner:s_e4480cdc", -- I don't think that you're able to help me.
	stopConversation = "true",
	options = {}
}
villageFsReflex1PrisonerConvoTemplate:addScreen(intro_wrongplayer);

intro_rescued = ConvoScreen:new {
	id = "intro_rescued",
	leftDialog = "@conversation/fs_reflex1_prisoner:s_1150de7c", -- Thank you so much for rescuing me!
	stopConversation = "true",
	options = {}
}
villageFsReflex1PrisonerConvoTemplate:addScreen(intro_rescued);

intro_inprogress = ConvoScreen:new {
	id = "intro_inprogress",
	leftDialog = "@conversation/fs_reflex1_prisoner:s_e9ddb716", -- Let's hurry up and get back to the village!
	stopConversation = "true",
	options = {}
}
villageFsReflex1PrisonerConvoTemplate:addScreen(intro_inprogress);

intro_failedquest = ConvoScreen:new {
	id = "intro_failedquest",
	leftDialog = "@conversation/fs_reflex1_prisoner:s_780bc309", -- I don't think that you're able to help me anymore.
	stopConversation = "true",
	options = {}
}
villageFsReflex1PrisonerConvoTemplate:addScreen(intro_failedquest);

intro_incombat = ConvoScreen:new {
	id = "intro_incombat",
	leftDialog = "@conversation/fs_reflex1_prisoner:s_f77ac89f", -- Not now! Give me a hand here!
	stopConversation = "true",
	options = {}
}
villageFsReflex1PrisonerConvoTemplate:addScreen(intro_incombat);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_reflex1_prisoner:s_2a6f5720", -- Thank you so much for coming after me. Let's get out of here!
	stopConversation = "true",
	options = {}
}
villageFsReflex1PrisonerConvoTemplate:addScreen(intro);

addConversationTemplate("villageFsReflex1PrisonerConvoTemplate", villageFsReflex1PrisonerConvoTemplate);