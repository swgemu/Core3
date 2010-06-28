object_building_military_outpost_cloning_facility_s02 = object_building_military_shared_outpost_cloning_facility_s02:new {
	gameObjectType = 519,
	mapLocationsType1 = 5,
	mapLocationsType2 = 0,
	mapLocationsType3 = 0,
	spawningPoints = { 			
			{ x = 4.44727, z = 0.125266, y = -3.80136, ow = 0.707745, ox = 0, oz = 0, oy = -0.706468, cellid = 5 },
			{ x = 4.65395, z = 0.125266, y = 1.49466, ow = -0.699587, ox = 0, oz = 0, oy = 0.714548, cellid = 4 }
			}, -- { x, z, y, ow, ox, oy, oz, cellid }
	templateType = CLONINGBUILDING
}

ObjectTemplates:addTemplate(object_building_military_outpost_cloning_facility_s02, "object/building/military/outpost_cloning_facility_s02.iff")