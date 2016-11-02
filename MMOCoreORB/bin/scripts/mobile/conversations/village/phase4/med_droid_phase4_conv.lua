villageMedicalDroidPhase4ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageMedicalDroidPhase4ConvoHandler",
	screens = {}
}

intro_no_quest = ConvoScreen:new {
	id = "intro_no_quest",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_bf4eec78", -- I am sorry, but only authorized medical personnel have access to my functions.
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_sick01:s_67e6df55", "see_sivarra"}, -- Okay.
	}
}
villageMedicalDroidPhase4ConvoTemplate:addScreen(intro_no_quest);

see_sivarra = ConvoScreen:new {
	id = "see_sivarra",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_95a8553f", -- Please talk to Sivarra Mecheaux for inquiries about gaining access.
	stopConversation = "true",
	options = {}
}
villageMedicalDroidPhase4ConvoTemplate:addScreen(see_sivarra);

medical_records = ConvoScreen:new {
	id = "medical_records",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_fa8f35d7", -- Accessing Medical Records... Total Records found with indications you have helped our troops: %TO
	stopConversation = "true",
	options = {}
}
villageMedicalDroidPhase4ConvoTemplate:addScreen(medical_records);

addConversationTemplate("villageMedicalDroidPhase4ConvoTemplate", villageMedicalDroidPhase4ConvoTemplate);