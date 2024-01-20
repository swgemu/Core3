spacestation_corellia_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_corellia_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationCorelliaConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_corellia_greeting = ConvoScreen:new {
	id = "spacestation_corellia_greeting",
	leftDialog = "@conversation/station_corellia:s_87bb06cf", --You have entered CorSec space in the Corellia System.  Please identify yourself and state your business.
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_7e77cbe2", "spacestation_corellia_land"}, --I would like to land
		--{"@conversation/station_corellia:s_c358d041", "spacestation_corellia_repair"}, --(Request Repairs)
	}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_corellia:s_bf5b2480", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(out_of_range);

--Start conversation to land
spacestation_corellia_land = ConvoScreen:new {
	id = "spacestation_corellia_land",
	leftDialog = "@conversation/station_corellia:s_108cc9eb", --There are four starports available to a ship of your class, %TU.  Please indicate your destination.
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_c3399297", "spacestation_corellia_land_coronet"}, --Coronet Starport.
		{"@conversation/station_corellia:s_ccc6f3ed", "spacestation_corellia_land_kor_vella"}, --Kor Vella Starport.
		{"@conversation/station_corellia:s_19bf16ff", "spacestation_corellia_land_doaba_guerfel"}, --Doaba Guerfel Starport.
		{"@conversation/station_corellia:s_63ccb695", "spacestation_corellia_land_tyrena"}, --Tyrena Starport.
	}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land);

--Land at coronet
spacestation_corellia_land_coronet = ConvoScreen:new {
	id = "spacestation_corellia_land_coronet",
	leftDialog = "@conversation/station_corellia:s_d00437d0", --Very well, %TU, you are cleared for landing at the Coronet Starport.
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_2dc4697a", "spacestation_corellia_land_coronet_complete"}, --(Land)
		{"@conversation/station_corellia:s_851eb5fa", "spacestation_corellia_land_coronet_abort"}, --Disregard.
	}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_coronet);

--Finishing landing at coronet
spacestation_corellia_land_coronet_complete = ConvoScreen:new {
	id = "spacestation_corellia_land_coronet_complete",
	leftDialog = "@conversation/station_corellia:s_f7203392", --Assigning you an operator. Transmitting data now.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_coronet_complete);

--Abort landing at coronet
spacestation_corellia_land_coronet_abort = ConvoScreen:new {
	id = "spacestation_corellia_land_coronet_abort",
	leftDialog = "@conversation/station_corellia:s_1bbaf71f", --Roger that, %TU.  Please clear the area for other traffic.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_coronet_abort);

--Land at kor_vella
spacestation_corellia_land_kor_vella = ConvoScreen:new {
	id = "spacestation_corellia_land_kor_vella",
	leftDialog = "@conversation/station_corellia:s_eec4dc6e", --Very well, %TU, you are cleared for landing at the Kor Vella Starport.
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_2dc4697a", "spacestation_corellia_land_kor_vella_complete"}, --(Land)
		{"@conversation/station_corellia:s_851eb5fa", "spacestation_corellia_land_kor_vella_abort"}, --Disregard.
	}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_kor_vella);

--Finishing landing at kor_vella
spacestation_corellia_land_kor_vella_complete = ConvoScreen:new {
	id = "spacestation_corellia_land_kor_vella_complete",
	leftDialog = "@conversation/station_corellia:s_f7203392", --Assigning you an operator. Transmitting data now.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_kor_vella_complete);

--Abort landing at kor_vella
spacestation_corellia_land_kor_vella_abort = ConvoScreen:new {
	id = "spacestation_corellia_land_kor_vella_abort",
	leftDialog = "@conversation/station_corellia:s_1bbaf71f", --Roger that, %TU.  Please clear the area for other traffic.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_kor_vella_abort);

--Land at doaba_guerfel
spacestation_corellia_land_doaba_guerfel = ConvoScreen:new {
	id = "spacestation_corellia_land_doaba_guerfel",
	leftDialog = "@conversation/station_corellia:s_b596ece0", --Very well, %TU, you are cleared for landing at the Doaba Guerfel Starport.
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_2dc4697a", "spacestation_corellia_land_doaba_guerfel_complete"}, --(Land)
		{"@conversation/station_corellia:s_851eb5fa", "spacestation_corellia_land_doaba_guerfel_abort"}, --Disregard.
	}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_doaba_guerfel);

--Finishing landing at doaba_guerfel
spacestation_corellia_land_doaba_guerfel_complete = ConvoScreen:new {
	id = "spacestation_corellia_land_doaba_guerfel_complete",
	leftDialog = "@conversation/station_corellia:s_f7203392", --Assigning you an operator. Transmitting data now.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_doaba_guerfel_complete);

--Abort landing at doaba_guerfel
spacestation_corellia_land_doaba_guerfel_abort = ConvoScreen:new {
	id = "spacestation_corellia_land_doaba_guerfel_abort",
	leftDialog = "@conversation/station_corellia:s_1bbaf71f", --Roger that, %TU.  Please clear the area for other traffic.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_doaba_guerfel_abort);

--Land at tyrena
spacestation_corellia_land_tyrena = ConvoScreen:new {
	id = "spacestation_corellia_land_tyrena",
	leftDialog = "@conversation/station_corellia:s_f0f7d52d", --Very well, %TU, you are cleared for landing at the Tyrena Starport.
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_2dc4697a", "spacestation_corellia_land_tyrena_complete"}, --(Land)
		{"@conversation/station_corellia:s_851eb5fa", "spacestation_corellia_land_tyrena_abort"}, --Disregard.
	}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_tyrena);

--Finishing landing at tyrena
spacestation_corellia_land_tyrena_complete = ConvoScreen:new {
	id = "spacestation_corellia_land_tyrena_complete",
	leftDialog = "@conversation/station_corellia:s_f7203392", --Assigning you an operator. Transmitting data now.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_tyrena_complete);

--Abort landing at tyrena
spacestation_corellia_land_tyrena_abort = ConvoScreen:new {
	id = "spacestation_corellia_land_tyrena_abort",
	leftDialog = "@conversation/station_corellia:s_1bbaf71f", --Roger that, %TU.  Please clear the area for other traffic.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_land_tyrena_abort);

-- Repair Main
spacestation_corellia_repair = ConvoScreen:new {
	id = "spacestation_corellia_repair",
	leftDialog = "@conversation/station_corellia:s_13071055", --Roger, %TU.  We are a fully functional station and can provide you with whatever level of repairs that are necessary.  Please indicate your status.
	stopConversation = "false",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_repair);

spacestation_corellia_repair_deny = ConvoScreen:new {
	id = "spacestation_corellia_repair_deny",
	leftDialog = "@conversation/station_corellia:s_2f3c1bdc", -- Copy that, %TU.  CorSec station out.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(spacestation_corellia_repair_deny);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_corellia:s_99824a76", -- Roger, %TU.  For a fee of %DI credits we'll repair just enough to get you underway.  Please confirm.
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_b1525744", "accept_repair_25"}, -- Do it
		{"@conversation/station_corellia:s_457a7010", "deny_repair_25"}, -- No
	}
}
spacestation_corellia_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_corellia:s_2f8c6a62", -- 25% of your ship damage has been fixed. Please clear the area for other traffic.  CorSec station, out.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(accept_repair_25);

-- Deny Repair 25
deny_repair_25 = ConvoScreen:new {
	id = "deny_repair_25",
	leftDialog = "@conversation/station_corellia:s_71a60205", -- As you wish, %TU.  Please clear the area for other traffic.  CorSec station, out.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(deny_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_corellia:s_28d56475", -- Affirmative, %TU.  Repairing half your current damage will cost %DI credits. Are you ready to transfer the funds?
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_370822d1", "accept_repair_50"}, -- Yes
		{"@conversation/station_corellia:s_457a7010", "deny_repair_50"}, -- No
	}
}
spacestation_corellia_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_corellia:s_9be6fb53", -- Received, %TU.  Half of your ship damage has been fixed.  You are clear to leave the area.  CorSec station, out.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(accept_repair_50);

-- Deny Repair 50
deny_repair_50 = ConvoScreen:new {
	id = "deny_repair_50",
	leftDialog = "@conversation/station_corellia:s_71a60205", -- As you wish, %TU.  Please clear the area for other traffic.  CorSec station, out.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(deny_repair_50);

-- Repair Most
repair_most = ConvoScreen:new {
	id = "repair_most",
	leftDialog = "@conversation/station_corellia:s_c3f09c65", -- Roger that, %TU.  We can repair three-fourths of your ship's damage at a fee of %DI credits.  Are you ready to transfer the funds?
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_370822d1", "accept_repair_75"}, -- Yes
		{"@conversation/station_corellia:s_457a7010", "deny_repair_75"}, -- No
	}
}
spacestation_corellia_convotemplate:addScreen(repair_most);

-- Accept Repair Most
accept_repair_75 = ConvoScreen:new {
	id = "accept_repair_75",
	leftDialog = "@conversation/station_corellia:s_4a546bbb", -- Funds received, %TU... Repairs complete.  You are clear to leave the station.  CorSec station, out.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(accept_repair_75);

-- Deny Repair Most
deny_repair_75 = ConvoScreen:new {
	id = "deny_repair_75",
	leftDialog = "@conversation/station_corellia:s_af84143a", -- Bye
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(deny_repair_75);

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_corellia:s_ef7f535a", -- A complete repair of your ship will cost %DI credits, %TU.  Are you sure?
	stopConversation = "false",
	options = {
		{"@conversation/station_corellia:s_370822d1", "accept_repair_full"}, -- Yes
		{"@conversation/station_corellia:s_457a7010", "deny_repair_full"}, -- No
	}
}
spacestation_corellia_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_corellia:s_26f0c6f6", -- Repairs complete!  You are clear to leave CorSec station, out.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(accept_repair_full);

-- Deny Repair Full
deny_repair_full = ConvoScreen:new {
	id = "deny_repair_full",
	leftDialog = "@conversation/station_corellia:s_a98368fb", --  As you wish, %TU.  Please leave the area to make room for incoming traffic.  Out.
	stopConversation = "true",
	options = {}
}
spacestation_corellia_convotemplate:addScreen(deny_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_corellia_convotemplate", spacestation_corellia_convotemplate);
