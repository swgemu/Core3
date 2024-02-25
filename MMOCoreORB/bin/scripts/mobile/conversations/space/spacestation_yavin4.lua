spacestation_yavin4_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_yavin4_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationYavin4ConvoHandler",
	screens = {}
}

-- Greeting

spacestation_yavin4_greeting = ConvoScreen:new {
	id = "spacestation_yavin4_greeting",
	leftDialog = "@conversation/station_yavin4:s_a8657d8a",
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_305434ff", "spacestation_yavin4_land"},
		--{"@conversation/station_yavin4:s_6c8ffad8", "spacestation_yavin4_repair"},
	}
}
spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_yavin4:s_c3e92bf9", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(out_of_range);

-- Land Main
spacestation_yavin4_land = ConvoScreen:new {
	id = "spacestation_yavin4_land",
	leftDialog = "@conversation/station_yavin4:s_2b867034",
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_826b822", "spacestation_yavin4_land_mining_main"},
		{"@conversation/station_yavin4:s_f4af242d", "spacestation_yavin4_land_labor_main"},
		{"@conversation/station_yavin4:s_7afe2900", "spacestation_yavin4_land_imperial_main"},
	}
}
spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_land);

-- Landing Screens

-- Mining Outpost Landing Main

spacestation_yavin4_land_mining_main = ConvoScreen:new {
	id = "spacestation_yavin4_land_mining_main",
	leftDialog = "@conversation/station_yavin4:s_e6e072e0",
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_2dc4697a", "spacestation_yavin4_land_mining_land"},
		{"@conversation/station_yavin4:s_b989d1b3", "spacestation_yavin4_land_all_abort"},
	}
}

spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_land_mining_main);

-- Mining Outpost Landing - Land

spacestation_yavin4_land_mining_land = ConvoScreen:new {
	id = "spacestation_yavin4_land_mining_land",
	leftDialog = "@conversation/station_yavin4:s_914cece8",
	stopConversation = "true",
	options = {}
}

spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_land_mining_land);

-- Labor Outpost Landing Main

spacestation_yavin4_land_labor_main = ConvoScreen:new {
	id = "spacestation_yavin4_land_labor_main",
	leftDialog = "@conversation/station_yavin4:s_b942e498",
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_2dc4697a", "spacestation_yavin4_land_labor_land"},
		{"@conversation/station_yavin4:s_b989d1b3", "spacestation_yavin4_land_all_abort"},
	}
}

spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_land_labor_main);

-- Labor Outpost Landing - Land

spacestation_yavin4_land_labor_land = ConvoScreen:new {
	id = "spacestation_yavin4_land_labor_land",
	leftDialog = "@conversation/station_yavin4:s_914cece8",
	stopConversation = "true",
	options = {}
}

spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_land_labor_land);

-- Imperial Outpost Landing Main

spacestation_yavin4_land_imperial_main = ConvoScreen:new {
	id = "spacestation_yavin4_land_imperial_main",
	leftDialog = "@conversation/station_yavin4:s_238a5da3",
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_2dc4697a", "spacestation_yavin4_land_imperial_land"},
		{"@conversation/station_yavin4:s_b989d1b3", "spacestation_yavin4_land_all_abort"},
	}
}

spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_land_imperial_main);

-- Imperial Outpost Landing - Land

spacestation_yavin4_land_imperial_land = ConvoScreen:new {
	id = "spacestation_yavin4_land_imperial_land",
	leftDialog = "@conversation/station_yavin4:s_914cece8",
	stopConversation = "true",
	options = {}
}

spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_land_imperial_land);

-- Repair Main
spacestation_yavin4_repair = ConvoScreen:new {
	id = "spacestation_yavin4_repair",
	leftDialog = "@conversation/station_yavin4:s_ac4d2f7b", -- Yeah, you got damage, right. We can fix that, no problem, huh?
	stopConversation = "false",
	options = {}
}

spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_repair);

spacestation_yavin4_repair_deny = ConvoScreen:new {
	id = "spacestation_yavin4_repair_deny",
	leftDialog = "@conversation/station_yavin4:s_3aac2f84", -- Yeah, right! You can never mind, too, huh?
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_repair_deny);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_yavin4:s_4bb8df07", -- %DI credits! You gotta pay now, huh!
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_fdfb1283", "accept_repair_25"}, -- (Transfer funds)
		{"@conversation/station_yavin4:s_169df3bb", "deny_repair_25"}, -- Never mind.
	}
}
spacestation_yavin4_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_yavin4:s_b239081a", -- 25% of your ship's damage has been fixed. Now you go on.
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(accept_repair_25);

-- Deny Repair 25
deny_repair_25 = ConvoScreen:new {
	id = "deny_repair_25",
	leftDialog = "@conversation/station_yavin4:s_3aac2f84", -- Yeah, right! You can never mind, too, huh?
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(deny_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_yavin4:s_4bb8df07", -- %DI credits! You gotta pay now, huh!
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_fdfb1283", "accept_repair_50"}, -- (Transfer funds)
		{"@conversation/station_yavin4:s_169df3bb", "deny_repair_50"}, -- Never mind.
	}
}
spacestation_yavin4_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_yavin4:s_7c3eca7b", -- 50% of your ship's damage has been fixed. Now you go on.
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(accept_repair_50);

-- Deny Repair 50
deny_repair_50 = ConvoScreen:new {
	id = "deny_repair_50",
	leftDialog = "@conversation/station_yavin4:s_3aac2f84", -- Yeah, right! You can never mind, too, huh?.
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(deny_repair_50);

-- Repair Most
repair_most = ConvoScreen:new {
	id = "repair_most",
	leftDialog = "@conversation/station_yavin4:s_4bb8df07", -- %DI credits! You gotta pay now, huh!
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_fdfb1283", "accept_repair_75"}, -- (Transfer funds)
		{"@conversation/station_yavin4:s_169df3bb", "deny_repair_75"}, -- Never mind.
	}
}
spacestation_yavin4_convotemplate:addScreen(repair_most);

-- Accept Repair Most
accept_repair_75 = ConvoScreen:new {
	id = "accept_repair_75",
	leftDialog = "@conversation/station_yavin4:s_e5cc8ab2", -- 75% of your ship's damage has been fixed. Now you go on.
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(accept_repair_75);

-- Deny Repair Most
deny_repair_75 = ConvoScreen:new {
	id = "deny_repair_75",
	leftDialog = "@conversation/station_yavin4:s_3aac2f84", -- Yeah, right! You can never mind, too, huh?.
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(deny_repair_75);

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_yavin4:s_4bb8df07", -- %DI credits! You gotta pay now, huh!
	stopConversation = "false",
	options = {
		{"@conversation/station_yavin4:s_fdfb1283", "accept_repair_full"}, -- (Transfer funds)
		{"@conversation/station_yavin4:s_169df3bb", "deny_repair_full"}, -- Never mind.
	}
}
spacestation_yavin4_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_yavin4:s_f3c91859", -- Your ship is fixed, now. So! Now you're leaving, ok!
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(accept_repair_full);

-- Deny Repair Full
deny_repair_full = ConvoScreen:new {
	id = "deny_repair_full",
	leftDialog = "@conversation/station_yavin4:s_3aac2f84", -- Yeah, right! You can never mind, too, huh?.
	stopConversation = "true",
	options = {}
}
spacestation_yavin4_convotemplate:addScreen(deny_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_yavin4_convotemplate", spacestation_yavin4_convotemplate);
