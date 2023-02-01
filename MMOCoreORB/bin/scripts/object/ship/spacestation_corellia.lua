object_ship_spacestation_corellia = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_corellia",
    conversationTemplate = "spacestation_corellia_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_corellia.iff",
    --Too Far Message
    conversationMessage = "@conversation/station_corellia:s_bf5b2480"
}

ObjectTemplates:addTemplate(object_ship_spacestation_corellia, "object/ship/spacestation_corellia.iff")
