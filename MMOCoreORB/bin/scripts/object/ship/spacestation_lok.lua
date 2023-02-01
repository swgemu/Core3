object_ship_spacestation_lok = object_ship_shared_spacestation_neutral:new {
    objectName = "@space/space_mobile_type:station_lok",
    conversationTemplate = "spacestation_lok_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_lok.iff",
    conversationMessage = "@conversation/station_lok:s_5d8ae855", -- Too Far Message
    faction = "civilian",
    type = "spacestation_neutral"
}

ObjectTemplates:addTemplate(object_ship_spacestation_lok, "object/ship/spacestation_lok.iff")
