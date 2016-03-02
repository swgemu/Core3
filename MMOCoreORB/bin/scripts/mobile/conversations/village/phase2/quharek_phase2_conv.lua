villageQuharekPhase2ConvoTemplate = ConvoTemplate:new {
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
villageQuharekPhase2ConvoTemplate:addScreen(intro_wrongplayer);