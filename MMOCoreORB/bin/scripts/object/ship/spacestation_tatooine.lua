object_ship_spacestation_tatooine = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_tatooine",
    conversationTemplate = "spacestation_tatooine_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_tatooine.iff",
    conversationMessage = "@conversation/station_tatooine:s_a9ce7ad3", -- Too Far Message
    faction = "civilian",
    type = "spacestation_neutral"
}

ObjectTemplates:addTemplate(object_ship_spacestation_tatooine, "object/ship/spacestation_tatooine.iff")
