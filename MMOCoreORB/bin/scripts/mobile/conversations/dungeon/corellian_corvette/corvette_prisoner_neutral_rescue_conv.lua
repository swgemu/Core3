corvetteNeutralPrisonerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvettePrisonerConvoHandler",
	screens = {}
}

not_rescued = ConvoScreen:new {
	id = "not_rescued",
	leftDialog = "@conversation/corvette_neutral_prisoner_02:s_940601d4", --Phew, I thought Jabba was going to leave me to rot. I owe ye one mate!
	stopConversation = "true",
	options = {}
}
corvetteNeutralPrisonerConvoTemplate:addScreen(not_rescued);

rescued = ConvoScreen:new {
	id = "rescued",
	leftDialog = "@conversation/corvette_neutral_prisoner_02:s_fa08a772", --Later mate... I'm getting off this ship.
	stopConversation = "true",
	options = {}
}
corvetteNeutralPrisonerConvoTemplate:addScreen(rescued);

addConversationTemplate("corvetteNeutralPrisonerConvoTemplate", corvetteNeutralPrisonerConvoTemplate);
