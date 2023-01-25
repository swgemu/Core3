spacestation_dathomir_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_dathomir_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_dathomir_conv_handler",
    screens = {}
}

-- Initial Greeting
spacestation_dathomir_greeting = ConvoScreen:new {
    id = "spacestation_dathomir_greeting",
    leftDialog = "@conversation/station_dathomir:s_576", --I don't think you're supposed to be here. Do you have the Imperial authorization code to be in this system?
    stopConversation = "false",
    options = {
        {"@conversation/station_dathomir:s_578", "spacestation_dathomir_no_code"}, --No.
        {"@conversation/station_dathomir:s_591", "spacestation_dathomir_yes_code"}, --Yes.
    }
}
spacestation_dathomir_convotemplate:addScreen(spacestation_dathomir_greeting);

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

-- Add Template (EOF)
addConversationTemplate("spacestation_dathomir_convotemplate", spacestation_dathomir_convotemplate);
