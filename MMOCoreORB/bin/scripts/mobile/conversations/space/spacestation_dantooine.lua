spacestation_dantooine_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_dantooine_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationDantooineConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_dantooine_greeting = ConvoScreen:new {
	id = "spacestation_dantooine_greeting",
	leftDialog = "@conversation/station_dantooine:s_73a08149", --This is Dantooine Station. What can I do for ya?
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_75f22c97", "spacestation_dantooine_land_prelude"}, --I want to land on Dantooine.
		--{"@conversation/station_dantooine:s_54c04765", "spacestation_dantooine_repair"}, --I need repairs!
	}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_dantooine:s_1b90bd5", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(out_of_range);

--Extra Dantooine-only conversation
spacestation_dantooine_land_prelude = ConvoScreen:new {
	id = "spacestation_dantooine_land_prelude",
	leftDialog = "@conversation/station_dantooine:s_688c4b5e", --Good grief, friend. Why would you want to land here?
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_fc85e244", "spacestation_dantooine_land"}, --I have business on Dantooine.
	}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_prelude);

--Start conversation to land
spacestation_dantooine_land = ConvoScreen:new {
	id = "spacestation_dantooine_land",
	leftDialog = "@conversation/station_dantooine:s_460d6dba", --There are nicer places to visit in the galaxy, but I suppose if you're in a pinch, then you might be able to get by on Dantooine.
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_9fa6755e", "spacestation_dantooine_land_mining"}, --Let me land at the Mining Outpost.
		{"@conversation/station_dantooine:s_9977dcd9", "spacestation_dantooine_land_agro"}, --Let me land at the Agro Outpost.
		{"@conversation/station_dantooine:s_6c9d2543", "spacestation_dantooine_land_imperial"}, --Let me land at the Imperial Outpost.
	}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land);

--Land at Mining Outpost
spacestation_dantooine_land_mining = ConvoScreen:new {
	id = "spacestation_dantooine_land_mining",
	leftDialog = "@conversation/station_dantooine:s_bc8bd720", --That mining outpost hasn't been producing decent resources for months. I'd suggest traveling to a different system. I hear Naboo is nice.
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_890b6a4c", "spacestation_dantooine_land_mining_complete"}, --Just clear me for landing.
		{"@conversation/station_dantooine:s_737e644a", "spacestation_dantooine_land_mining_abort"}, --Never mind then.
	}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_mining);

--Finishing landing at Mining Outpost
spacestation_dantooine_land_mining_complete = ConvoScreen:new {
	id = "spacestation_dantooine_land_mining_complete",
	leftDialog = "@conversation/station_dantooine:s_3ca4bcbc", --Ok, ok... don't know why you're in such a rush to go there, though. You're cleared for landing.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_mining_complete);

--Abort landing at Mining Outpost
spacestation_dantooine_land_mining_abort = ConvoScreen:new {
	id = "spacestation_dantooine_land_mining_abort",
	leftDialog = "@conversation/station_dantooine:s_338dd0a0", --Ok, what do ya want then?
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_mining_abort);

--Land at Agro Outpost
spacestation_dantooine_land_agro = ConvoScreen:new {
	id = "spacestation_dantooine_land_agro",
	leftDialog = "@conversation/station_dantooine:s_8316a19c", --Oh... Oh! You're one of... I mean. Ok, then. You're sure you want to land there? I mean, there's some rough customers around those parts, if you know what I mean.
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_bceb6c8c", "spacestation_dantooine_land_agro_complete"}, --Yes, clear me for landing.
		{"@conversation/station_dantooine:s_5d4f7fdb", "spacestation_dantooine_land_agro_abort"}, --On second thought...
	}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_agro);

--Finishing landing at Agro Outpost
spacestation_dantooine_land_agro_complete = ConvoScreen:new {
	id = "spacestation_dantooine_land_agro_complete",
	leftDialog = "@conversation/station_dantooine:s_ff02facb", --Ok. Give us a comm if there's anything I can do for you.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_agro_complete);

--Abort landing at Agro Outpost
spacestation_dantooine_land_agro_abort = ConvoScreen:new {
	id = "spacestation_dantooine_land_agro_abort",
	leftDialog = "@conversation/station_dantooine:s_432005ea", --Ok what do ya want then?
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_agro_abort);

--Land at Imperial Military Outpost
spacestation_dantooine_land_imperial = ConvoScreen:new {
	id = "spacestation_dantooine_land_imperial",
	leftDialog = "@conversation/station_dantooine:s_eb3c41c", --Oh, I see. Here on official business, are you?
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_890b6a4c", "spacestation_dantooine_land_imperial_complete"}, --Just clear me for landing.
		{"@conversation/station_dantooine:s_aec16b0a", "spacestation_dantooine_land_imperial_abort"}, --On second thought, never mind.
	}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_imperial);

--Finishing landing at Imperial Military Outpost
spacestation_dantooine_land_imperial_complete = ConvoScreen:new {
	id = "spacestation_dantooine_land_imperial_complete",
	leftDialog = "@conversation/station_dantooine:s_28876db2", --Ok, ok... You're cleared for landing.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_imperial_complete);

--Abort landing at Imperial Military Outpost
spacestation_dantooine_land_imperial_abort = ConvoScreen:new {
	id = "spacestation_dantooine_land_imperial_abort",
	leftDialog = "@conversation/station_dantooine:s_737e644a", --Never mind then.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_imperial_abort);

--Land at the Rebel Base
spacestation_dantooine_land_rebel_complete = ConvoScreen:new {
	id = "spacestation_dantooine_land_rebel_complete",
	leftDialog = "@conversation/station_dantooine:s_28876db2", --Ok, ok... You're cleared for landing.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_land_rebel_complete);

-- Repair Main
spacestation_dantooine_repair = ConvoScreen:new {
	id = "spacestation_dantooine_repair",
	leftDialog = "@conversation/station_dantooine:s_b22f6cee", --Well, you sure picked a backwater station to get repairs from. Until our next supply ship comes through, we're sort of limited with that. Just how much of that damage do you need repaired?
	stopConversation = "false",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_repair);

-- Recently repair another player
repair_recent = ConvoScreen:new {
	id = "repair_recent",
	leftDialog = "@conversation/station_dantooine:s_3626cec6", -- 'Fraid we can't manage that, friend. We're all out of supplies 'til the next shipment comes in.
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_bbdda3b3", "delay_upset"}, -- Fine. Bye
		{"@conversation/station_dantooine:s_cb019515", "delay_patient"}, -- I'll wait.
	}
}
spacestation_dantooine_convotemplate:addScreen(repair_recent);

delay_upset = ConvoScreen:new {
	id = "delay_upset",
	leftDialog = "@conversation/station_dantooine:s_fe0697d3", -- Shouldn't be long now. Check back in a few. Or I guess you could land on Dantooine and see if there's a shipwright handy.
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_d6695e83", "delay_no_land"}, -- No thanks.
		{"@conversation/station_dantooine:s_1b800e2e", "spacestation_dantooine_land"}, -- Yes. Let me land.
	}
}
spacestation_dantooine_convotemplate:addScreen(delay_upset);

delay_no_land = ConvoScreen:new {
	id = "delay_no_land",
	leftDialog = "@conversation/station_dantooine:s_9e962746", -- Ok then. Nice talking to you, %NU.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(delay_no_land);

delay_patient = ConvoScreen:new {
	id = "delay_patient",
	leftDialog = "@conversation/station_dantooine:s_49a5815f", -- Sure thing, friend. Maybe you want to land, though? Could get some help on the planet, maybe.
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_7a1a092d", "spacestation_dantooine_land"}, -- Fine. Let me land.
		{"@conversation/station_dantooine:s_d6695e83", "delay_no_land"}, -- No thanks.
	}
}
spacestation_dantooine_convotemplate:addScreen(delay_patient);

spacestation_dantooine_repair_deny = ConvoScreen:new {
	id = "spacestation_dantooine_repair_deny",
	leftDialog = "@conversation/station_dantooine:s_7e303ed8", -- Ok, %NU. Give us a comm if there's anything we can do for you.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_repair_deny);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_dantooine:s_6b2d605a", -- Ok, that shouldn't be too much trouble. We can fix you up just enough for you to get underway again for a mere %DI credits. How's that sound?
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_fef28268", "accept_repair_25"}, -- Do it
		{"@conversation/station_dantooine:s_ca932c28", "deny_repair_25"}, -- Forget it.
	}
}
spacestation_dantooine_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_dantooine:s_5600fd38", -- There you go. You might be limpin' for a while 'til you can afford some more repairs. Just give us a comm if there's anything else we can do for you.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(accept_repair_25);

-- Deny Repair 25
deny_repair_25 = ConvoScreen:new {
	id = "deny_repair_25",
	leftDialog = "@conversation/station_dantooine:s_be24e8c2", -- Your call, friend. Give us a comm if there's something we can help you with.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(deny_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_dantooine:s_2fc5fe5d", -- We can manage that. Do you have the %DI credits to pay for this, though?
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_d70dba34", "accept_repair_50"}, -- Yes
		{"@conversation/station_dantooine:s_4c695dbd", "deny_repair_50"}, -- No
	}
}
spacestation_dantooine_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_dantooine:s_4daeb488", -- Repairs complete! Give us a comm if there's anything else you need.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(accept_repair_50);

-- Deny Repair 50
deny_repair_50 = ConvoScreen:new {
	id = "deny_repair_50",
	leftDialog = "@conversation/station_dantooine:s_f3b73e85", -- I'm afraid I can't help you, then. Give us a comm if there's something we can do for you.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(deny_repair_50);

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_dantooine:s_6bceda29", -- A deal is a deal. Do you have the %DI credits to cover the costs for this? Hey, I never said I would do it for free!
	stopConversation = "false",
	options = {
		{"@conversation/station_dantooine:s_d70dba34", "accept_repair_full"}, -- Yes
		{"@conversation/station_dantooine:s_4c695dbd", "deny_repair_full"}, -- No
	}
}
spacestation_dantooine_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_dantooine:s_4daeb488", -- Repairs complete! Give us a comm if there's anything else you need.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(accept_repair_full);

-- Deny Repair Full
deny_repair_full = ConvoScreen:new {
	id = "deny_repair_full",
	leftDialog = "@conversation/station_dantooine:s_f3b73e85", -- I'm afraid I can't help you, then. Give us a comm if there's something we can do for you.
	stopConversation = "true",
	options = {}
}
spacestation_dantooine_convotemplate:addScreen(deny_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_dantooine_convotemplate", spacestation_dantooine_convotemplate);
