villageQuharekPhase2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageQuharekPhase2ConvoHandler",
	screens = {}
}

intro_questcompleted_activecrafter = ConvoScreen:new {
	id = "intro_questcompleted_activecrafter",
	leftDialog = "@conversation/quharek_phase_2:s_da07ca0e", -- Thanks for helping out with the defenses. You can still supply more ingredients if you'd like.
	stopConversation = "false",
	options = {
	--{"@conversation/quharek_phase_2:s_955b2ddb", ""}, -- I hear you're looking for crafters.
	--{"@conversation/quharek_phase_2:s_955b2ddb", "what_you_want_to_know"}, -- I'd like to get the status of the village defenses.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(intro_questcompleted_activecrafter);

intro_questcompleted_notactivecrafter = ConvoScreen:new {
	id = "intro_questcompleted_notactivecrafter",
	leftDialog = "@conversation/quharek_phase_2:s_15c7f70f", -- Thanks for helping out with the defenses.
	stopConversation = "false",
	options = {
	--{"@conversation/quharek_phase_2:s_955b2ddb", ""}, -- I hear you're looking for crafters.
	--{"@conversation/quharek_phase_2:s_955b2ddb", "what_you_want_to_know"}, -- I'd like to get the status of the village defenses.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(intro_questcompleted_notactivecrafter);

intro_communitycrafting_active = ConvoScreen:new {
	id = "intro_communitycrafting_active",
	leftDialog = "@conversation/quharek_phase_2:s_c1dac897", -- How may I help you?
	stopConversation = "false",
	options = {
	--{"@conversation/quharek_phase_2:s_955b2ddb", ""}, -- I hear you're looking for crafters.
	--{"@conversation/quharek_phase_2:s_955b2ddb", "what_you_want_to_know"}, -- I'd like to get the status of the village defenses.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(intro_communitycrafting_active);

intro_communitycrafting_inactive = ConvoScreen:new {
	id = "intro_communitycrafting_inactive",
	leftDialog = "@conversation/quharek_phase_2:s_bc2ccc0e", -- There is no crafting project currently being run. Please come back later.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase2ConvoTemplate:addScreen(intro_communitycrafting_inactive);

not_skilled = ConvoScreen:new {
	id = "not_skilled",
	leftDialog = "@conversation/quharek_phase_2:s_ef01f5ee", -- Yes, but I'm afraid you don't have the even the most basic skills needed to help out. Perhaps you should see if someone else needs assistance.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase2ConvoTemplate:addScreen(not_skilled);

max_crafters = ConvoScreen:new {
	id = "max_crafters",
	leftDialog = "@conversation/quharek_phase_2:s_a1a54741", -- I was, but I've got plenty of people helping me at the moment. Perhaps you should see if someone else needs assistance.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase2ConvoTemplate:addScreen(max_crafters);

need_people_to_help = ConvoScreen:new {
	id = "need_people_to_help",
	leftDialog = "@conversation/quharek_phase_2:s_cf89ace1", -- Yes, we need people to help create defenses for the village. You'll need to contribute at least %DI ingredients to the project. If you do, it will help you gain insight into how the Force can be used to improve your crafting technique. We're also giving awards to whoever brings the most or best ingredients. Are you interested?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_99347a8f", "you_should_know"}, -- Yes, I'd like to help out.
		{"@conversation/quharek_phase_2:s_e25e215d", "sorry_you_cant_help"}, -- No, I can't help you.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(need_people_to_help);

sorry_you_cant_help = ConvoScreen:new {
	id = "sorry_you_cant_help",
	leftDialog = "@conversation/quharek_phase_2:s_6f1f7b10", -- I'm sorry you can't help out. May the Force be with you.
	stopConversation = "true",
	options = {}
}
villageQuharekPhase2ConvoTemplate:addScreen(sorry_you_cant_help);

you_should_know = ConvoScreen:new {
	id = "you_should_know",
	leftDialog = "@conversation/quharek_phase_2:s_a9474f4a", -- You should know that if you help out with the defenses, you won't be able to do any other work here in the village until later. Is that ok?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_4f68f375", "talk_to_qtqc"}, -- That's no problem.
		{"@conversation/quharek_phase_2:s_f9d5461c", "sorry_you_cant_help"}, -- Oh. Maybe I'd better do something else then.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(you_should_know);

talk_to_qtqc = ConvoScreen:new {
	id = "talk_to_qtqc",
	leftDialog = "@conversation/quharek_phase_2:s_e0c642e", -- Excellent! The binary load lifter droid QT-QC has the schematics you'll need for the project. You'll also give it the ingredients you make. You can check the status of the defenses and how well you're contributing to the project at any time. May the Force be with you!
	stopConversation = "true",
	options = {}
}
villageQuharekPhase2ConvoTemplate:addScreen(talk_to_qtqc);

what_you_want_to_know = ConvoScreen:new {
	id = "what_you_want_to_know",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(what_you_want_to_know);

see_attributes = ConvoScreen:new {
	id = "see_attributes",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(see_attributes);

see_ingredient_quality = ConvoScreen:new {
	id = "see_ingredient_quality",
	leftDialog = "@conversation/quharek_phase_2:s_4ccd023a", -- Which ingredient would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_2a94bc85", "quality_slot_1"}, -- Refined Endrine
		{"@conversation/quharek_phase_2:s_ca02afa6", "quality_slot_2"}, -- Refined Rudic
		{"@conversation/quharek_phase_2:s_87a5e151", "quality_slot_3"}, -- Refined Ardanium II
		{"@conversation/quharek_phase_2:s_36cd5966", "quality_slot_4"}, -- Reinforced Wall Module
		{"@conversation/quharek_phase_2:s_574683dc", "quality_slot_5"}, -- Small Turret
		{"@conversation/quharek_phase_2:s_a489b2f6", "see_attributes"}, -- The overall project
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(see_ingredient_quality);

quality_slot_1 = ConvoScreen:new {
	id = "quality_slot_1",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quality_slot_1);

quality_slot_2 = ConvoScreen:new {
	id = "quality_slot_2",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quality_slot_2);

quality_slot_3 = ConvoScreen:new {
	id = "quality_slot_3",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quality_slot_3);

quality_slot_4 = ConvoScreen:new {
	id = "quality_slot_4",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quality_slot_4);

quality_slot_5 = ConvoScreen:new {
	id = "quality_slot_5",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quality_slot_5);

see_ingredient_quantity = ConvoScreen:new {
	id = "see_ingredient_quantity",
	leftDialog = "@conversation/quharek_phase_2:s_4ccd023a", -- Which ingredient would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_2a94bc85", "quantity_slot_1"}, -- Refined Endrine
		{"@conversation/quharek_phase_2:s_ca02afa6", "quantity_slot_2"}, -- Refined Rudic
		{"@conversation/quharek_phase_2:s_87a5e151", "quantity_slot_3"}, -- Refined Ardanium II
		{"@conversation/quharek_phase_2:s_36cd5966", "quantity_slot_4"}, -- Reinforced Wall Module
		{"@conversation/quharek_phase_2:s_574683dc", "quantity_slot_5"}, -- Small Turret
		{"@conversation/quharek_phase_2:s_a489b2f6", "see_attributes"}, -- The overall project
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(see_ingredient_quantity);

quantity_slot_1 = ConvoScreen:new {
	id = "quantity_slot_1",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quantity_slot_1);

quantity_slot_2 = ConvoScreen:new {
	id = "quantity_slot_2",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quantity_slot_2);

quantity_slot_3 = ConvoScreen:new {
	id = "quantity_slot_3",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quantity_slot_3);

quantity_slot_4 = ConvoScreen:new {
	id = "quantity_slot_4",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quantity_slot_4);

quantity_slot_5 = ConvoScreen:new {
	id = "quantity_slot_5",
	leftDialog = "@conversation/quharek_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/quharek_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/quharek_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/quharek_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQuharekPhase2ConvoTemplate:addScreen(quantity_slot_5);

addConversationTemplate("villageQuharekPhase2ConvoTemplate", villageQuharekPhase2ConvoTemplate);