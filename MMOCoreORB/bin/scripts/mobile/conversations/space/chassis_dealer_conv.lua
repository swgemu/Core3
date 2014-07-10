chassis_dealer_convotemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "chassis_dealer_conv_handler",
	screens = {}
}

chassis_dealer_init = ConvoScreen:new {
	id = "init",
	leftDialog = "",
	stopConversation = "false",
	options = {
	}
}

chassis_dealer_convotemplate:addScreen(chassis_dealer_init);

chassis_dealer_buy_chassis = ConvoScreen:new {
	id = "chassis_dealer_buy_chassis",
	leftDialog = "@conversation/chassis_npc:s_bcb592f", -- Let me see if you have any blueprints I can work with...
	stopConversation = "false",
	options = {
	}
}

chassis_dealer_convotemplate:addScreen(chassis_dealer_buy_chassis);

chassis_dealer_no_blueprint = ConvoScreen:new {
	id = "chassis_dealer_no_blueprint",
	leftDialog = "@conversation/chassis_npc:s_37386aa2", -- You need to procure a set of chassis blueprints from a Shipwright. Once you have the blueprints, you must come to a chassis dealer to have the chassis built to your specifications.
	stopConversation = "true",
	options = {
	}
}

chassis_dealer_convotemplate:addScreen(chassis_dealer_no_blueprint);

addConversationTemplate("chassis_dealer_convotemplate", chassis_dealer_convotemplate);
