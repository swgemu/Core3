spacestation_naboo_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_naboo_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationNabooConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_naboo_greeting = ConvoScreen:new {
	id = "spacestation_naboo_greeting",
	leftDialog = "@conversation/station_naboo:s_decdd151", --You have entered Naboo space, under the protection of the Royal Security Forces. Please identify yourself and your reason for visiting Naboo.
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_cebd107d", "spacestation_naboo_land"}, --(Request Permission to Land)
		--{"@conversation/station_naboo:s_c358d041", "spacestation_naboo_repair"}, --(Request Repairs)
	}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_naboo:s_1951f1c1", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(out_of_range);

--Start conversation to land
spacestation_naboo_land = ConvoScreen:new {
	id = "spacestation_naboo_land",
	leftDialog = "@conversation/station_naboo:s_4bb1f207", --Acknowledged, %TU. Please transmit your destination for flight clearance.
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_c42b6203", "spacestation_naboo_land_theed"}, --Theed Starport.
		{"@conversation/station_naboo:s_8845528b", "spacestation_naboo_land_kaadara"}, --Kaadara Starport.
		{"@conversation/station_naboo:s_a716a9c7", "spacestation_naboo_land_keren"}, --Keren Starport.
		{"@conversation/station_naboo:s_2f99890c", "spacestation_naboo_land_moenia"}, --Moenia Starport.
	}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land);

--Land at Theed
spacestation_naboo_land_theed = ConvoScreen:new {
	id = "spacestation_naboo_land_theed",
	leftDialog = "@conversation/station_naboo:s_8e61aac7", --Acknowledged, %TU. Theed Starport is awaiting your arrival.
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_2dc4697a", "spacestation_naboo_land_theed_complete"}, --(Land)
		{"@conversation/station_naboo:s_f148786f", "spacestation_naboo_land_theed_abort"}, --Cancel request to land.
	}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_theed);

--Finishing landing at Theed
spacestation_naboo_land_theed_complete = ConvoScreen:new {
	id = "spacestation_naboo_land_theed_complete",
	leftDialog = "@conversation/station_naboo:s_390e6f9a", --Enjoy your stay in Theed, %NU.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_theed_complete);

--Abort landing at Theed
spacestation_naboo_land_theed_abort = ConvoScreen:new {
	id = "spacestation_naboo_land_theed_abort",
	leftDialog = "@conversation/station_naboo:s_c6aaa6b3", --Of course, Sir! Let me know when you are ready.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_theed_abort);

--Land at Kaadara
spacestation_naboo_land_kaadara = ConvoScreen:new {
	id = "spacestation_naboo_land_kaadara",
	leftDialog = "@conversation/station_naboo:s_14ed557a", --Acknowledged, %TU. Kaadara Starport is awaiting your arrival.
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_2dc4697a", "spacestation_naboo_land_kaadara_complete"}, --(Land)
		{"@conversation/station_naboo:s_f148786f", "spacestation_naboo_land_kaadara_abort"}, --Cancel request to land.
	}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_kaadara);

--Finishing landing at Kaadara
spacestation_naboo_land_kaadara_complete = ConvoScreen:new {
	id = "spacestation_naboo_land_kaadara_complete",
	leftDialog = "@conversation/station_naboo:s_c9361653", --Enjoy your stay in Kaadara, %NU.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_kaadara_complete);

--Abort landing at Kaadara
spacestation_naboo_land_kaadara_abort = ConvoScreen:new {
	id = "spacestation_naboo_land_kaadara_abort",
	leftDialog = "@conversation/station_naboo:s_c6aaa6b3", --Of course, Sir! Let me know when you are ready.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_kaadara_abort);

--Land at Keren
spacestation_naboo_land_keren = ConvoScreen:new {
	id = "spacestation_naboo_land_keren",
	leftDialog = "@conversation/station_naboo:s_cfbc1584", --Acknowledged, %TU. Keren Starport is awaiting your arrival.
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_2dc4697a", "spacestation_naboo_land_keren_complete"}, --(Land)
		{"@conversation/station_naboo:s_f148786f", "spacestation_naboo_land_keren_abort"}, --Cancel request to land.
	}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_keren);

--Finishing landing at Keren
spacestation_naboo_land_keren_complete = ConvoScreen:new {
	id = "spacestation_naboo_land_keren_complete",
	leftDialog = "@conversation/station_naboo:s_13eddc62", --Enjoy your stay in Keren, %NU.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_keren_complete);

--Abort landing at Keren
spacestation_naboo_land_keren_abort = ConvoScreen:new {
	id = "spacestation_naboo_land_keren_abort",
	leftDialog = "@conversation/station_naboo:s_c6aaa6b3", --Of course, Sir! Let me know when you are ready.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_keren_abort);

--Land at Moenia
spacestation_naboo_land_moenia = ConvoScreen:new {
	id = "spacestation_naboo_land_moenia",
	leftDialog = "@conversation/station_naboo:s_7cffc9b4", --Acknowledged, %TU. Moenia Starport is awaiting your arrival.
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_2dc4697a", "spacestation_naboo_land_moenia_complete"}, --(Land)
		{"@conversation/station_naboo:s_f148786f", "spacestation_naboo_land_moenia_abort"}, --Cancel request to land.
	}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_moenia);

--Finishing landing at Moenia
spacestation_naboo_land_moenia_complete = ConvoScreen:new {
	id = "spacestation_naboo_land_moenia_complete",
	leftDialog = "@conversation/station_naboo:s_41f82cf5", --Enjoy your stay in Moenia, %NU.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_moenia_complete);

--Abort landing at Moenia
spacestation_naboo_land_moenia_abort = ConvoScreen:new {
	id = "spacestation_naboo_land_moenia_abort",
	leftDialog = "@conversation/station_naboo:s_c6aaa6b3", --Of course, Sir! Let me know when you are ready.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_moenia_abort);

-- Repair Main
spacestation_naboo_repair = ConvoScreen:new {
	id = "spacestation_naboo_repair",
	leftDialog = "@conversation/station_naboo:s_4b9c311", --Acknowledged, %TU. How much of the damage to your ship do you want to be repaired at this time?
	stopConversation = "false",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_repair);

spacestation_naboo_repair_deny = ConvoScreen:new {
	id = "spacestation_naboo_repair_deny",
	leftDialog = "@conversation/station_naboo:s_43af1e95", -- Ok, %NU. Please comm us if this station can be of service.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_repair_deny);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_naboo:s_cb44587c", -- This station will charge a fee of %DI credits to make only the most basic repairs to your ship. Are you ready to transfer the funds?
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_d70dba34", "accept_repair_25"}, -- Yes.
		{"@conversation/station_naboo:s_4c695dbd", "deny_repair_25"}, -- No.
	}
}
spacestation_naboo_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_naboo:s_f478139", -- Repairs complete, %TU. 25% of your ship's damage has been fixed. Thank you for visiting the Royal Security Forces Naboo Station.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(accept_repair_25);

-- Deny Repair 25
deny_repair_25 = ConvoScreen:new {
	id = "deny_repair_25",
	leftDialog = "@conversation/station_naboo:s_f918e086", -- Acknowledged, %NU. Please comm us when we can be of further service.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(deny_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_naboo:s_7f991ab5", -- This station will charge a fee of %DI credits to fix half of your ship's damage. Are you ready to transfer the funds?
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_d70dba34", "accept_repair_50"}, -- Yes.
		{"@conversation/station_naboo:s_4c695dbd", "deny_repair_50"}, -- No.
	}
}
spacestation_naboo_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_naboo:s_3b9f150e", -- Repairs complete, %TU. 50% of your ship's damage has been fixed. Thank you for visiting the Royal Security Forces Naboo Station.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(accept_repair_50);

-- Deny Repair 50
deny_repair_50 = ConvoScreen:new {
	id = "deny_repair_50",
	leftDialog = "@conversation/station_naboo:s_f918e086", -- Acknowledged, %NU. Please comm us when we can be of further service.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(deny_repair_50);

-- Repair Most
repair_most = ConvoScreen:new {
	id = "repair_most",
	leftDialog = "@conversation/station_naboo:s_a0434258", -- This station will charge a fee of %DI credits to repairs most of the damage to your ship. Are you ready to transfer the funds?
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_d70dba34", "accept_repair_75"}, -- Yes.
		{"@conversation/station_naboo:s_4c695dbd", "deny_repair_75"}, -- No.
	}
}
spacestation_naboo_convotemplate:addScreen(repair_most);

-- Accept Repair Most
accept_repair_75 = ConvoScreen:new {
	id = "accept_repair_75",
	leftDialog = "@conversation/station_naboo:s_ca5ee405", -- Repairs complete, %TU. 75% of your ship's damage has been fixed. Thank you for visiting the Royal Security Forces Naboo Station.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(accept_repair_75);

-- Deny Repair Most
deny_repair_75 = ConvoScreen:new {
	id = "deny_repair_75",
	leftDialog = "@conversation/station_naboo:s_f918e086", -- Acknowledged, %NU. Please comm us when we can be of further service.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(deny_repair_75);

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_naboo:s_67f72920", -- This station will charge a fee of %DI credits to repair all of the damage to your ship. Are you ready to transfer the funds?
	stopConversation = "false",
	options = {
		{"@conversation/station_naboo:s_d70dba34", "accept_repair_full"}, -- Yes.
		{"@conversation/station_naboo:s_4c695dbd", "deny_repair_full"}, -- No.
	}
}
spacestation_naboo_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_naboo:s_5cc333f9", -- Repairs complete, %TU. All of your ship's damage has been fixed. Thank you for visiting the Royal Security Forces Naboo Station.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(accept_repair_full);

-- Deny Repair Full
deny_repair_full = ConvoScreen:new {
	id = "deny_repair_full",
	leftDialog = "@conversation/station_naboo:s_f918e086", --  Acknowledged, %NU. Please comm us when we can be of further service.
	stopConversation = "true",
	options = {}
}
spacestation_naboo_convotemplate:addScreen(deny_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_naboo_convotemplate", spacestation_naboo_convotemplate);
