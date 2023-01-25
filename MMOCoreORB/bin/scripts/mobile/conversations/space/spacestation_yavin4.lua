spacestation_yavin4_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_yavin4_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_yavin4_conv_handler",
    screens = {}
}

-- Greeting

spacestation_yavin4_greeting = ConvoScreen:new {
    id = "spacestation_yavin4_greeting",
    leftDialog = "@conversation/station_yavin4:s_a8657d8a",
    stopConversation = "false",
    options = {
        {"@conversation/station_yavin4:s_305434ff", "spacestation_yavin4_land"},
        {"@conversation/station_yavin4:s_6c8ffad8", "spacestation_yavin4_repair"},
    }
}
spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_greeting);

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
    leftDialog = "@conversation/station_yavin4:s_1000a375",
    stopConversation = "false",
    options = {}
}

spacestation_yavin4_convotemplate:addScreen(spacestation_yavin4_repair);

-- Add Template (EOF)

addConversationTemplate("spacestation_yavin4_convotemplate", spacestation_yavin4_convotemplate);
