spacestation_naboo_convotemplate = ConvoTemplate:new {
    initialScreen = "spacestation_naboo_greeting",
    templateType = "Lua",
    luaClassHandler = "spacestation_naboo_conv_handler",
    screens = {}
}

-- Initial Greeting
spacestation_naboo_greeting = ConvoScreen:new {
    id = "spacestation_naboo_greeting",
    leftDialog = "@conversation/station_naboo:s_decdd151", --You have entered Naboo space, under the protection of the Royal Security Forces. Please identify yourself and your reason for visiting Naboo.
    stopConversation = "false",
    options = {
        {"@conversation/station_naboo:s_cebd107d", "spacestation_naboo_land"}, --(Request Permission to Land)
        {"@conversation/station_naboo:s_c358d041", "spacestation_naboo_repair"}, --(Request Repairs)
    }
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_greeting);

--Start conversation to land
spacestation_naboo_land = ConvoScreen:new {
    id = "spacestation_naboo_land",
    leftDialog = "@conversation/station_naboo:s_4bb1f207", --Acknowledged, %TU. Please transmit your destination for flight clearance.
    stopConversation = "false",
    options = {
        {"@conversation/station_naboo:s_c42b6203", "spacestation_naboo_land_theed"}, --Theed Starport.
        {"@conversation/station_naboo:s_8845528b", "spacestation_naboo_land_kaadara"}, --Kaadara Starport.
        {"@conversation/station_naboo:s_a716a9c7", "spacestation_naboo_land_keren"}, --Keren Starport.
        {"@conversation/station_naboo:s_2f99890c", "spacestation_naboo_land_moenia"}, --Moenia Starport.
    }
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land);

--Land at Theed
spacestation_naboo_land_theed = ConvoScreen:new {
    id = "spacestation_naboo_land_theed",
    leftDialog = "@conversation/station_naboo:s_8e61aac7", --Acknowledged, %TU. Theed Starport is awaiting your arrival.
    stopConversation = "false",
    options = {
        {"@conversation/station_naboo:s_2dc4697a", "spacestation_naboo_land_theed_complete"}, --(Land)
        {"@conversation/station_naboo:s_f148786f", "spacestation_naboo_land_theed_abort"}, --Cancel request to land.
    }
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_theed);

--Finishing landing at Theed
spacestation_naboo_land_theed_complete = ConvoScreen:new {
    id = "spacestation_naboo_land_theed_complete",
    leftDialog = "@conversation/station_naboo:s_390e6f9a", --Enjoy your stay in Theed, %NU.
    stopConversation = "true",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_theed_complete);

--Abort landing at Theed
spacestation_naboo_land_theed_abort = ConvoScreen:new {
    id = "spacestation_naboo_land_theed_abort",
    leftDialog = "@conversation/station_naboo:s_c6aaa6b3", --Of course, Sir! Let me know when you are ready.
    stopConversation = "true",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_theed_abort);

--Land at Kaadara
spacestation_naboo_land_kaadara = ConvoScreen:new {
    id = "spacestation_naboo_land_kaadara",
    leftDialog = "@conversation/station_naboo:s_14ed557a", --Acknowledged, %TU. Kaadara Starport is awaiting your arrival.
    stopConversation = "false",
    options = {
        {"@conversation/station_naboo:s_2dc4697a", "spacestation_naboo_land_kaadara_complete"}, --(Land)
        {"@conversation/station_naboo:s_f148786f", "spacestation_naboo_land_kaadara_abort"}, --Cancel request to land.
    }
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_kaadara);

--Finishing landing at Kaadara
spacestation_naboo_land_kaadara_complete = ConvoScreen:new {
    id = "spacestation_naboo_land_kaadara_complete",
    leftDialog = "@conversation/station_naboo:s_c9361653", --Enjoy your stay in Kaadara, %NU.
    stopConversation = "true",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_kaadara_complete);

--Abort landing at Kaadara
spacestation_naboo_land_kaadara_abort = ConvoScreen:new {
    id = "spacestation_naboo_land_kaadara_abort",
    leftDialog = "@conversation/station_naboo:s_c6aaa6b3", --Of course, Sir! Let me know when you are ready.
    stopConversation = "true",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_kaadara_abort);

--Land at Keren
spacestation_naboo_land_keren = ConvoScreen:new {
    id = "spacestation_naboo_land_keren",
    leftDialog = "@conversation/station_naboo:s_cfbc1584", --Acknowledged, %TU. Keren Starport is awaiting your arrival.
    stopConversation = "false",
    options = {
        {"@conversation/station_naboo:s_2dc4697a", "spacestation_naboo_land_keren_complete"}, --(Land)
        {"@conversation/station_naboo:s_f148786f", "spacestation_naboo_land_keren_abort"}, --Cancel request to land.
    }
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_keren);

--Finishing landing at Keren
spacestation_naboo_land_keren_complete = ConvoScreen:new {
    id = "spacestation_naboo_land_keren_complete",
    leftDialog = "@conversation/station_naboo:s_13eddc62", --Enjoy your stay in Keren, %NU.
    stopConversation = "true",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_keren_complete);

--Abort landing at Keren
spacestation_naboo_land_keren_abort = ConvoScreen:new {
    id = "spacestation_naboo_land_keren_abort",
    leftDialog = "@conversation/station_naboo:s_c6aaa6b3", --Of course, Sir! Let me know when you are ready.
    stopConversation = "true",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_keren_abort);

--Land at Moenia
spacestation_naboo_land_moenia = ConvoScreen:new {
    id = "spacestation_naboo_land_moenia",
    leftDialog = "@conversation/station_naboo:s_7cffc9b4", --Acknowledged, %TU. Moenia Starport is awaiting your arrival.
    stopConversation = "false",
    options = {
        {"@conversation/station_naboo:s_2dc4697a", "spacestation_naboo_land_moenia_complete"}, --(Land)
        {"@conversation/station_naboo:s_f148786f", "spacestation_naboo_land_moenia_abort"}, --Cancel request to land.
    }
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_moenia);

--Finishing landing at Moenia
spacestation_naboo_land_moenia_complete = ConvoScreen:new {
    id = "spacestation_naboo_land_moenia_complete",
    leftDialog = "@conversation/station_naboo:s_41f82cf5", --Enjoy your stay in Moenia, %NU.
    stopConversation = "true",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_moenia_complete);

--Abort landing at Moenia
spacestation_naboo_land_moenia_abort = ConvoScreen:new {
    id = "spacestation_naboo_land_moenia_abort",
    leftDialog = "@conversation/station_naboo:s_c6aaa6b3", --Of course, Sir! Let me know when you are ready.
    stopConversation = "true",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_land_moenia_abort);

-- Repair Main
spacestation_naboo_repair = ConvoScreen:new {
    id = "spacestation_naboo_repair",
    leftDialog = "@conversation/station_naboo:s_4b9c311", --Acknowledged, %TU. How much of the damage to your ship do you want to be repaired at this time?
    stopConversation = "false",
    options = {}
}
spacestation_naboo_convotemplate:addScreen(spacestation_naboo_repair);

-- Add Template (EOF)
addConversationTemplate("spacestation_naboo_convotemplate", spacestation_naboo_convotemplate);
