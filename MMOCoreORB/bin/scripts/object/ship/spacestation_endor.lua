object_ship_spacestation_endor = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_endor",
    conversationTemplate = "spacestation_endor_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_endor.iff",
    conversationMessage = "@conversation/station_endor:s_e1c14e1d", -- Too Far Message
    faction = "civilian",
    type = "spacestation_neutral"
}

ObjectTemplates:addTemplate(object_ship_spacestation_endor, "object/ship/spacestation_endor.iff")
