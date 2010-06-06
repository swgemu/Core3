object_building_player_player_guildhall_tatooine_style_01 = object_building_player_shared_player_guildhall_tatooine_style_01:new {
	lotSize = 5,
	baseMaintenanceRate = 100,
	allowedZones = {1,4,8},
	
	--Terminal Location is cell#, x, z, y, qx, qy, qz, qw
	terminalLocation = {2, 9.13004, 1.49609, 6.3587, 0, 0.707107, 0, 0.707107},
	
	--Elevator Terminals format is template_path, cell#, x, z, y, qx, qy, qz, qw, dz - where dz is the delta z.
	elevatorTerminals = {
			"", 0, 0, 0, 0, 0, 0, 0, 1, 0,
			"", 0, 0, 0, 0, 0, 0, 0, 1, 0
	}
}

ObjectTemplates:addTemplate(object_building_player_player_guildhall_tatooine_style_01, "object/building/player/player_guildhall_tatooine_style_01.iff")

object_building_player_player_garage_tatooine_style_01 = object_building_player_shared_player_garage_tatooine_style_01:new {
	lotSize = 0,
	baseMaintenanceRate = 0,
	allowedZones = {1,4,8}
}

ObjectTemplates:addTemplate(object_building_player_player_garage_tatooine_style_01, "object/building/player/player_garage_tatooine_style_01.iff")

object_building_player_player_guildhall_tatooine_style_02 = object_building_player_shared_player_guildhall_tatooine_style_02:new {
	lotSize = 5,
	baseMaintenanceRate = 100,
	allowedZones = {1,4,8}
}

ObjectTemplates:addTemplate(object_building_player_player_guildhall_tatooine_style_02, "object/building/player/player_guildhall_tatooine_style_02.iff")

object_building_player_player_house_tatooine_large_style_01 = object_building_player_shared_player_house_tatooine_large_style_01:new {
	lotSize = 5,
	baseMaintenanceRate = 50,
	allowedZones = {1,4,8}
}

ObjectTemplates:addTemplate(object_building_player_player_house_tatooine_large_style_01, "object/building/player/player_house_tatooine_large_style_01.iff")

object_building_player_player_house_tatooine_medium_style_01 = object_building_player_shared_player_house_tatooine_medium_style_01:new {
	lotSize = 2,
	baseMaintenanceRate = 34,
	allowedZones = {1,4,8}
}

ObjectTemplates:addTemplate(object_building_player_player_house_tatooine_medium_style_01, "object/building/player/player_house_tatooine_medium_style_01.iff")

object_building_player_player_house_tatooine_small_style_01 = object_building_player_shared_player_house_tatooine_small_style_01:new {
	lotSize = 2,
	baseMaintenanceRate = 16,
	allowedZones = {1,4,8}
}

ObjectTemplates:addTemplate(object_building_player_player_house_tatooine_small_style_01, "object/building/player/player_house_tatooine_small_style_01.iff")

object_building_player_player_house_tatooine_small_style_02 = object_building_player_shared_player_house_tatooine_small_style_02:new {
	lotSize = 2,
	baseMaintenanceRate = 16,
	allowedZones = {1,4,8}
}

ObjectTemplates:addTemplate(object_building_player_player_house_tatooine_small_style_02, "object/building/player/player_house_tatooine_small_style_02.iff")
