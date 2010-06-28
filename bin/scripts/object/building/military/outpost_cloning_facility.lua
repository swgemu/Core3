object_building_military_outpost_cloning_facility = object_building_military_shared_outpost_cloning_facility:new {
	gameObjectType = 519,
	mapLocationsType1 = 5,
	mapLocationsType2 = 0,
	mapLocationsType3 = 0,
	spawningPoints = { 
			{ x = 3.2408, z = 0.125266, y = -3.59732, ow = -0.706572, ox = 0, oz = 0, oy = 0.707641, cellid = 5 }
			}, -- { x, z, y, ow, ox, oy, oz, cellid }
	templateType = CLONINGBUILDING	
}

ObjectTemplates:addTemplate(object_building_military_outpost_cloning_facility, "object/building/military/outpost_cloning_facility.iff")