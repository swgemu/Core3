object_building_player_city_bank_naboo = object_building_player_city_shared_bank_naboo:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	mapLocationsType1 = 2,
	cityRankRequired = 2,
	abilitiesRequired = {"placeBank"}
}

ObjectTemplates:addTemplate(object_building_player_city_bank_naboo, "object/building/player/city/bank_naboo.iff")

object_building_player_city_cantina_naboo = object_building_player_city_shared_cantina_naboo:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	gameObjectType = 518,
	mapLocationsType1 = 3,
	cityRankRequired = 2
}

ObjectTemplates:addTemplate(object_building_player_city_cantina_naboo, "object/building/player/city/cantina_naboo.iff")

object_building_player_city_cityhall_naboo = object_building_player_city_shared_cityhall_naboo:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	mapLocationsType1 = 50,
	allowedZones = {1,5,6},
	cityRankRequired = 0
}

ObjectTemplates:addTemplate(object_building_player_city_cityhall_naboo, "object/building/player/city/cityhall_naboo.iff")

object_building_player_city_cloning_naboo = object_building_player_city_shared_cloning_naboo:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	gameObjectType = 519,
	mapLocationsType1 = 5,
	allowedZones = {1,5,6},
	cityRankRequired = 3,
	spawningPoints = { {x = -9.6, z = -1.2, y = -6.4, ow = 1, ox = 0, oz = 0, oy = 0, cellid = 4} }, -- { x, z, y, ow, ox, oy, oz, cellid }
	templateType = CLONINGBUILDING,
	abilitiesRequired = {"placeCloningFacility"}
}

ObjectTemplates:addTemplate(object_building_player_city_cloning_naboo, "object/building/player/city/cloning_naboo.iff")

object_building_player_city_hospital_naboo = object_building_player_city_shared_hospital_naboo:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	gameObjectType = 517,
	mapLocationsType1 = 13,
	cityRankRequired = 3
}

ObjectTemplates:addTemplate(object_building_player_city_hospital_naboo, "object/building/player/city/hospital_naboo.iff")

object_building_player_city_shuttleport_naboo = object_building_player_city_shared_shuttleport_naboo:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 4,
	abilitiesRequired = {"placeShuttleport"}
}

ObjectTemplates:addTemplate(object_building_player_city_shuttleport_naboo, "object/building/player/city/shuttleport_naboo.iff")

object_building_player_city_theater_naboo = object_building_player_city_shared_theater_naboo:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	gameObjectType = 524,
	mapLocationsType1 = 51,
	cityRankRequired = 4
}

ObjectTemplates:addTemplate(object_building_player_city_theater_naboo, "object/building/player/city/theater_naboo.iff")

object_building_player_city_garden_naboo_lrg_01 = object_building_player_city_shared_garden_naboo_lrg_01:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 3,
	abilitiesRequired = {"placeLargeGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_lrg_01, "object/building/player/city/garden_naboo_lrg_01.iff")

object_building_player_city_garden_naboo_lrg_02 = object_building_player_city_shared_garden_naboo_lrg_02:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 3,
	abilitiesRequired = {"placeLargeGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_lrg_02, "object/building/player/city/garden_naboo_lrg_02.iff")

object_building_player_city_garden_naboo_lrg_03 = object_building_player_city_shared_garden_naboo_lrg_03:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 3,
	abilitiesRequired = {"placeLargeGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_lrg_03, "object/building/player/city/garden_naboo_lrg_03.iff")

object_building_player_city_garden_naboo_lrg_04 = object_building_player_city_shared_garden_naboo_lrg_04:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 3,
	abilitiesRequired = {"placeLargeGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_lrg_04, "object/building/player/city/garden_naboo_lrg_04.iff")

object_building_player_city_garden_naboo_lrg_05 = object_building_player_city_shared_garden_naboo_lrg_05:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 3,
	abilitiesRequired = {"placeLargeGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_lrg_05, "object/building/player/city/garden_naboo_lrg_05.iff")

object_building_player_city_garden_naboo_med_01 = object_building_player_city_shared_garden_naboo_med_01:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 2,
	abilitiesRequired = {"placeMediumGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_med_01, "object/building/player/city/garden_naboo_med_01.iff")

object_building_player_city_garden_naboo_med_02 = object_building_player_city_shared_garden_naboo_med_02:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 2,
	abilitiesRequired = {"placeMediumGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_med_02, "object/building/player/city/garden_naboo_med_02.iff")

object_building_player_city_garden_naboo_med_03 = object_building_player_city_shared_garden_naboo_med_03:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 2,
	abilitiesRequired = {"placeMediumGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_med_03, "object/building/player/city/garden_naboo_med_03.iff")

object_building_player_city_garden_naboo_med_04 = object_building_player_city_shared_garden_naboo_med_04:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 2,
	abilitiesRequired = {"placeMediumGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_med_04, "object/building/player/city/garden_naboo_med_04.iff")

object_building_player_city_garden_naboo_med_05 = object_building_player_city_shared_garden_naboo_med_05:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 2,
	abilitiesRequired = {"placeMediumGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_med_05, "object/building/player/city/garden_naboo_med_05.iff")

object_building_player_city_garden_naboo_sml_01 = object_building_player_city_shared_garden_naboo_sml_01:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 1,
	abilitiesRequired = {"placeSmallGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_sml_01, "object/building/player/city/garden_naboo_sml_01.iff")

object_building_player_city_garden_naboo_sml_02 = object_building_player_city_shared_garden_naboo_sml_02:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 1,
	abilitiesRequired = {"placeSmallGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_sml_02, "object/building/player/city/garden_naboo_sml_02.iff")

object_building_player_city_garden_naboo_sml_03 = object_building_player_city_shared_garden_naboo_sml_03:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 1,
	abilitiesRequired = {"placeSmallGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_sml_03, "object/building/player/city/garden_naboo_sml_03.iff")

object_building_player_city_garden_naboo_sml_04 = object_building_player_city_shared_garden_naboo_sml_04:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 1,
	abilitiesRequired = {"placeSmallGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_sml_04, "object/building/player/city/garden_naboo_sml_04.iff")

object_building_player_city_garden_naboo_sml_05 = object_building_player_city_shared_garden_naboo_sml_05:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 1,
	abilitiesRequired = {"placeSmallGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_sml_05, "object/building/player/city/garden_naboo_sml_05.iff")

object_building_player_city_garden_naboo_large = object_building_player_city_shared_garden_naboo_large:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,5,6},
	cityRankRequired = 3,
	abilitiesRequired = {"placeLargeGarden"}
}

ObjectTemplates:addTemplate(object_building_player_city_garden_naboo_large, "object/building/player/city/garden_naboo_large.iff")
