spacestation_endor_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_endor_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationEndorConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_endor_greeting = ConvoScreen:new {
	id = "spacestation_endor_greeting",
	leftDialog = "@conversation/station_endor:s_de3168cf", --Greetings! Have you come to visit the Endor Research Center?
	stopConversation = "false",
	options = {
		{"@conversation/station_endor:s_25759913", "spacestation_endor_land_other"}, --No, but I do want to land on Endor.
		{"@conversation/station_endor:s_2610c442", "spacestation_endor_land_research_proper"}, --Yes! I want to land at the Research Outpost.
		--{"@conversation/station_endor:s_5f4952b7", "spacestation_endor_repair"}, --No, I need repairs.
	}
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_endor:s_e1c14e1d", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(out_of_range);

--Start conversation to land at smuggler's outpost
spacestation_endor_land_other = ConvoScreen:new {
	id = "spacestation_endor_land_other",
	leftDialog = "@conversation/station_endor:s_9eae7799", --I... see... I wasn't aware of another outpost on Endor, but...
	stopConversation = "false",
	options = {
		{"@conversation/station_endor:s_4a43e175", "spacestation_endor_land_other_selection"}, --I'll find a place.
	}
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_land_other);

--Land option including smuggler's outpost
spacestation_endor_land_other_selection = ConvoScreen:new {
	id = "spacestation_endor_land_other_selection",
	leftDialog = "@conversation/station_endor:s_9e0cc5c", --If you say so. You're cleared to land... wherever it is you're going to land.
	stopConversation = "false",
	options = {
		{"@conversation/station_endor:s_695e2019", "spacestation_endor_land_research"}, --(Land at the Research Outpost)
		{"@conversation/station_endor:s_c6f610d3", "spacestation_endor_land_smuggler"}, --(Land at the Smuggler's Outpost)
	}
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_land_other_selection);

-- Land at Research Outpost with the station aware
spacestation_endor_land_research_proper = ConvoScreen:new {
	id = "spacestation_endor_land_research_proper",
	leftDialog = "@conversation/station_endor:s_35417d09", --I'll notify the Research Outpost that you are on your way.
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_land_research_proper);

-- Land at Research Outpost with the station confused
spacestation_endor_land_research = ConvoScreen:new {
	id = "spacestation_endor_land_research",
	leftDialog = "@conversation/station_endor:s_592038e",--Be careful. The Forest Moon of Endor is not very civilized!
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_land_research);

-- Land at the smuggler outpost
spacestation_endor_land_smuggler = ConvoScreen:new {
	id = "spacestation_endor_land_smuggler",
	leftDialog = "@conversation/station_endor:s_75d638d8", --Be careful. Endor is uncivilized.
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_land_smuggler);

-- Repair Main
spacestation_endor_repair = ConvoScreen:new {
	id = "spacestation_endor_repair",
	leftDialog = "@conversation/station_endor:s_2a121119", --Not a problem! It may surprise you to learn that our little research station is well-supplied by the Empire! How much damage do you need repaired?
	stopConversation = "false",
	options = {}
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_repair);

spacestation_endor_repair_deny = ConvoScreen:new {
	id = "spacestation_endor_repair_deny",
	leftDialog = "@conversation/station_endor:s_e8eb7684", -- Ok, bye!
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_repair_deny);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_endor:s_c0d7347d", -- Not a problem. There will be a fee of %DI credits, however. Is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/station_endor:s_d70dba34", "accept_repair_25"}, -- Yes.
		{"@conversation/station_endor:s_4c695dbd", "deny_repair_25"}, -- No.
	}
}
spacestation_endor_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_endor:s_a22bada4", -- Repairs complete. That should get you underway, at least.
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(accept_repair_25);

-- Deny Repair 25
deny_repair_25 = ConvoScreen:new {
	id = "deny_repair_25",
	leftDialog = "@conversation/station_endor:s_9445899b", -- Oh. Well... Ok... Comm me if you need anything.
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(deny_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_endor:s_edc85a49", -- Will do! Repairing half of the damage on your ship will cost %DI credits. Ok?
	stopConversation = "false",
	options = {
		{"@conversation/station_endor:s_895d093", "accept_repair_50"}, -- Ok.
		{"@conversation/station_endor:s_4c695dbd", "deny_repair_50"}, -- No.
	}
}
spacestation_endor_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_endor:s_549ada4b", -- Repairs complete! Thank you for visiting the Forest Moon of Endor Research Station!
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(accept_repair_50);

-- Deny Repair 50
deny_repair_50 = ConvoScreen:new {
	id = "deny_repair_50",
	leftDialog = "@conversation/station_endor:s_685bb895", -- In that case, let me know if there is anything else I can do for you.
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(deny_repair_50);

-- Repair Most
repair_most = ConvoScreen:new {
	id = "repair_most",
	leftDialog = "@conversation/station_endor:s_460bcfda", -- We could repair three-fourths of your ship's damage for %DI credits. Ok?
	stopConversation = "false",
	options = {
		{"@conversation/station_endor:s_ebe2e111", "accept_repair_75"}, -- It's a deal.
		{"@conversation/station_endor:s_4c695dbd", "deny_repair_75"}, -- No.
	}
}
spacestation_endor_convotemplate:addScreen(repair_most);

-- Accept Repair Most
accept_repair_75 = ConvoScreen:new {
	id = "accept_repair_75",
	leftDialog = "@conversation/station_endor:s_c6b82293", -- There you are! Come back any time!
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(accept_repair_75);

-- Deny Repair Most
deny_repair_75 = ConvoScreen:new {
	id = "deny_repair_75",
	leftDialog = "@conversation/station_endor:s_eb2adf47", -- Ok, come back any time.
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(deny_repair_75);

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_endor:s_b68693bb", -- We can completely repair your ship for %DI credits. Is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/station_endor:s_d70dba34", "accept_repair_full"}, -- Yes.
		{"@conversation/station_endor:s_4c695dbd", "deny_repair_full"}, -- No.
	}
}
spacestation_endor_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_endor:s_7bc8f950", --  Your ship has been completely fixed. Thank you for coming.
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(accept_repair_full);

-- Deny Repair Full
deny_repair_full = ConvoScreen:new {
	id = "deny_repair_full",
	leftDialog = "@conversation/station_endor:s_3b68a624", --  I guess that is pretty expensive. Maybe you can get some cheaper repairs somewhere else.
	stopConversation = "true",
	options = {}
}
spacestation_endor_convotemplate:addScreen(deny_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_endor_convotemplate", spacestation_endor_convotemplate);
