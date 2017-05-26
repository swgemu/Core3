corvetteNeutralPrisonerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvettePrisonerConvoHandler",
	screens = {}
}

not_rescued = ConvoScreen:new {
	id = "not_rescued",
	leftDialog = "@conversation/corvette_neutral_prisoner_02:s_941cfab3", -- About time you showed up. For a second I thought that slug coundn't have cared less if I was going to prison or not. Oh you're not here for me?! This is not the last Jabba has heard of me.
	stopConversation = "true",
	options = {}
}
corvetteNeutralPrisonerConvoTemplate:addScreen(not_rescued);

rescued = ConvoScreen:new {
	id = "rescued",
	leftDialog = "@conversation/corvette_neutral_prisoner_02:s_169c1160", -- 	I'm getting off this ship, and when I do, don't go sayin' anything to Jabba. I aim to talk to him myself.
	stopConversation = "true",
	options = {}
}
corvetteNeutralPrisonerConvoTemplate:addScreen(rescued);

addConversationTemplate("corvetteNeutralPrisonerConvoTemplate", corvetteNeutralPrisonerConvoTemplate);
