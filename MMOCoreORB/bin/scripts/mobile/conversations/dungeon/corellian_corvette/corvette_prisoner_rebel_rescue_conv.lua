corvetteRebelPrisonerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvettePrisonerConvoHandler",
	screens = {}
}

not_rescued = ConvoScreen:new {
	id = "not_rescued",
	leftDialog = "@conversation/corvette_rebel_prisoner_02:s_fc440e0b", --Am I glad to see you! I hear the Dathomir prison is worse than death.
	stopConversation = "true",
	options = {}
}
corvetteRebelPrisonerConvoTemplate:addScreen(not_rescued);

rescued = ConvoScreen:new {
	id = "rescued",
	leftDialog = "@conversation/corvette_rebel_prisoner_02:s_ecc17e1	", --I can't wait to get back onto Corellian soil! Thank you!
	stopConversation = "true",
	options = {}
}
corvetteRebelPrisonerConvoTemplate:addScreen(rescued);

addConversationTemplate("corvetteRebelPrisonerConvoTemplate", corvetteRebelPrisonerConvoTemplate);
