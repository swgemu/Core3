object_building_military_outpost_cloning_facility_s03 = object_building_military_shared_outpost_cloning_facility_s03:new {
	gameObjectType = 519,
	mapLocationsType1 = 5,
	mapLocationsType2 = 0,
	mapLocationsType3 = 0,
	spawningPoints = { 			
			{ x = 4.42891, z = 0.125266, y = -3.717, ow = -0.701643, ox = 0, oz = 0, oy = 0.712528, cellid = 5 }, 
			{ x = 4.45469, z = 0.125266, y = 1.18026, ow = -0.68668, ox = 0, oz = 0, oy = 0.72696, cellid = 4 },
			{ x = 4.73, z = 0.125266, y = 3.02662, ow = -0.696336, ox = 0, oz = 0, oy = 0.717716, cellid = 4 }
			}, -- { x, z, y, ow, ox, oy, oz, cellid }
	templateType = CLONINGBUILDING
}

ObjectTemplates:addTemplate(object_building_military_outpost_cloning_facility_s03, "object/building/military/outpost_cloning_facility_s03.iff")