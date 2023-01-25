spacestation_dantooine_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_dantooine_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_dantooine_conv_handler",
    screens = {}
}

-- Initial Greeting
spacestation_dantooine_greeting = ConvoScreen:new {
    id = "spacestation_dantooine_greeting",
    leftDialog = "@conversation/station_dantooine:s_73a08149", --This is Dantooine Station. What can I do for ya?
    stopConversation = "false",
    options = {
        {"@conversation/station_dantooine:s_75f22c97", "spacestation_dantooine_land_prelude"}, --I want to land on Dantooine.
        {"@conversation/station_dantooine:s_54c04765", "spacestation_dantooine_repair"}, --I need repairs!
    }
}
spacestation_dantooine_convotemplate:addScreen(spacestation_dantooine_greeting);

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

-- Add Template (EOF)
addConversationTemplate("spacestation_dantooine_convotemplate", spacestation_dantooine_convotemplate);
