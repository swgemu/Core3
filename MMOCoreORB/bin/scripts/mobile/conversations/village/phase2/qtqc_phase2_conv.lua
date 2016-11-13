villageQtQcPhase2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageQtQcPhase2ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/qtqc_phase_2:s_67afc98f", -- What would you like to do?
	stopConversation = "false",
	options = {
	--{"@conversation/qtqc_phase_2:s_3a6af75d", ""}, -- I need the schematics for the village defenses.
	--{"@conversation/qtqc_phase_2:s_20141151", "explain_resources"}, -- Tell me about these special resources again.
	--{"@conversation/qtqc_phase_2:s_ebcb651f", "put_in_inventory"}, -- I'd like to add an ingredient to the village defenses.
	--{"@conversation/qtqc_phase_2:s_2ce1f012", ""}, -- How many more items do I need to contribute?
	--{"@conversation/qtqc_phase_2:s_baf57f52", "what_you_want_to_know"}, -- I'd like to get the status of the village defenses.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(intro);

intro_communitycrafting_inactive = ConvoScreen:new {
	id = "intro_communitycrafting_inactive",
	leftDialog = "@conversation/qtqc_phase_2:s_bc2ccc0e", -- There is no crafting project currently being run. Please come back later.
	stopConversation = "true",
	options = {}
}
villageQtQcPhase2ConvoTemplate:addScreen(intro_communitycrafting_inactive);

schematics_given = ConvoScreen:new {
	id = "schematics_given",
	leftDialog = "@conversation/qtqc_phase_2:s_6ef148af", -- You have been given the schematics needed for the project. They can be accessed via the 'mission/community crafting' categories of your crafting tool.  When you have an ingredient ready, see me to add it to the project.
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_adcf90d8", "explain_resources"}, -- I don't recognize the resources needed by the schematics.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(schematics_given);

explain_resources = ConvoScreen:new {
	id = "explain_resources",
	leftDialog = "@conversation/qtqc_phase_2:s_cdaf165d", -- There are people who are working for Eozlin who are gathering special resources. You must get the resources from them to craft the items needed for the defenses. There are also reports that the Sith Shadows are using them to build their bases.
	stopConversation = "true",
	options = {}
}
villageQtQcPhase2ConvoTemplate:addScreen(explain_resources);

put_in_inventory = ConvoScreen:new {
	id = "put_in_inventory",
	leftDialog = "@conversation/qtqc_phase_2:s_739cd87c", -- Please put the ingredients you want to add into my inventory.
	stopConversation = "true",
	options = {}
}
villageQtQcPhase2ConvoTemplate:addScreen(put_in_inventory);

needs_one_item = ConvoScreen:new {
	id = "needs_one_item",
	leftDialog = "@conversation/qtqc_phase_2:s_9750fd54", -- You need to give one more item.
	stopConversation = "true",
	options = {}
}
villageQtQcPhase2ConvoTemplate:addScreen(needs_one_item);

needs_multiple_items = ConvoScreen:new {
	id = "needs_multiple_items",
	leftDialog = "@conversation/qtqc_phase_2:s_bf623b9", -- You need to give %DI more items.
	stopConversation = "true",
	options = {}
}
villageQtQcPhase2ConvoTemplate:addScreen(needs_multiple_items);

needs_no_items = ConvoScreen:new {
	id = "needs_no_items",
	leftDialog = "@conversation/qtqc_phase_2:s_74be10c7", -- You don't need to give any more items, although you can to help the project.
	stopConversation = "true",
	options = {}
}
villageQtQcPhase2ConvoTemplate:addScreen(needs_no_items);

what_you_want_to_know = ConvoScreen:new {
	id = "what_you_want_to_know",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(what_you_want_to_know);

see_attributes = ConvoScreen:new {
	id = "see_attributes",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(see_attributes);

see_ingredient_quality = ConvoScreen:new {
	id = "see_ingredient_quality",
	leftDialog = "@conversation/qtqc_phase_2:s_4ccd023a", -- Which ingredient would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_2a94bc85", "quality_slot_1"}, -- Refined Endrine
		{"@conversation/qtqc_phase_2:s_ca02afa6", "quality_slot_2"}, -- Refined Rudic
		{"@conversation/qtqc_phase_2:s_87a5e151", "quality_slot_3"}, -- Refined Ardanium II
		{"@conversation/qtqc_phase_2:s_36cd5966", "quality_slot_4"}, -- Reinforced Wall Module
		{"@conversation/qtqc_phase_2:s_574683dc", "quality_slot_5"}, -- Small Turret
		{"@conversation/qtqc_phase_2:s_a489b2f6", "see_attributes"}, -- The overall project
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(see_ingredient_quality);

quality_slot_1 = ConvoScreen:new {
	id = "quality_slot_1",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quality_slot_1);

quality_slot_2 = ConvoScreen:new {
	id = "quality_slot_2",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quality_slot_2);

quality_slot_3 = ConvoScreen:new {
	id = "quality_slot_3",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quality_slot_3);

quality_slot_4 = ConvoScreen:new {
	id = "quality_slot_4",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quality_slot_4);

quality_slot_5 = ConvoScreen:new {
	id = "quality_slot_5",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quality_slot_5);

see_ingredient_quantity = ConvoScreen:new {
	id = "see_ingredient_quantity",
	leftDialog = "@conversation/qtqc_phase_2:s_4ccd023a", -- Which ingredient would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_2a94bc85", "quantity_slot_1"}, -- Refined Endrine
		{"@conversation/qtqc_phase_2:s_ca02afa6", "quantity_slot_2"}, -- Refined Rudic
		{"@conversation/qtqc_phase_2:s_87a5e151", "quantity_slot_3"}, -- Refined Ardanium II
		{"@conversation/qtqc_phase_2:s_36cd5966", "quantity_slot_4"}, -- Reinforced Wall Module
		{"@conversation/qtqc_phase_2:s_574683dc", "quantity_slot_5"}, -- Small Turret
		{"@conversation/qtqc_phase_2:s_a489b2f6", "see_attributes"}, -- The overall project
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(see_ingredient_quantity);

quantity_slot_1 = ConvoScreen:new {
	id = "quantity_slot_1",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quantity_slot_1);

quantity_slot_2 = ConvoScreen:new {
	id = "quantity_slot_2",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quantity_slot_2);

quantity_slot_3 = ConvoScreen:new {
	id = "quantity_slot_3",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quantity_slot_3);

quantity_slot_4 = ConvoScreen:new {
	id = "quantity_slot_4",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quantity_slot_4);

quantity_slot_5 = ConvoScreen:new {
	id = "quantity_slot_5",
	leftDialog = "@conversation/qtqc_phase_2:s_261bbc0d", -- What would you like to know about?
	stopConversation = "false",
	options = {
		{"@conversation/qtqc_phase_2:s_ff02a401", "see_attributes"}, -- I'd like to see the project's current attributes.
		{"@conversation/qtqc_phase_2:s_39019ea3", "see_ingredient_quality"}, -- I'd like to know about the quality of the ingredients people are giving.
		{"@conversation/qtqc_phase_2:s_c57c793", "see_ingredient_quantity"}, -- I'd like to know about the amount of ingredients people are giving.
	}
}
villageQtQcPhase2ConvoTemplate:addScreen(quantity_slot_5);

addConversationTemplate("villageQtQcPhase2ConvoTemplate", villageQtQcPhase2ConvoTemplate);
