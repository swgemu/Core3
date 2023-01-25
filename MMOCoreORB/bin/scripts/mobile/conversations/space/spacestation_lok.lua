spacestation_lok_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_lok_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_lok_conv_handler",
    screens = {}
}

-- Initial Greeting
spacestation_lok_greeting = ConvoScreen:new {
    id = "spacestation_lok_greeting",
    leftDialog = "@conversation/station_lok:s_bc62d0fb", --Greets to you! And welcome to the Lok Station. What are you needing today?
    stopConversation = "false",
    options = {
        {"@conversation/station_lok:s_305434ff", "spacestation_lok_land"}, --I want to land.
        {"@conversation/station_lok:s_6c8ffad8", "spacestation_lok_repair"}, --I need repairs.
    }
}
spacestation_lok_convotemplate:addScreen(spacestation_lok_greeting);

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

-- Add Template (EOF)
addConversationTemplate("spacestation_lok_convotemplate", spacestation_lok_convotemplate);
