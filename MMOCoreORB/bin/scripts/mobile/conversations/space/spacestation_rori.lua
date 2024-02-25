spacestation_rori_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_rori_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationRoriConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_rori_greeting = ConvoScreen:new {
	id = "spacestation_rori_greeting",
	leftDialog = "@conversation/station_rori:s_331", --Ello, boyos! Yous wantin ta speedaway down ta Roritowns? Or yousa been crunchen?
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_327", "spacestation_rori_land"}, --I want to land.
		--{"@conversation/station_rori:s_373", "spacestation_rori_repair"}, --I need repairs.
	}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_rori:s_201", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(out_of_range);

--Start conversation to land
spacestation_rori_land = ConvoScreen:new {
	id = "spacestation_rori_land",
	leftDialog = "@conversation/station_rori:s_335", --Okeyday! Wesa give usa landaway... Which Roritown yousa goen?
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_337", "spacestation_rori_land_narmle"}, --Narmle Starport.
		{"@conversation/station_rori:s_349", "spacestation_rori_land_restuss"}, --Restuss Starport.
	}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_land);

--Land at Narmle
spacestation_rori_land_narmle = ConvoScreen:new {
	id = "spacestation_rori_land_narmle",
	leftDialog = "@conversation/station_rori:s_339", --Allee clear! Yousen landaway now.
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_341", "spacestation_rori_land_narmle_complete"}, --Thank you.
		{"@conversation/station_rori:s_345", "spacestation_rori_land_narmle_abort"}, --On second thought, never mind.
	}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_land_narmle);

--Finishing landing at Narmle
spacestation_rori_land_narmle_complete = ConvoScreen:new {
	id = "spacestation_rori_land_narmle_complete",
	leftDialog = "@conversation/station_rori:s_455", --Okeyday! Byenow.
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_land_narmle_complete);

--Abort landing at Narmle
spacestation_rori_land_narmle_abort = ConvoScreen:new {
	id = "spacestation_rori_land_narmle_abort",
	leftDialog = "@conversation/station_rori:s_455", --Okeyday! Byenow.
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_land_narmle_abort);

--Land at Restuss
spacestation_rori_land_restuss = ConvoScreen:new {
	id = "spacestation_rori_land_restuss",
	leftDialog = "@conversation/station_rori:s_351", --Werry good! Restuss is waitin-now fer yousa!
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_341", "spacestation_rori_land_restuss_complete"}, --Thank you.
		{"@conversation/station_rori:s_357", "spacestation_rori_land_restuss_abort"}, --Cancel that request.
	}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_land_restuss);

--Finishing landing at Restuss
spacestation_rori_land_restuss_complete = ConvoScreen:new {
	id = "spacestation_rori_land_restuss_complete",
	leftDialog = "@conversation/station_rori:s_455", --Okeyday! Byenow.
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_land_restuss_complete);

--Abort landing at Restuss
spacestation_rori_land_restuss_abort = ConvoScreen:new {
	id = "spacestation_rori_land_restuss_abort",
	leftDialog = "@conversation/station_rori:s_455", --Okeyday! Byenow.
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_land_restuss_abort);

-- Repair Main
spacestation_rori_repair = ConvoScreen:new {
	id = "spacestation_rori_repair",
	leftDialog = "@conversation/station_rori:s_375", -- Oie Boie! You been crunchen, huh? Wesa gonna fix you up!
	stopConversation = "false",
	options = {}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_repair);

spacestation_rori_repair2 = ConvoScreen:new {
	id = "spacestation_rori_repair2",
	leftDialog = "@conversation/station_rori:s_435", -- Yuosa see, we fix dat crunchen an yousa been good en new.
	stopConversation = "false",
	options = {}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_repair2);

spacestation_rori_repair_unsure = ConvoScreen:new {
	id = "spacestation_rori_repair_unsure",
	leftDialog = "@conversation/station_rori:s_431", -- No problem, %TU! Wesa pitty good at dis!
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_433", "spacestation_rori_repair2"}, -- Ok, I want repairs.
		{"@conversation/station_rori:s_437", "spacestation_rori_repair_deny"}, -- Forget it. I'll get repairs somewhere else.
	}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_repair_unsure);

spacestation_rori_repair_deny = ConvoScreen:new {
	id = "spacestation_rori_repair_deny",
	leftDialog = "@conversation/station_rori:s_439", -- Yousa tink yous smarty den us-ens? Yousa tink yous brain so big. Yousa fixen dat crunchen on your own sef den!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_repair_deny);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_rori:s_379", -- Wesa fixen some da crunchen to your ship. You payin %DI credits?
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_381", "accept_repair_25"}, -- Yes.
		{"@conversation/station_rori:s_385", "deny_repair_25"}, -- Never mind.
	}
}
spacestation_rori_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_rori:s_383", -- Okeyday! We dood it!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(accept_repair_25);

-- Deny Repair 25
deny_repair_25 = ConvoScreen:new {
	id = "deny_repair_25",
	leftDialog = "@conversation/station_rori:s_387", -- Okeyday! Byenow, %NU!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(deny_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_rori:s_391", -- Wesa fixen halfsies on da crunchen. You payin %DI credits?
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_393", "accept_repair_50"}, -- Yes.
		{"@conversation/station_rori:s_397", "deny_repair_50"}, -- No.
	}
}
spacestation_rori_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_rori:s_383", -- Okeyday! We dood it!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(accept_repair_50);

-- Deny Repair 50
deny_repair_50 = ConvoScreen:new {
	id = "deny_repair_50",
	leftDialog = "@conversation/station_rori:s_387", -- Okeyday! Byenow, %NU!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(deny_repair_50);

-- Repair Most
repair_most = ConvoScreen:new {
	id = "repair_most",
	leftDialog = "@conversation/station_rori:s_403", -- Wesa fixen mossen all da crunchen. You payin %DI credits?
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_405", "accept_repair_75"}, -- Yes.
		{"@conversation/station_rori:s_409", "deny_repair_75"}, -- No.
	}
}
spacestation_rori_convotemplate:addScreen(repair_most);

-- Accept Repair Most
accept_repair_75 = ConvoScreen:new {
	id = "accept_repair_75",
	leftDialog = "@conversation/station_rori:s_407", -- Okeyday! We dood it!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(accept_repair_75);

-- Deny Repair Most
deny_repair_75 = ConvoScreen:new {
	id = "deny_repair_75",
	leftDialog = "@conversation/station_rori:s_411", -- Okeyday! Byenow, %NU!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(deny_repair_75);

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_rori:s_415", -- We fixen all dat crunchen fer %DI credits. Okeyday?
	stopConversation = "false",
	options = {
		{"@conversation/station_rori:s_417", "accept_repair_full"}, -- Yes.
		{"@conversation/station_rori:s_421", "deny_repair_full"}, -- No.
		{"@conversation/station_rori:s_425", "accept_repair_full"}, -- Okeyday!
	}
}
spacestation_rori_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_rori:s_419", -- We dood it! Yousa allee bombad now!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(accept_repair_full);

-- Deny Repair Full
deny_repair_full = ConvoScreen:new {
	id = "deny_repair_full",
	leftDialog = "@conversation/station_rori:s_423", -- Okeyday! Byenow, %NU!
	stopConversation = "true",
	options = {}
}
spacestation_rori_convotemplate:addScreen(deny_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_rori_convotemplate", spacestation_rori_convotemplate);
