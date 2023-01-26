object_ship_spacestation_talus = object_ship_shared_spacestation_neutral:new {
    objectName = "@clientpoi_n:station_talus",
    conversationTemplate = "spacestation_talus_convotemplate",
    conversationMobile = "object/mobile/shared_space_comm_station_talus.iff"
}

ObjectTemplates:addTemplate(object_ship_spacestation_talus, "object/ship/spacestation_talus.iff")
