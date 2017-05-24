corvetteImperialPrisonerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvettePrisonerConvoHandler",
	screens = {}
}

not_rescued = ConvoScreen:new {
	id = "not_rescued",
	leftDialog = "@conversation/corvette_imperial_prisoner_02:s_9b0874b1", --Good work soldiers! Knew I could count on the Empire's finest to get me out of here.
	stopConversation = "true",
	options = {}
}
corvetteImperialPrisonerConvoTemplate:addScreen(not_rescued);

rescued = ConvoScreen:new {
	id = "rescued",
	leftDialog = "@conversation/corvette_imperial_prisoner_02:s_a8dab33a", --Time to get off this ship. Thanks again!
	stopConversation = "true",
	options = {}
}
corvetteImperialPrisonerConvoTemplate:addScreen(rescued);

addConversationTemplate("corvetteImperialPrisonerConvoTemplate", corvetteImperialPrisonerConvoTemplate);
