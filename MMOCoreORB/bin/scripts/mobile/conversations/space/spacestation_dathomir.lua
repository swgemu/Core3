spacestation_dathomir_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_dathomir_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationDathomirConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_dathomir_greeting = ConvoScreen:new {
	id = "spacestation_dathomir_greeting",
	leftDialog = "@conversation/station_dathomir:s_767", -- This is Dathomir Station. What do you need?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_769", "spacestation_dathomir_land"}, -- (Request Permission to Land)
		-- {"@conversation/station_dathomir:s_591", "spacestation_dathomir_repair"}, -- (Request Repairs)
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_greeting);

out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/station_dathomir:s_562", -- Too Far Message
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(out_of_range);

-- Rebel Greeting
spacestation_dathomir_greeting_rebel = ConvoScreen:new {
	id = "spacestation_dathomir_greeting_rebel",
	leftDialog = "@conversation/station_dathomir:s_576", --I don't think you're supposed to be here. Do you have the Imperial authorization code to be in this system?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_578", "spacestation_dathomir_no_code"}, --No.
		{"@conversation/station_dathomir:s_591", "spacestation_dathomir_yes_code"}, --Yes.
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_greeting_rebel);

--Initial "no" on code prompt
spacestation_dathomir_no_code = ConvoScreen:new {
	id = "spacestation_dathomir_no_code",
	leftDialog = "@conversation/station_dathomir:s_581", --I'm sorry. I won't be able to help you. In fact, I should probably call this in...
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_583", "spacestation_dathomir_yes_code"}, --Wait! Yes I do.
		{"@conversation/station_dathomir:s_586", "spacestation_dathomir_leave"}, --Don't do that. I'll leave.
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_no_code);

--Leave the station without providing a code
spacestation_dathomir_leave = ConvoScreen:new {
	id = "spacestation_dathomir_leave",
	leftDialog = "@conversation/station_dathomir:s_588", --Well... I guess it would save me some paperwork to forget I ever saw you. But don't hang around here!
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_leave);

--Yes, I have a code
spacestation_dathomir_yes_code = ConvoScreen:new {
	id = "spacestation_dathomir_yes_code",
	leftDialog = "@conversation/station_dathomir:s_594", --Transmit your authorization code, please.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_598", "spacestation_dathomir_code_no"}, --I don't have one.
		{"@conversation/station_dathomir:s_603", "spacestation_dathomir_code_fake"}, --(Fake it)
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_yes_code);

--Waffled on whether I have a code
spacestation_dathomir_code_no = ConvoScreen:new {
	id = "spacestation_dathomir_code_no",
	leftDialog = "@conversation/station_dathomir:s_601", --Stop playing games, pilot. Do you have the authorization code or not?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_578", "spacestation_dathomir_no_code"}, --No.
		{"@conversation/station_dathomir:s_591", "spacestation_dathomir_yes_code"}, --Yes.
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_code_no);

--Faking an authorization code
spacestation_dathomir_code_fake = ConvoScreen:new {
	id = "spacestation_dathomir_code_fake",
	leftDialog = "@conversation/station_dathomir:s_605", --This code doesn't look right... *sigh* Why doesn't the Empire ever send me the latest codes? This must be new. Okay, how can I help you?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_695", "spacestation_dathomir_land"}, --(Request Permission to Land)
		{"@conversation/station_dathomir:s_698", "spacestation_dathomir_repair"}, --(Request Repairs)
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_code_fake);

--Start conversation to land
spacestation_dathomir_land = ConvoScreen:new {
	id = "spacestation_dathomir_land",
	leftDialog = "@conversation/station_dathomir:s_771", --There are only two outposts on this planet than can accommodate your ship. Where do you want to land?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_773", "spacestation_dathomir_land_trade"}, --Trade Outpost.
		{"@conversation/station_dathomir:s_785", "spacestation_dathomir_land_science"}, --Dathomir Science Outpost.
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_land);

--Land at Trade Outpost
spacestation_dathomir_land_trade = ConvoScreen:new {
	id = "spacestation_dathomir_land_trade",
	leftDialog = "@conversation/station_dathomir:s_775", --You are cleared for landing.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_777", "spacestation_dathomir_land_trade_complete"}, --(Land)
		{"@conversation/station_dathomir:s_781", "spacestation_dathomir_land_trade_abort"}, --Never mind.
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_land_trade);

--Finishing landing at Trade Outpost
spacestation_dathomir_land_trade_complete = ConvoScreen:new {
	id = "spacestation_dathomir_land_trade_complete",
	leftDialog = "@conversation/station_dathomir:s_779", --Be careful down there. This is a dangerous world!
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_land_trade_complete);

--Abort landing at Trade Outpost
spacestation_dathomir_land_trade_abort = ConvoScreen:new {
	id = "spacestation_dathomir_land_trade_abort",
	leftDialog = "@conversation/station_dathomir:s_783", --Acknowledged. Landing clearance aborted. Hail me if I can be of service.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_land_trade_abort);

--Land at Science Outpost
spacestation_dathomir_land_science = ConvoScreen:new {
	id = "spacestation_dathomir_land_science",
	leftDialog = "@conversation/station_dathomir:s_787", --Acknowledged. Dathomir Science Outpost is ready for you to land.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_777", "spacestation_dathomir_land_science_complete"}, --(Land)
		{"@conversation/station_dathomir:s_781", "spacestation_dathomir_land_science_abort"}, --Never mind.
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_land_science);

--Finishing landing at Science Outpost
spacestation_dathomir_land_science_complete = ConvoScreen:new {
	id = "spacestation_dathomir_land_science_complete",
	leftDialog = "@conversation/station_dathomir:s_791", --Good luck.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_land_science_complete);

--Abort landing at Science Outpost
spacestation_dathomir_land_science_abort = ConvoScreen:new {
	id = "spacestation_dathomir_land_science_abort",
	leftDialog = "@conversation/station_dathomir:s_795", --Acknowledged. Landing clearance aborted.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_land_science_abort);

-- Repair Main
spacestation_dathomir_repair = ConvoScreen:new {
	id = "spacestation_dathomir_repair",
	leftDialog = "@conversation/station_dathomir:s_797", --(Request Repairs)
	stopConversation = "false",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_repair);

-- Recently repair another player
repair_recent = ConvoScreen:new {
	id = "repair_recent",
	leftDialog = "@conversation/station_dathomir:s_799", -- Sorry, %TU, but we don't have the supplies on hand to provide you with more repairs. We should be getting more supplies any day now though.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_801", "delay_scrounge"}, -- I can't wait that long!
		{"@conversation/station_dathomir:s_805", "delay_upset"}, -- Arrgh!
	}
}
spacestation_dathomir_convotemplate:addScreen(repair_recent);

delay_scrounge = ConvoScreen:new {
	id = "delay_scrounge",
	leftDialog = "@conversation/station_dathomir:s_803", -- Well, just give me a few minutes... maybe I can scrounge something up...
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(delay_scrounge);

delay_upset = ConvoScreen:new {
	id = "delay_upset",
	leftDialog = "@conversation/station_dathomir:s_807", -- I know, I know. It's terrible being stationed in such a remote locale. We hardly ever get a supply run through here.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_809", "delay_luck"}, -- That's okay. I'll manage somehow.
		{"@conversation/station_dathomir:s_813", "delay_worst_station"}, -- This is the worst station in the galaxy!
	}
}
spacestation_dathomir_convotemplate:addScreen(delay_upset);

delay_luck = ConvoScreen:new {
	id = "delay_luck",
	leftDialog = "@conversation/station_dathomir:s_811", -- Okay, %NU. Good luck!
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(delay_luck);

delay_worst_station = ConvoScreen:new {
	id = "delay_worst_station",
	leftDialog = "@conversation/station_dathomir:s_815", -- I know, I know... but what can I do? I wish I could get a transfer.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_817", "delay_mean_pilot"}, -- You don't deserve a transfer.
		{"@conversation/station_dathomir:s_835", "delay_hang_in_there"}, -- Well, hang in there.
	}
}
spacestation_dathomir_convotemplate:addScreen(delay_worst_station);

delay_hang_in_there = ConvoScreen:new {
	id = "delay_hang_in_there",
	leftDialog = "@conversation/station_dathomir:s_837", -- Thanks, %NU.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(delay_hang_in_there);

delay_mean_pilot = ConvoScreen:new {
	id = "delay_mean_pilot",
	leftDialog = "@conversation/station_dathomir:s_819", -- Well... look... it's not my fault. I wish I could help you, I really do. I just don't have the supplies on hand here.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_821", "delay_liar"}, -- I don't believe you!
		{"@conversation/station_dathomir:s_831", "delay_forget_it"}, -- That's okay. Forget it.
	}
}
spacestation_dathomir_convotemplate:addScreen(delay_mean_pilot);

delay_forget_it = ConvoScreen:new {
	id = "delay_forget_it",
	leftDialog = "@conversation/station_dathomir:s_833", -- I really am sorry, %TU. Very, very sorry.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(delay_forget_it);

delay_liar = ConvoScreen:new {
	id = "delay_liar",
	leftDialog = "@conversation/station_dathomir:s_823", -- But it's true! I mean... maybe I could scrounge something up to get you under way, but... it wouldn't be much.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_825", "delay_scrounge"}, -- Try!
		{"@conversation/station_dathomir:s_827", "delay_forget_it"}, -- Aw, forget it.
	}
}
spacestation_dathomir_convotemplate:addScreen(delay_liar);

spacestation_dathomir_repair_deny = ConvoScreen:new {
	id = "spacestation_dathomir_repair_deny",
	leftDialog = "@conversation/station_dathomir:s_851", -- I don't think there's anything we can do for you, unless you'd like to land and seek repairs on Dathomir.
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_853", "spacestation_dathomir_land"}, -- Yes, I want to land.
		{"@conversation/station_dathomir:s_855", "spacestation_dathomir_good_luck"}, -- No thank you. Never mind.
	}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_repair_deny);

spacestation_dathomir_good_luck = ConvoScreen:new {
	id = "spacestation_dathomir_good_luck",
	leftDialog = "@conversation/station_dathomir:s_857", -- Very well. Good luck.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_good_luck);

-- Repair Some
repair_small = ConvoScreen:new {
	id = "repair_small",
	leftDialog = "@conversation/station_dathomir:s_843", -- I think we can manage to get you underway. There will be a fee of %DI credits for this, though. Is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_845", "accept_repair_25"}, -- Yes.
		{"@conversation/station_dathomir:s_849", "spacestation_dathomir_repair_deny"}, -- No.
	}
}
spacestation_dathomir_convotemplate:addScreen(repair_small);

-- Accept Repair 25
accept_repair_25 = ConvoScreen:new {
	id = "accept_repair_25",
	leftDialog = "@conversation/station_dathomir:s_847", -- Acknowledged. I hope that holds you until you can get back to civilization.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(accept_repair_25);

-- Repair Half
repair_half = ConvoScreen:new {
	id = "repair_half",
	leftDialog = "@conversation/station_dathomir:s_861", -- Repairing half of the damage on your ship shouldn't be a problem. There will be a fee of %DI credits, however. Is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_863", "accept_repair_50"}, -- Yes.
		{"@conversation/station_dathomir:s_867", "spacestation_dathomir_repair_deny"}, -- No.
	}
}
spacestation_dathomir_convotemplate:addScreen(repair_half);

-- Accept Repair 50
accept_repair_50 = ConvoScreen:new {
	id = "accept_repair_50",
	leftDialog = "@conversation/station_dathomir:s_865", -- Repairs Complete! Let me know if there is anything else I can do for you.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(accept_repair_50);

-- Repair Most
repair_most = ConvoScreen:new {
	id = "repair_most",
	leftDialog = "@conversation/station_dathomir:s_879", -- Well, we can repair 75% of your ship's damage for %DI credits, and it looks like you could afford that amount. Would you like to try that instead?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_881", "accept_repair_75"}, -- Yes.
		{"@conversation/station_dathomir:s_885", "spacestation_dathomir_repair_deny"}, -- No thanks.
	}
}
spacestation_dathomir_convotemplate:addScreen(repair_most);

-- Repair Most - Returned when selecting repair full without quests being complete for the station
repair_most_two = ConvoScreen:new {
	id = "repair_most_two",
	leftDialog = "@conversation/station_dathomir:s_889", -- The most we could possibly repair at this station is 75% of your ship's damage. There will be a fee of %DI credits for that repair... is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_891", "accept_repair_75"}, -- Yes.
		{"@conversation/station_dathomir:s_895", "spacestation_dathomir_repair_deny"}, -- No.
	}
}
spacestation_dathomir_convotemplate:addScreen(repair_most_two);

-- Accept Repair Most
accept_repair_75 = ConvoScreen:new {
	id = "accept_repair_75",
	leftDialog = "@conversation/station_dathomir:s_883", -- Repairs Complete! Let me know if there is anything else I can do for you.
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(accept_repair_75);

-- Only given if player has quests completed

-- Repair Full
repair_full = ConvoScreen:new {
	id = "repair_full",
	leftDialog = "@conversation/station_dathomir:s_871", -- Repairing your ship of all damage shouldn't be a problem. There will be a fee of %DI credits, however. Is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/station_dathomir:s_873", "accept_repair_full"}, -- Yes.
		{"@conversation/station_dathomir:s_877", "deny_repair_full"}, -- I can't afford that.
		{"@conversation/station_dathomir:s_887", "spacestation_dathomir_repair_deny"}, -- Never mind.
	}
}
spacestation_dathomir_convotemplate:addScreen(repair_full);

-- Accept Repair Full
accept_repair_full = ConvoScreen:new {
	id = "accept_repair_full",
	leftDialog = "@conversation/station_dathomir:s_865", -- "Repairs Complete! Let me know if there is anything else I can do for you."
	stopConversation = "true",
	options = {}
}
spacestation_dathomir_convotemplate:addScreen(accept_repair_full);

-- Add Template (EOF)
addConversationTemplate("spacestation_dathomir_convotemplate", spacestation_dathomir_convotemplate);
