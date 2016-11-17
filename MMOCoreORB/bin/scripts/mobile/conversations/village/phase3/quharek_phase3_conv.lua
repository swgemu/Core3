villageQuharekPhase3ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageQuharekPhase3ConvoHandler",
	screens = {}
}

intro_questcompleted_activecrafter = ConvoScreen:new {
	id = "intro_questcompleted_activecrafter",
	leftDialog = "@conversation/quharek_phase_3:s_be53a473", -- Thanks for helping out with the shields. You can still supply more ingredients if you'd like.
	stopConversation = "false",
	options = {
	--{"@conversation/quharek_phase_3:s_955b2ddb", ""}, -- I hear you're looking for crafters.
	--{"@conversation/quharek_phase_3:s_c266e38f", "what_you_want_to_know"}, -- I'd like to get the status of the village shields.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(intro_questcompleted_activecrafter);

intro_questcompleted_notactivecrafter = ConvoScreen:new {
	id = "intro_questcompleted_notactivecrafter",
	leftDialog = "@conversation/quharek_phase_3:s_ed69bd0c", -- Thanks for helping out with the shields.
	stopConversation = "false",
	options = {
	--{"@conversation/quharek_phase_3:s_955b2ddb", ""}, -- I hear you're looking for crafters.
	--{"@conversation/quharek_phase_3:s_c266e38f", "what_you_want_to_know"}, -- I'd like to get the status of the village shields.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(intro_questcompleted_notactivecrafter);

intro_communitycrafting_active = ConvoScreen:new {
	id = "intro_communitycrafting_active",
	leftDialog = "@conversation/quharek_phase_3:s_c1dac897", -- How may I help you?
	stopConversation = "false",
	options = {
	--{"@conversation/quharek_phase_3:s_955b2ddb", ""}, -- I hear you're looking for crafters.
	--{"@conversation/quharek_phase_3:s_c266e38f", "what_you_want_to_know"}, -- I'd like to get the status of the village shields.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(intro_communitycrafting_active);

intro_communitycrafting_inactive = ConvoScreen:new {
	id = "intro_communitycrafting_inactive",
	leftDialog = "@conversation/quharek_phase_3:s_bc2ccc0e", -- There is no crafting project currently being run. Please come back later.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase3ConvoTemplate:addScreen(intro_communitycrafting_inactive);

not_skilled = ConvoScreen:new {
	id = "not_skilled",
	leftDialog = "@conversation/quharek_phase_3:s_ef01f5ee", -- Yes, but I'm afraid you don't have the even the most basic skills needed to help out. Perhaps you should see if someone else needs assistance.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase3ConvoTemplate:addScreen(not_skilled);

max_crafters = ConvoScreen:new {
	id = "max_crafters",
	leftDialog = "@conversation/quharek_phase_3:s_a1a54741", -- I was, but I've got plenty of people helping me at the moment. Perhaps you should see if someone else needs assistance.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase3ConvoTemplate:addScreen(max_crafters);

need_people_to_help = ConvoScreen:new {
	id = "need_people_to_help",
	leftDialog = "@conversation/quharek_phase_3:s_6c81c99f", -- Yes, we need people to help create energy shields for the village. You'll need to contribute at least %DI ingredients to the project. If you do, it will help you gain insight into how the Force can be used to improve your crafting experimentation. We're also giving awards to whoever brings the most or best ingredients. Are you interested?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_99347a8f", "you_should_know"}, -- Yes, I'd like to help out.
		{"@conversation/quharek_phase_3:s_e25e215d", "sorry_you_cant_help"}, -- No, I can't help you.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(need_people_to_help);

sorry_you_cant_help = ConvoScreen:new {
	id = "sorry_you_cant_help",
	leftDialog = "@conversation/quharek_phase_3:s_6f1f7b10", -- I'm sorry you can't help out. May the Force be with you.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase3ConvoTemplate:addScreen(sorry_you_cant_help);

you_should_know = ConvoScreen:new {
	id = "you_should_know",
	leftDialog = "@conversation/quharek_phase_3:s_a9474f4a", -- Ok. You should know that if you help out with the defenses, you won't be able to do any other work here in the village until later. Is that ok?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_4f68f375", "talk_to_qtqc"}, -- That's no problem.
		{"@conversation/quharek_phase_3:s_f9d5461c", "sorry_you_cant_help"}, -- Oh. Maybe I'd better do something else then.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(you_should_know);

talk_to_qtqc = ConvoScreen:new {
	id = "talk_to_qtqc",
	leftDialog = "@conversation/quharek_phase_3:s_e0c642e", -- Excellent! The binary load lifter droid QT-QC has the schematics you'll need for the project. You'll also give it the ingredients you make. You can check the status of the defenses and how well you're contributing to the project at any time. May the Force be with you!
	stopConversation = "true",
	options = {}
}
villageQuharekPhase3ConvoTemplate:addScreen(talk_to_qtqc);

what_you_want_to_know = ConvoScreen:new {
	id = "what_you_want_to_know",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(what_you_want_to_know);

see_attributes = ConvoScreen:new {
	id = "see_attributes",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(see_attributes);

see_ingredient_quality = ConvoScreen:new {
	id = "see_ingredient_quality",
	leftDialog = "@conversation/quharek_phase_3:s_4ccd023a", -- Which ingredient would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_f580c83d", "quality_slot_1"}, -- Endrost Alloy
		{"@conversation/quharek_phase_3:s_b200fa3f", "quality_slot_2"}, -- Shield Housing
		{"@conversation/quharek_phase_3:s_c61bebb1", "quality_slot_3"}, -- Power Supply
		{"@conversation/quharek_phase_3:s_75024256", "quality_slot_4"}, -- Unit Computer
		{"@conversation/quharek_phase_3:s_10aecfa1", "quality_slot_5"}, -- Regulator
		{"@conversation/quharek_phase_3:s_1ccf69c4", "quality_slot_6"}, -- Shield Connections
		{"@conversation/quharek_phase_3:s_e9fef768", "quality_slot_7"}, -- Primary Computer
		{"@conversation/quharek_phase_3:s_a489b2f6", "see_attributes"}, -- The overall project
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(see_ingredient_quality);

quality_slot_1 = ConvoScreen:new {
	id = "quality_slot_1",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quality_slot_1);

quality_slot_2 = ConvoScreen:new {
	id = "quality_slot_2",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quality_slot_2);

quality_slot_3 = ConvoScreen:new {
	id = "quality_slot_3",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quality_slot_3);

quality_slot_4 = ConvoScreen:new {
	id = "quality_slot_4",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quality_slot_4);

quality_slot_5 = ConvoScreen:new {
	id = "quality_slot_5",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quality_slot_5);

quality_slot_6 = ConvoScreen:new {
	id = "quality_slot_6",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quality_slot_6);

quality_slot_7 = ConvoScreen:new {
	id = "quality_slot_7",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quality_slot_7);

see_ingredient_quantity = ConvoScreen:new {
	id = "see_ingredient_quantity",
	leftDialog = "@conversation/quharek_phase_3:s_4ccd023a", -- Which ingredient would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_f580c83d", "quantity_slot_1"}, -- Endrost Alloy
		{"@conversation/quharek_phase_3:s_b200fa3f", "quantity_slot_2"}, -- Shield Housing
		{"@conversation/quharek_phase_3:s_c61bebb1", "quantity_slot_3"}, -- Power Supply
		{"@conversation/quharek_phase_3:s_75024256", "quantity_slot_4"}, -- Unit Computer
		{"@conversation/quharek_phase_3:s_10aecfa1", "quantity_slot_5"}, -- Regulator
		{"@conversation/quharek_phase_3:s_1ccf69c4", "quantity_slot_6"}, -- Shield Connections
		{"@conversation/quharek_phase_3:s_e9fef768", "quantity_slot_7"}, -- Primary Computer
		{"@conversation/quharek_phase_3:s_a489b2f6", "see_attributes"}, -- The overall project
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(see_ingredient_quantity);

quantity_slot_1 = ConvoScreen:new {
	id = "quantity_slot_1",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quantity_slot_1);

quantity_slot_2 = ConvoScreen:new {
	id = "quantity_slot_2",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quantity_slot_2);

quantity_slot_3 = ConvoScreen:new {
	id = "quantity_slot_3",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quantity_slot_3);

quantity_slot_4 = ConvoScreen:new {
	id = "quantity_slot_4",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quantity_slot_4);

quantity_slot_5 = ConvoScreen:new {
	id = "quantity_slot_5",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quantity_slot_5);

quantity_slot_6 = ConvoScreen:new {
	id = "quantity_slot_6",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quantity_slot_6);

quantity_slot_7 = ConvoScreen:new {
	id = "quantity_slot_7",
	leftDialog = "@conversation/quharek_phase_3:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_3:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_3:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_3:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase3ConvoTemplate:addScreen(quantity_slot_7);

addConversationTemplate("villageQuharekPhase3ConvoTemplate", villageQuharekPhase3ConvoTemplate);
