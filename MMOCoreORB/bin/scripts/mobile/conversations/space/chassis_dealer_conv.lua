chassis_dealer_convotemplate = ConvoTemplate:new {
	initialScreen = "chassis_dealer_greeting",
	templateType = "Lua",
	luaClassHandler = "chassis_dealer_conv_handler",
	screens = {}
}

chassis_dealer_greeting = ConvoScreen:new {
	id = "chassis_dealer_greeting",
	leftDialog = "@conversation/chassis_npc:s_9ed93871",
	stopConversation = "false",
	options = {
		{"@conversation/chassis_npc:s_2f553ea8", "chassis_dealer_buy_chassis"},
		{"@conversation/chassis_npc:s_94e3013f", "chassis_dealer_sell_components"},
		{"@conversation/chassis_npc:s_93a92e8", "chassis_dealer_how_do_i"},
		{"@conversation/chassis_npc:s_42d3759c", "chassis_dealer_come_back_later"},
	}
}

chassis_dealer_convotemplate:addScreen(chassis_dealer_greeting);

chassis_dealer_buy_chassis = ConvoScreen:new {
	id = "chassis_dealer_buy_chassis",
	leftDialog = "@conversation/chassis_npc:s_bcb592f",
	stopConversation = "true",
	options = {
	}
}

chassis_dealer_convotemplate:addScreen(chassis_dealer_buy_chassis);

chassis_dealer_sell_components = ConvoScreen:new {
	id = "chassis_dealer_sell_components",
	leftDialog = "@conversation/chassis_npc:s_aae81853",
	stopConversation = "true",
	options = {
	}
}

chassis_dealer_convotemplate:addScreen(chassis_dealer_sell_components);

chassis_dealer_how_do_i = ConvoScreen:new {
	id = "chassis_dealer_how_do_i",
	leftDialog = "@conversation/chassis_npc:s_37386aa2", -- You need to procure a set of chassis blueprints from a Shipwright. Once you have the blueprints, you must come to a chassis dealer to have the chassis built to your specifications.
	stopConversation = "true",
	options = {
	}
}

chassis_dealer_convotemplate:addScreen(chassis_dealer_how_do_i);

chassis_dealer_come_back_later = ConvoScreen:new {
	id = "chassis_dealer_come_back_later",
	leftDialog = "@conversation/chassis_npc:s_37f48153",
	stopConversation = "true",
	options = {
	}
}

chassis_dealer_convotemplate:addScreen(chassis_dealer_come_back_later);

addConversationTemplate("chassis_dealer_convotemplate", chassis_dealer_convotemplate);
