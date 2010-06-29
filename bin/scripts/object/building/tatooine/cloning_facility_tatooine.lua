object_building_tatooine_cloning_facility_tatooine = object_building_tatooine_shared_cloning_facility_tatooine:new {
	gameObjectType = 519,
	mapLocationsType1 = 5,
	mapLocationsType2 = 0,
	mapLocationsType3 = 0,
	spawningPoints = { 			
			{ x = -16.6514, z = -4.29167, y = -10.4976, ow = 0.704753, ox = 0, oz = 0, oy = 0.709453, cellid = 4 }, 
			{ x = -16.5965, z = -4.29167, y = -14.1652, ow = 0.692575, ox = 0, oz = 0, oy = 0.721346, cellid = 4 }, 
			{ x = 16.5771, z = -4.29167, y = -14.2091, ow = -0.702231, ox = 0, oz = 0, oy = 0.71195, cellid = 4 }, 
			{ x = 16.6876, z = -4.29167, y = -10.5391, ow = 0.716877, ox = 0, oz = 0, oy = -0.6972, cellid = 4 }, 
			{ x = 6.32992, z = -4.79167, y = 0.613332, ow = 0.00405023, ox = 0, oz = 0, oy = 0.999992, cellid = 4 }, 
			{ x = 1.58067, z = -4.79167, y = 1.00877, ow = -0.143217, ox = 0, oz = 0, oy = 0.989691, cellid = 4 }, 
			{ x = -2.84125, z = -4.79167, y = 1.26153, ow = 0.999366, ox = 0, oz = 0, oy = -0.0356012, cellid = 4 }
			}, -- { x, z, y, ow, ox, oy, oz, cellid }
	templateType = CLONINGBUILDING
}

ObjectTemplates:addTemplate(object_building_tatooine_cloning_facility_tatooine, "object/building/tatooine/cloning_facility_tatooine.iff")