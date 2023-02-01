object_ship_spacestation_rori = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_rori",
    conversationTemplate = "spacestation_rori_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_rori.iff",

    -- Too Far Message
    conversationMessage = "@conversation/station_rori:s_201"
}

ObjectTemplates:addTemplate(object_ship_spacestation_rori, "object/ship/spacestation_rori.iff")
