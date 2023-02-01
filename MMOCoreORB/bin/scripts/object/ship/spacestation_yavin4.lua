object_ship_spacestation_yavin4 = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_yavin4",
    conversationTemplate = "spacestation_yavin4_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_yavin4.iff",

    -- Too Far Message
    conversationMessage = "@conversation/station_yavin4:s_c3e92bf9"
}

ObjectTemplates:addTemplate(object_ship_spacestation_yavin4, "object/ship/spacestation_yavin4.iff")
