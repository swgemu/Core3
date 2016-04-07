object_resource_container_resource_spawn = object_resource_container_shared_simple:new {
	playerRaces = { "object/creature/player/bothan_male.iff",
				"object/creature/player/bothan_female.iff",
				"object/creature/player/human_male.iff",
				"object/creature/player/human_female.iff",
				"object/creature/player/ithorian_male.iff",
				"object/creature/player/ithorian_female.iff",
				"object/creature/player/moncal_male.iff",
				"object/creature/player/moncal_female.iff",
				"object/creature/player/rodian_male.iff",
				"object/creature/player/rodian_female.iff",
				"object/creature/player/sullustan_male.iff",
				"object/creature/player/sullustan_female.iff",
				"object/creature/player/trandoshan_male.iff",
				"object/creature/player/trandoshan_female.iff",
				"object/creature/player/twilek_male.iff",
				"object/creature/player/twilek_female.iff",
				"object/creature/player/wookiee_male.iff",
				"object/creature/player/wookiee_female.iff",
				"object/creature/player/zabrak_male.iff",
				"object/creature/player/zabrak_female.iff" },

	level = 10,

	maxCondition = 1000,

	useCount = 1,

	optionsBitmask = 256, --Default all objects to not display ham bars.
	pvpStatusBitmask = 0,
	objectMenuComponent = "TangibleObjectMenuComponent",
	attributeListComponent = "AttributeListComponent",

	sliceable = 0,

	templateType = RESOURCESPAWN,
	gameObjectType = 4259840
}

ObjectTemplates:addTemplate(object_resource_container_resource_spawn, "object/resource_container/resource_spawn.iff")
