spacestation_rori_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_rori_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_rori_conv_handler",
    screens = {}
}

-- Initial Greeting
spacestation_rori_greeting = ConvoScreen:new {
    id = "spacestation_rori_greeting",
    leftDialog = "@conversation/station_rori:s_331", --Ello, boyos! Yous wantin ta speedaway down ta Roritowns? Or yousa been crunchen?
    stopConversation = "false",
    options = {
        {"@conversation/station_rori:s_327", "spacestation_rori_land"}, --I want to land.
        {"@conversation/station_rori:s_329", "spacestation_rori_repair"}, --I need repairs.
    }
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_greeting);

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
    leftDialog = "@conversation/station_rori:s_375", --Oie Boie! You been crunchen, huh? Wesa gonna fix you up!
    stopConversation = "false",
    options = {}
}
spacestation_rori_convotemplate:addScreen(spacestation_rori_repair);

-- Add Template (EOF)
addConversationTemplate("spacestation_rori_convotemplate", spacestation_rori_convotemplate);
