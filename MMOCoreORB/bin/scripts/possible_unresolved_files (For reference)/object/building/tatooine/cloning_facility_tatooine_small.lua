object_building_tatooine_cloning_facility_tatooine_small = object_building_tatooine_shared_cloning_facility_tatooine_small:new {
	gameObjectType = 519,
	mapLocationsType1 = 5,
	mapLocationsType2 = 0,
	mapLocationsType3 = 0,
	spawningPoints = { 
			-- Needs Revisited, Needs elevator terms.
			{ x = 0.445015, z = 0.271775, y = 1.39199, ow = 0.707176, ox = 0, oz = 0, oy = 0.707038, cellid = 9 }
			}, -- { x, z, y, ow, ox, oy, oz, cellid }
	templateType = CLONINGBUILDING	
}

ObjectTemplates:addTemplate(object_building_tatooine_cloning_facility_tatooine_small, "object/building/tatooine/cloning_facility_tatooine_small.iff")