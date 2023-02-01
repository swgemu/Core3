object_ship_spacestation_dantooine = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_dantooine",
    conversationTemplate = "spacestation_dantooine_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_dantooine.iff",
    conversationMessage = "@conversation/station_dantooine:s_1b90bd5", --Too Far Message
    faction = "civilian",
    type = "spacestation_neutral"
}

ObjectTemplates:addTemplate(object_ship_spacestation_dantooine, "object/ship/spacestation_dantooine.iff")
