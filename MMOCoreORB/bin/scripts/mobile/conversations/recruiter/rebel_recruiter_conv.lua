rebel_recruiter_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rebel_recruiter_handler",
	screens = {}
}

--greet_hated
rebel_recruiter_greet_hated = ConvoScreen:new {
	id = "greet_hated",
	leftDialog = "@conversation/faction_recruiter_rebel:s_462",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_greet_hated);


--greet_changing_status
rebel_recruiter_greet_changing_status = ConvoScreen:new {
	id = "greet_changing_status",
	leftDialog = "@conversation/faction_recruiter_rebel:s_596",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_greet_changing_status);


--greet_enemy
rebel_recruiter_greet_enemy = ConvoScreen:new {
	id = "greet_enemy",
	leftDialog = "@conversation/faction_recruiter_rebel:s_464",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_greet_enemy);


--member start
rebel_recruiter_member_covert_start = ConvoScreen:new {
	id = "greet_member_start_covert",
	leftDialog = "@conversation/faction_recruiter_rebel:s_466",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_504", "confirm_go_overt"},
		{"@conversation/faction_recruiter_rebel:s_526", "leave_time_covert"},
		{"@conversation/faction_recruiter_rebel:s_538", "resign_covert"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_member_covert_start);


rebel_recruiter_member_overt_start = ConvoScreen:new {
id = "greet_member_start_overt",
	leftDialog = "@conversation/faction_recruiter_rebel:s_466",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_504", "confirm_go_covert"},
		{"@conversation/faction_recruiter_rebel:s_526", "leave_time_overt"},
		{"@conversation/faction_recruiter_rebel:s_538", "resign_overt"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_member_overt_start);


rebel_recruiter_neutral_start = ConvoScreen:new {
	id = "greet_neutral_start",
	leftDialog = "@conversation/faction_recruiter_rebel:s_566",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_580", "join_military"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_neutral_start);


rebel_recruiter_onleave_start = ConvoScreen:new {
	id = "greet_onleave_start",
	leftDialog = "@conversation/faction_recruiter_rebel:s_448",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_450", "resume_duties"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_onleave_start);


--join military
rebel_recruiter_join_military = ConvoScreen:new {
	id = "join_military",
	leftDialog = "@conversation/faction_recruiter_rebel:s_584",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_586", "accept_join"},
		{"@conversation/faction_recruiter_rebel:s_592", "think_more"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_join_military);


--accept_join
rebel_recruiter_accept_join = ConvoScreen:new {
	id = "accept_join",
	leftDialog = "@conversation/faction_recruiter_rebel:s_588",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_590", "accepted_join"},
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accept_join);


--accepted_join
rebel_recruiter_accepted_join = ConvoScreen:new {
	id = "accepted_join",
	leftDialog = "@conversation/faction_recruiter_rebel:s_588",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_join);


--think_more
rebel_recruiter_think_more = ConvoScreen:new {
	id = "think_more",
	leftDialog = "@conversation/faction_recruiter_rebel:s_594",
	stopConversation = "true",
	options = {		
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_think_more);


--confirm_go_overt
rebel_recruiter_confirm_go_overt = ConvoScreen:new {
	id = "confirm_go_overt",
	leftDialog = "@conversation/faction_recruiter_rebel:s_516",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_518", "accepted_go_overt"},
		{"@conversation/faction_recruiter_rebel:s_522", "greet_member_start_overt"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_confirm_go_overt);


--confirm_go_covert
rebel_recruiter_confirm_go_covert = ConvoScreen:new {
	id = "confirm_go_covert",
	leftDialog = "@conversation/faction_recruiter_rebel:s_506",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_508", "accepted_go_covert"},
		{"@conversation/faction_recruiter_rebel:s_512", "greet_member_start_covert"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_confirm_go_covert);


--accepted_go_overt
rebel_recruiter_accepted_go_overt = ConvoScreen:new {
	id = "accepted_go_overt",
	leftDialog = "@conversation/faction_recruiter_rebel:s_520",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_go_overt);


--accepted_go_covert
rebel_recruiter_accepted_go_covert = ConvoScreen:new {
	id = "accepted_go_covert",
	leftDialog = "@conversation/faction_recruiter_rebel:s_514",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_go_covert);


--leave_time
rebel_recruiter_leave_time_covert = ConvoScreen:new {
	id = "leave_time_covert",
	leftDialog = "@conversation/faction_recruiter_rebel:s_528",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_530", "accepted_go_on_leave"},
		{"@conversation/faction_recruiter_rebel:s_534", "greet_member_start_covert"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_leave_time_covert);


rebel_recruiter_leave_time_overt = ConvoScreen:new {
	id = "leave_time_overt",
	leftDialog = "@conversation/faction_recruiter_rebel:s_528",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_530", "accepted_go_on_leave"},
		{"@conversation/faction_recruiter_rebel:s_534", "greet_member_start_overt"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_leave_time_overt);


--accepted_go_on_leave
rebel_recruiter_accepted_go_on_leave = ConvoScreen:new {
	id = "accepted_go_on_leave",
	leftDialog = "@conversation/faction_recruiter_rebel:s_532",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_go_on_leave);


--resign
rebel_recruiter_leave_resign_covert = ConvoScreen:new {
	id = "resign_covert",
	leftDialog = "@conversation/faction_recruiter_rebel:s_540",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_542", "accepted_resign"},
		{"@conversation/faction_recruiter_rebel:s_546", "greet_member_start_covert"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_leave_resign_covert);


rebel_recruiter_leave_resign_overt = ConvoScreen:new {
	id = "resign_overt",
	leftDialog = "@conversation/faction_recruiter_rebel:s_540",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_542", "accepted_resign"},
		{"@conversation/faction_recruiter_rebel:s_546", "greet_member_start_overt"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_leave_resign_overt);


--accepted_resign
rebel_recruiter_accepted_resign = ConvoScreen:new {
	id = "accepted_resign",
	leftDialog = "@conversation/faction_recruiter_rebel:s_544",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_resign);


-------------------------------------------
--resume_duties
rebel_recruiter_resume_duties = ConvoScreen:new {
	id = "resume_duties",
	leftDialog = "@conversation/faction_recruiter_rebel:s_452",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_454", "accepted_resume_duties"},
		{"@conversation/faction_recruiter_rebel:s_458", "greet_onleave_start"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_resume_duties);


--accept_resume_duties
rebel_recruiter_accepted_resume_duties = ConvoScreen:new {
	id = "accepted_resume_duties",
	leftDialog = "@conversation/faction_recruiter_rebel:s_456",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_resume_duties);


--confirm_promotion
rebel_recruiter_confirm_promotion = ConvoScreen:new {
	id = "confirm_promotion",
	leftDialog = "@conversation/faction_recruiter_rebel:s_470",
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_rebel:s_472", "accepted_promotion"}
--		{"@conversation/faction_recruiter_rebel:s_476", "declined_promotion"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_confirm_promotion);


--accepted_promotion
rebel_recruiter_accepted_promotion = ConvoScreen:new {
	id = "accepted_promotion",
	leftDialog = "@conversation/faction_recruiter_rebel:s_474",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_promotion);


--declined_promotion
rebel_recruiter_declined_promotion = ConvoScreen:new {
	id = "declined_promotion",
	leftDialog = "@conversation/faction_recruiter_rebel:s_478",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_declined_promotion);


--not enough points
rebel_recruiter_not_enough_points = ConvoScreen:new {
	id = "not_enough_points",
	leftDialog = "@faction_recruiter:not_enough_for_promotion",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_not_enough_points);


--confirm_bribe
rebel_recruiter_confirm_bribe = ConvoScreen:new {
	id = "confirm_bribe",
	leftDialog = "@conversation/faction_recruiter_rebel:s_570",
	stopConversation = "false",
	options = {
	{"@conversation/faction_recruiter_rebel:s_572", "accepted_bribe_20k"}
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_confirm_bribe);


--accepted_bribe_20k
rebel_recruiter_accepted_bribe_20k = ConvoScreen:new {
	id = "accepted_bribe_20k",
	leftDialog = "@conversation/faction_recruiter_rebel:s_574",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_bribe_20k);


--accepted_bribe_100k
rebel_recruiter_accepted_bribe_100k = ConvoScreen:new {
	id = "accepted_bribe_100k",
	leftDialog = "@conversation/faction_recruiter_rebel:s_574",
	stopConversation = "true",
	options = {
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_accepted_bribe_100k);


-- selected option to purchase faction items
rebel_recruiter_faction_purchase = ConvoScreen:new {
	id = "faction_purchase",
	leftDialog = "@conversation/faction_recruiter_rebel:s_482",  -- we have some things.  what do you need?
	stopConversation = "false",
	options = {
			{ "@faction_recruiter:option_purchase_weapons_armor", "fp_weapons_armor" }, --I'm interested in weapons and armor
			{ "@faction_recruiter:option_purchase_furniture", "fp_furniture"}, -- I'm interested in furniture.
			{ "@faction_recruiter:option_purchase_installation", "fp_installations" }, -- I'm interested in installations.
			{ "@faction_recruiter:option_hirelings", "fp_hirelings" }, -- I would like some personnel support.
	},
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_faction_purchase);



-- selected option to view furniture
rebel_recruiter_fp_furniture = ConvoScreen:new {
	id = "fp_furniture",
	leftDialog = "@faction_recruiter:select_item_purchase", -- select the item you wish to request.  All costs are in faction standing poitns.
	stopConversation = "false",
	options = {

		},
	
}
rebel_recruiter_convotemplate:addScreen(rebel_recruiter_fp_furniture);

-- selected option to view weapons and armor
rebel_recruiter_fp_weapons_armor = ConvoScreen:new {
	id = "fp_weapons_armor",
	leftDialog = "@faction_recruiter:select_item_purchase", -- select the item you wish to request.  All costs are in faction standing poitns.
	stopConversation = "false",
	options = {

		},
	
}
rebel_recruiter_convotemplate:addScreen(rebel_recruiter_fp_weapons_armor);

-- selected option to view installations
rebel_recruiter_fp_installations = ConvoScreen:new {
	id = "fp_installations",
	leftDialog = "@faction_recruiter:select_item_purchase", -- select the item you wish to request.  All costs are in faction standing poitns.
	stopConversation = "false",
	options = {

		},
	
}
rebel_recruiter_convotemplate:addScreen(rebel_recruiter_fp_installations);

-- selected option to view hirelings
rebel_recruiter_fp_hirelings = ConvoScreen:new {
	id = "fp_hirelings",
	leftDialog = "@faction_recruiter:select_item_purchase", -- select the item you wish to request.  All costs are in faction standing poitns.
	stopConversation = "false",
	options = {

		},
	
}
rebel_recruiter_convotemplate:addScreen(rebel_recruiter_fp_hirelings);

-- purchase failed
rebel_recruiter_purchased_not_enough= ConvoScreen:new {
	id = "purchased_not_enough",
	leftDialog = "@faction_recruiter:not_enough_standing_spend", -- YOu do not have enough faction standing to spend.
	stopConversation = "true",
	options = {
	
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_purchased_not_enough);

-- inventory is full screen
rebel_recruiter_inventory_full= ConvoScreen:new {
	id = "inventory_full",
	leftDialog = "@dispenser:inventory_full", -- Your inventory is full.  You must make some room before you can purchase.  
	stopConversation = "true",
	options = {
	
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_inventory_full);

-- datapad is full screen
rebel_recruiter_datapad_full= ConvoScreen:new {
	id = "datapad_full",
	leftDialog = "@faction_recruiter:datapad_full", -- Your datapad is full. You must first free some space.
	stopConversation = "true",
	options = {
	
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_datapad_full);

-- item purchase screen
rebel_recruiter_purchased_item = ConvoScreen:new {
	id = "purchased_item",
	leftDialog = "@faction_recruiter:item_purchase_complete", -- Your requisition of %TT is complete.
	stopConversation = "true",
	options = {
	
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_purchased_item);

-- hireling purchase screen
rebel_recruiter_purchased_hireling = ConvoScreen:new {
	id = "purchased_hireling",
	leftDialog = "@faction_recruiter:hireling_purchase_complete", -- The %TT is now under your command.
	stopConversation = "true",
	options = {
	
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_purchased_hireling);

-- too many hirelings screen
rebel_recruiter_too_many_hirelings = ConvoScreen:new {
	id = "too_many_hirelings",
	leftDialog = "@faction_recruiter:too_many_hirelings", -- You already have too much under your command.
	stopConversation = "true",
	options = {
	
	}
}

rebel_recruiter_convotemplate:addScreen(rebel_recruiter_too_many_hirelings);


addConversationTemplate("rebel_recruiter_convotemplate", rebel_recruiter_convotemplate);
