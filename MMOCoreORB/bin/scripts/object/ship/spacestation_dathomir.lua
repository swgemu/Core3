object_ship_spacestation_dathomir = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_dathomir",
    conversationTemplate = "spacestation_dathomir_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_dathomir.iff",
    conversationMessage = "@conversation/station_dathomir:s_562", -- Too Far Message
    faction = "civilian",
    type = "spacestation_neutral"
}

ObjectTemplates:addTemplate(object_ship_spacestation_dathomir, "object/ship/spacestation_dathomir.iff")
