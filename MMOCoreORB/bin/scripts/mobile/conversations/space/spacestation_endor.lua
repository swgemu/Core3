spacestation_endor_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_endor_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_endor_conv_handler",
    screens = {}
}

-- Initial Greeting
spacestation_endor_greeting = ConvoScreen:new {
    id = "spacestation_endor_greeting",
    leftDialog = "@conversation/station_endor:s_de3168cf", --Greetings! Have you come to visit the Endor Research Center?
    stopConversation = "false",
    options = {
        {"@conversation/station_endor:s_2610c442", "spacestation_endor_land_research_proper"}, --Yes! I want to land at the Research Outpost.
        {"@conversation/station_endor:s_25759913", "spacestation_endor_land_other"}, --No, but I do want to land on Endor.
        {"@conversation/station_endor:s_5f4952b7", "spacestation_endor_repair"}, --No, I need repairs.
    }
}
spacestation_endor_convotemplate:addScreen(spacestation_endor_greeting);

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

-- Add Template (EOF)
addConversationTemplate("spacestation_endor_convotemplate", spacestation_endor_convotemplate);
