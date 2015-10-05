
object_building_poi_coa2_rebel_drall_camp = object_building_poi_base_shared_base_poi_medium:new {
	childObjects = {
		{templateFile = "object/static/vehicle/player_shuttle.iff", x = -2, z = 0, y = -20, ox = 0, oy = 0.7071, oz = 0, ow = 0.7071, cellid = -1, containmentType = -1},
		{templateFile = "object/static/structure/corellia/corl_tent_hut_s01.iff", x = 18, z = 0, y = 0, ox = 0, oy = 0.7071, oz = 0, ow = 0.7071, cellid = -1, containmentType = -1},
		{templateFile = "object/static/structure/corellia/corl_tent_hut_s01.iff", x = -18, z = 0, y = 0, ox = 0, oy = -0.7071, oz = 0, ow = 0.7071, cellid = -1, containmentType = -1},
	}
}

ObjectTemplates:addTemplate(object_building_poi_coa2_rebel_drall_camp, "object/building/poi/coa2_rebel_drall_camp.iff")
