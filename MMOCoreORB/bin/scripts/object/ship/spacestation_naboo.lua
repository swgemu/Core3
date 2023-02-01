object_ship_spacestation_naboo = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_naboo",
    conversationTemplate = "spacestation_naboo_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_naboo.iff",
    conversationMessage = "@conversation/station_naboo:s_1951f1c1", -- Too Far Message
    faction = "civilian",
    type = "spacestation_neutral"
}

ObjectTemplates:addTemplate(object_ship_spacestation_naboo, "object/ship/spacestation_naboo.iff")
