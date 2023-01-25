spacestation_tatooine_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_tatooine_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_tatooine_conv_handler",
    screens = {}
}

--Greeting
spacestation_tatooine_greeting = ConvoScreen:new {
    id = "spacestation_tatooine_greeting",
    leftDialog = "@conversation/station_tatooine:s_a9152d31", --Hey, you! What do you want?
    stopConversation = "false",
    options = {
        {"@conversation/station_tatooine:s_5984746e", "spacestation_tatooine_land"}, --I want to land on Tatooine.
        {"@conversation/station_tatooine:s_6c8ffad8", "spacestation_tatooine_repair"}, --I need repairs.
    }
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_greeting);

--Land Main Menu
spacestation_tatooine_land = ConvoScreen:new {
    id = "spacestation_tatooine_land",
    leftDialog = "@conversation/station_tatooine:s_83bace61", --Yeah? Anywhere in particular or were you just gonna set down in the desert?
    stopConversation = "false",
    options = {
        {"@conversation/station_tatooine:s_43d2bcbe", "spacestation_tatooine_land_bestine"}, --Bestine Starport.
        {"@conversation/station_tatooine:s_ccbc6cf4", "spacestation_tatooine_land_eisley"}, --Mos Eisley Starport.
        {"@conversation/station_tatooine:s_75ba8830", "spacestation_tatooine_land_espa"}, --Mos Espa Starport.
        {"@conversation/station_tatooine:s_69ffeefe", "spacestation_tatooine_land_entha"}, --Mos Entha Starport.
    }
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land);

--Bestine Landing Main
spacestation_tatooine_land_bestine = ConvoScreen:new {
    id = "spacestation_tatooine_land_bestine",
    leftDialog = "@conversation/station_tatooine:s_ea06a410", --Ok, you're clear to land.
    stopConversation = "false",
    options = {
        {"@conversation/station_tatooine:s_c4682ea6", "spacestation_tatooine_land_bestine_complete"}, --Thanks!
        {"@conversation/station_tatooine:s_4dc4840b", "spacestation_tatooine_land_bestine_abort"}, --Wait, I changed my mind.
    }
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_bestine);

--Bestine Landing Complete
spacestation_tatooine_land_bestine_complete = ConvoScreen:new {
    id = "spacestation_tatooine_land_bestine_complete",
    leftDialog = "@conversation/station_tatooine:s_333ffc01", --Yeah, yeah.  Tatooine station, out!
    stopConversation = "true",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_bestine_complete);

--Bestine Landing Abort
spacestation_tatooine_land_bestine_abort = ConvoScreen:new {
    id = "spacestation_tatooine_land_bestine_abort",
    leftDialog = "@conversation/station_tatooine:s_43b6dcb9", --I'm too busy to wait.  Let me know when you figure out what it is you want.
    stopConversation = "true",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_bestine_abort);

--Eisley Landing Main
spacestation_tatooine_land_eisley = ConvoScreen:new {
    id = "spacestation_tatooine_land_eisley",
    leftDialog = "@conversation/station_tatooine:s_6ff46cdd", --Go ahead and land. No one there cares who comes or goes.
    stopConversation = "false",
    options = {
        {"@conversation/station_tatooine:s_b9b27823", "spacestation_tatooine_land_eisley_complete"}, --Thank you.
        {"@conversation/station_tatooine:s_d195782", "spacestation_tatooine_land_eisley_abort"}, --Wait! I changed my mind.
    }
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_eisley);

--Eisley Landing
spacestation_tatooine_land_eisley_complete = ConvoScreen:new {
    id = "spacestation_tatooine_land_eisley_complete",
    leftDialog = "@conversation/station_tatooine:s_4650b19f", --Watch your back.
    stopConversation = "true",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_eisley_complete);

--Eisley Landing Abort
spacestation_tatooine_land_eisley_abort = ConvoScreen:new {
    id = "spacestation_tatooine_land_eisley_abort",
    leftDialog = "@conversation/station_tatooine:s_1ba81e14", --Fine by me. Stay in orbit and rot. Tatooine Station, out!.
    stopConversation = "true",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_eisley_abort);

--Espa Landing Main
spacestation_tatooine_land_espa = ConvoScreen:new {
    id = "spacestation_tatooine_land_espa",
    leftDialog = "@conversation/station_tatooine:s_ea06a410", --Ok, you're clear to land.
    stopConversation = "false",
    options = {
        {"@conversation/station_tatooine:s_895d093", "spacestation_tatooine_land_espa_complete"}, --Ok.
        {"@conversation/station_tatooine:s_e1ef9209", "spacestation_tatooine_land_espa_abort"}, --Wait, I don't want to land there.
    }
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_espa);

--Espa Landing Complete
spacestation_tatooine_land_espa_complete = ConvoScreen:new {
    id = "spacestation_tatooine_land_espa_complete",
    leftDialog = "@conversation/station_tatooine:s_b729c637", --Land in the Dune Sea for all I care. Tatooine Station, out!
    stopConversation = "true",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_espa_complete);

--Espa Landing Abort
spacestation_tatooine_land_espa_abort = ConvoScreen:new {
    id = "spacestation_tatooine_land_espa_abort",
    leftDialog = "@conversation/station_tatooine:s_2a7858d1", --Well, hail me when you figure out what it is you need.
    stopConversation = "true",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_espa_abort);

--Entha Landing Main
spacestation_tatooine_land_entha = ConvoScreen:new {
    id = "spacestation_tatooine_land_entha",
    leftDialog = "@conversation/station_tatooine:s_ea06a410", --Ok, you're clear to land.
    stopConversation = "false",
    options = {
        {"@conversation/station_tatooine:s_895d093", "spacestation_tatooine_land_entha_complete"}, --Ok.
        {"@conversation/station_tatooine:s_e76d5278", "spacestation_tatooine_land_entha_abort"}, --On second thought, I don't want to land there.
    }
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_entha);

--Entha Landing Complete
spacestation_tatooine_land_entha_complete = ConvoScreen:new {
    id = "spacestation_tatooine_land_entha_complete",
    leftDialog = "@conversation/station_tatooine:s_c1013aa7", --Whatever.
    stopConversation = "true",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_entha_complete);

--Entha Landing Abort
spacestation_tatooine_land_entha_abort = ConvoScreen:new {
    id = "spacestation_tatooine_land_entha_abort",
    leftDialog = "@conversation/station_tatooine:s_82f403b1", --I don't have time for this, come back when you have made up your mind.
    stopConversation = "true",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_land_entha_abort);

-- Repair Main
spacestation_tatooine_repair = ConvoScreen:new {
    id = "spacestation_tatooine_repair",
    leftDialog = "@conversation/station_tatooine:s_35221afe", --So I noticed. Looks like you bit off a little more than you could chew. So what do want: a complete overhaul or just enough repairs to put you back on your way?
    stopConversation = "false",
    options = {}
}
spacestation_tatooine_convotemplate:addScreen(spacestation_tatooine_repair);


-- Add Template (EOF)
addConversationTemplate("spacestation_tatooine_convotemplate", spacestation_tatooine_convotemplate);
