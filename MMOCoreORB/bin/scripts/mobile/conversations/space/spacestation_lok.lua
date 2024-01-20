spacestation_lok_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_lok_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationLokConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_lok_greeting = ConvoScreen:new {
	id = "spacestation_lok_greeting",
	leftDialog = "@conversation/station_lok:s_bc62d0fb", --Greets to you! And welcome to the Lok Station. What are you needing today?
	stopConversation = "false",
	options = {
		{"@conversation/station_lok:s_305434ff", "spacestation_lok_land"}, --I want to land.
		--{"@conversation/station_lok:s_6c8ffad8", "spacestation_lok_repair"}, --I need repairs.
	}
}
spacestation_lok_convotemplate:addScreen(spacestation_lok_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_lok:s_5d8ae855", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(out_of_range);

--Start conversation to land
spacestation_lok_land = ConvoScreen:new {
	id = "spacestation_lok_land",
	leftDialog = "@conversation/station_lok:s_35f718b7", --Well, there's only one starport on Lok that can handle that ship of yours... So will it be Nym's Stronghold for you then?
	stopConversation = "false",
	options = {
		{"@conversation/station_lok:s_d70dba34", "spacestation_lok_land_nym_complete"}, --Yes.
		{"@conversation/station_lok:s_4c695dbd", "spacestation_lok_land_nym_abort"}, --No.
	}
}
spacestation_lok_convotemplate:addScreen(spacestation_lok_land);

--Finishing landing at Nym's
spacestation_lok_land_nym_complete = ConvoScreen:new {
	id = "spacestation_lok_land_nym_complete",
	leftDialog = "@conversation/station_lok:s_94d99aa4", --I would alert the authorities of your arrival... if there were any!
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(spacestation_lok_land_nym_complete);

--Abort landing at Nym's
spacestation_lok_land_nym_abort = ConvoScreen:new {
	id = "spacestation_lok_land_nym_abort",
	leftDialog = "@conversation/station_lok:s_96576ff4", --It seems there's nothing I can do for you then. Off you go!
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(spacestation_lok_land_nym_abort);

-- Repair Main
spacestation_lok_repair = ConvoScreen:new {
	id = "spacestation_lok_repair",
	leftDialog = "@conversation/station_lok:s_3538339", --I can see that! I mean, I wasn't going to say anything, but since you mentioned it... Anyway, we've got all the necessary equipment to fix you right up! Want a complete repair job?
	stopConversation = "false",
	options = {}
}
spacestation_lok_convotemplate:addScreen(spacestation_lok_repair);

spacestation_lok_repair_deny = ConvoScreen:new {
	id = "spacestation_lok_repair_deny",
	leftDialog = "@conversation/station_lok:s_f33a826f", -- Yeah, you're not so badly damaged after all, I s'pose. If you're on your way, then I'll be getting back to work.
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(spacestation_lok_repair_deny);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_lok:s_d38dd40", -- Right! Money's a bit tight, isn't it? How about we get you running for %DI credits?
	stopConversation = "false",
	options = {
		{"@conversation/station_lok:s_ebe2e111", "accept_repair_25"}, -- It's a deal.
		{"@conversation/station_lok:s_d6695e83", "deny_repair_25"}, -- No thanks.
	}
}
spacestation_lok_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_lok:s_60460c5", -- And here's your repairs! That ought to allow you to limp back home, anyway.
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(accept_repair_25);

-- Deny Repair 25
deny_repair_25 = ConvoScreen:new {
	id = "deny_repair_25",
	leftDialog = "@conversation/station_lok:s_bc1b6f03", -- Ok. I guess I'd better get back to work.
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(deny_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_lok:s_360058b6", -- Easy to say, easy to do! And a bargain at %DI credits, don't you agree?
	stopConversation = "false",
	options = {
		{"@conversation/station_lok:s_d70dba34", "accept_repair_50"}, -- Yes.
		{"@conversation/station_lok:s_4c695dbd", "deny_repair_50"}, -- No.
	}
}
spacestation_lok_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_lok:s_a6054d56", -- Repairs complete! How's that for quick work? Stop by again if you need anything else!
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(accept_repair_50);

-- Deny Repair 50
deny_repair_50 = ConvoScreen:new {
	id = "deny_repair_50",
	leftDialog = "@conversation/station_lok:s_8a98e9e7", -- Well, what do you know about the cost of repairing a ship as damaged as yours, anyway? Ask around and you'll see that was a fair price. Then you'll be back, won't you?
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(deny_repair_50);

-- Repair Most
repair_most = ConvoScreen:new {
	id = "repair_most",
	leftDialog = "@conversation/station_lok:s_d47aa2c4", -- How does this sound? We'll take care of three-fourths of the damage, and you take care of us to the tune of... say... %DI credits. Sounds good?
	stopConversation = "false",
	options = {
		{"@conversation/station_lok:s_d70dba34", "accept_repair_75"}, -- Yes.
		{"@conversation/station_lok:s_4c695dbd", "deny_repair_75"}, -- No.
	}
}
spacestation_lok_convotemplate:addScreen(repair_most);

-- Accept Repair Most
accept_repair_75 = ConvoScreen:new {
	id = "accept_repair_75",
	leftDialog = "@conversation/station_lok:s_a6054d56", -- Repairs complete! How's that for quick work? Stop by again if you need anything else!
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(accept_repair_75);

-- Deny Repair Most
deny_repair_75 = ConvoScreen:new {
	id = "deny_repair_75",
	leftDialog = "@conversation/station_lok:s_8a98e9e7", -- Well, what do you know about the cost of repairing a ship as damaged as yours, anyway? Ask around and you'll see that was a fair price. Then you'll be back, won't you?
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(deny_repair_75);

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_lok:s_3e88ac8b", -- Ha ha! That's the spirit! No sense limping around in a damaged heap, right! This will only cost you %DI credits, and a better price you'll never find!
	stopConversation = "false",
	options = {
		{"@conversation/station_lok:s_fef28268", "accept_repair_full"}, -- Do it.
		{"@conversation/station_lok:s_d6695e83", "deny_repair_full"}, -- No thanks.
	}
}
spacestation_lok_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_lok:s_ce3f3ff6", --  Your ship has been completely fixed! And that work is guaranteed for life... barring any sort of combat-related damage, or normal wear and tear, or acts of the Force and the like. Come see us again if you have problems at all!
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(accept_repair_full);

-- Deny Repair Full
deny_repair_full = ConvoScreen:new {
	id = "deny_repair_full",
	leftDialog = "@conversation/station_lok:s_bc1b6f03", -- Ok. I guess I'd better get back to work.
	stopConversation = "true",
	options = {}
}
spacestation_lok_convotemplate:addScreen(deny_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_lok_convotemplate", spacestation_lok_convotemplate);
