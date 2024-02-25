spacestation_talus_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_talus_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationTalusConvoHandler",
	screens = {}
}
--There are two full versions of this same dialogue - one in Selonian for most players, and one in English for smugglers. TODO - implement the smuggler version.
-- Initial Greeting
spacestation_talus_greeting = ConvoScreen:new {
	id = "spacestation_talus_greeting",
	leftDialog = "@conversation/station_talus:s_a830645d", --Neeshter syish freg'n Talus Station. Meesta krand't fnyor, %TU?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_f34bcf78", "spacestation_talus_land"}, --(Request Landing Permission)
		--{"@conversation/station_talus:s_c358d041", "spacestation_talus_repair"}, --(Request Repairs)
	}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_talus:s_a830645d", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(out_of_range);

--Start conversation to land
spacestation_talus_land = ConvoScreen:new {
	id = "spacestation_talus_land",
	leftDialog = "@conversation/station_talus:s_3ee404d7", --Fnyenk, b'dor, %TU?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_9b8f2142", "spacestation_talus_land_dearic"}, --Dearic Starport.
		{"@conversation/station_talus:s_16015565", "spacestation_talus_land_nashal"}, --Nashal Starport.
		{"@conversation/station_talus:s_2902ab38", "spacestation_talus_land_imperial"}, --Imperial Outpost Starport.
	}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land);

--Land at Dearic
spacestation_talus_land_dearic = ConvoScreen:new {
	id = "spacestation_talus_land_dearic",
	leftDialog = "@conversation/station_talus:s_5e3d8b95", --Nyard'msh k'rall deeba Dearic Starport?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_d70dba34", "spacestation_talus_land_dearic_complete"}, --Yes.
		{"@conversation/station_talus:s_4c695dbd", "spacestation_talus_land_dearic_abort"}, --No.
	}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_dearic);

--Finishing landing at Dearic
spacestation_talus_land_dearic_complete = ConvoScreen:new {
	id = "spacestation_talus_land_dearic_complete",
	leftDialog = "@conversation/station_talus:s_fd46b8d9", --Kan'dest ka nir zan da zint! Pa!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_dearic_complete);

--Abort landing at Dearic
spacestation_talus_land_dearic_abort = ConvoScreen:new {
	id = "spacestation_talus_land_dearic_abort",
	leftDialog = "@conversation/station_talus:s_672b2c6f", --Fnyorgin p'shhis!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_dearic_abort);

--Land at Nashal
spacestation_talus_land_nashal = ConvoScreen:new {
	id = "spacestation_talus_land_nashal",
	leftDialog = "@conversation/station_talus:s_d3b3ffb2", --Nyard'msh k'rall deeba Nashal Starport?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_d70dba34", "spacestation_talus_land_nashal_complete"}, --Yes.
		{"@conversation/station_talus:s_4c695dbd", "spacestation_talus_land_nashal_abort"}, --No.
	}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_nashal);

--Finishing landing at Kaadara
spacestation_talus_land_nashal_complete = ConvoScreen:new {
	id = "spacestation_talus_land_nashal_complete",
	leftDialog = "@conversation/station_talus:s_fd46b8d9", --Kan'dest ka nir zan da zint! Pa!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_nashal_complete);

--Abort landing at Kaadara
spacestation_talus_land_nashal_abort = ConvoScreen:new {
	id = "spacestation_talus_land_nashal_abort",
	leftDialog = "@conversation/station_talus:s_672b2c6f", --Fnyorgin p'shhis!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_nashal_abort);

--Land at Imperial Outpost
spacestation_talus_land_imperial = ConvoScreen:new {
	id = "spacestation_talus_land_imperial",
	leftDialog = "@conversation/station_talus:s_cd4fd870", --Nyard'msh k'rall deeba Talus Imperial Outpost?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_d70dba34", "spacestation_talus_land_imperial_complete"}, --Yes.
		{"@conversation/station_talus:s_4c695dbd", "spacestation_talus_land_imperial_abort"}, --No.
	}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_imperial);

--Finishing landing at Imperial Outpost
spacestation_talus_land_imperial_complete = ConvoScreen:new {
	id = "spacestation_talus_land_imperial_complete",
	leftDialog = "@conversation/station_talus:s_fd46b8d9", --Kan'dest ka nir zan da zint! Pa!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_imperial_complete);

--Abort landing at Imperial Outpost
spacestation_talus_land_imperial_abort = ConvoScreen:new {
	id = "spacestation_talus_land_imperial_abort",
	leftDialog = "@conversation/station_talus:s_672b2c6f", --Fnyorgin p'shhis!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_land_imperial_abort);

-- Repair Main
spacestation_talus_repair = ConvoScreen:new {
	id = "spacestation_talus_repair",
	leftDialog = "@conversation/station_talus:s_335e1e3", --Mag'n fweroba, %NU! Eshka b'lor ka pa?
	stopConversation = "false",
	options = {}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_repair);

spacestation_talus_repair_deny = ConvoScreen:new {
	id = "spacestation_talus_repair_deny",
	leftDialog = "@conversation/station_talus:s_c245bae", -- Pa!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(spacestation_talus_repair_deny);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_talus:s_3adc835a", -- T'cost din miska %DI credits. Ka dir pa?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_d70dba34", "accept_repair_25"}, -- Yes.
		{"@conversation/station_talus:s_4c695dbd", "deny_repair_25"}, -- No.
	}
}
spacestation_talus_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_talus:s_f895eb69", -- Kan'dest ka nir zint! Pa!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(accept_repair_25);

-- Deny Repair 25
deny_repair_25 = ConvoScreen:new {
	id = "deny_repair_25",
	leftDialog = "@conversation/station_talus:s_c245bae", -- Pa!.
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(deny_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_talus:s_3adc835a", -- T'cost din miska %DI credits. Ka dir pa?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_d70dba34", "accept_repair_50"}, -- Yes.
		{"@conversation/station_talus:s_4c695dbd", "deny_repair_50"}, -- No.
	}
}
spacestation_talus_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_talus:s_f895eb69", -- Kan'dest ka nir zint! Pa!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(accept_repair_50);

-- Deny Repair 50
deny_repair_50 = ConvoScreen:new {
	id = "deny_repair_50",
	leftDialog = "@conversation/station_talus:s_c245bae", -- Pa!.
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(deny_repair_50);

-- Repair Most
repair_most = ConvoScreen:new {
	id = "repair_most",
	leftDialog = "@conversation/station_talus:s_3adc835a", -- T'cost din miska %DI credits. Ka dir pa?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_d70dba34", "accept_repair_75"}, -- Yes.
		{"@conversation/station_talus:s_4c695dbd", "deny_repair_75"}, -- No.
	}
}
spacestation_talus_convotemplate:addScreen(repair_most);

-- Accept Repair Most
accept_repair_75 = ConvoScreen:new {
	id = "accept_repair_75",
	leftDialog = "@conversation/station_talus:s_f895eb69", -- Kan'dest ka nir zint! Pa!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(accept_repair_75);

-- Deny Repair Most
deny_repair_75 = ConvoScreen:new {
	id = "deny_repair_75",
	leftDialog = "@conversation/station_talus:s_c245bae", -- Pa!.
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(deny_repair_75);

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_talus:s_3adc835a", -- T'cost din miska %DI credits. Ka dir pa?
	stopConversation = "false",
	options = {
		{"@conversation/station_talus:s_d70dba34", "accept_repair_full"}, -- Yes.
		{"@conversation/station_talus:s_4c695dbd", "deny_repair_full"}, -- No.
	}
}
spacestation_talus_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_talus:s_f895eb69", -- Kan'dest ka nir zint! Pa!
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(accept_repair_full);

-- Deny Repair Full
deny_repair_full = ConvoScreen:new {
	id = "deny_repair_full",
	leftDialog = "@conversation/station_talus:s_c245bae", -- Pa!.
	stopConversation = "true",
	options = {}
}
spacestation_talus_convotemplate:addScreen(deny_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_talus_convotemplate", spacestation_talus_convotemplate);
