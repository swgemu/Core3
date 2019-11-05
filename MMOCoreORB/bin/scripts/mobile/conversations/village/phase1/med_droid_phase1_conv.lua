villageMedicalDroidPhase1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageMedicalDroidPhase1ConvoHandler",
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
villageMedicalDroidPhase1ConvoTemplate:addScreen(intro_no_quest);

see_sivarra = ConvoScreen:new {
	id = "see_sivarra",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_95a8553f", -- Please talk to Sivarra Mecheaux for inquiries about gaining access.
	stopConversation = "true",
	options = {}
}
villageMedicalDroidPhase1ConvoTemplate:addScreen(see_sivarra);

intro_has_symptoms = ConvoScreen:new {
	id = "intro_has_symptoms",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_3904c58", -- This patient is currently suffering from %TO. If you have any treatments you would like to administer to him, please give the treatment to me so I can administer them.
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_sick01:s_67e6df55", "thank_you"}, -- Okay.
	}
}
villageMedicalDroidPhase1ConvoTemplate:addScreen(intro_has_symptoms);

thank_you = ConvoScreen:new {
	id = "thank_you",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_b9b27823", -- Thank you.
	stopConversation = "true",
	options = {}
}
villageMedicalDroidPhase1ConvoTemplate:addScreen(thank_you);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_95bc25f3", -- Greetings, I am the 2-1B Medical droid in charge of this patient. How may I assist you?
	stopConversation = "false",
	options = {
		{"@conversation/fs_medic_puzzle_sick01:s_12ec68a8", "currently_suffering_from"}, -- What is wrong with this patient?
		{"@conversation/fs_medic_puzzle_sick01:s_67e6df55", "pleasure_to_assist"}, -- Never mind, I'm looking for another patient.
	}
}
villageMedicalDroidPhase1ConvoTemplate:addScreen(intro);

currently_suffering_from = ConvoScreen:new {
	id = "currently_suffering_from",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_3904c58", -- This patient is currently suffering from %TO. If you have any treatments you would like to administer to him, please give the treatment to me so I can administer them.
	stopConversation = "true",
	options = {}
}
villageMedicalDroidPhase1ConvoTemplate:addScreen(currently_suffering_from);

pleasure_to_assist = ConvoScreen:new {
	id = "pleasure_to_assist",
	leftDialog = "@conversation/fs_medic_puzzle_sick01:s_1d567ce1", -- Always a pleasure to assist. Please let me know if there is anything else I can assist with.
	stopConversation = "true",
	options = {}
}
villageMedicalDroidPhase1ConvoTemplate:addScreen(pleasure_to_assist);

addConversationTemplate("villageMedicalDroidPhase1ConvoTemplate", villageMedicalDroidPhase1ConvoTemplate);