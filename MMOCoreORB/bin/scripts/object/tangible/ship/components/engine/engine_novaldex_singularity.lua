object_tangible_ship_components_engine_engine_novaldex_singularity = object_tangible_ship_components_engine_shared_engine_novaldex_singularity:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_novaldex_singularity",

	attributes = {
		{"maxSpeed", 52.68},
		{"maxPitch", 53.088},
		{"maxRoll", 53.088},
		{"maxYaw", 53.088},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 1650},
		{"mass", 6187.5},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maxSpeed", 0.1},
		{"maxPitch", 0.06},
		{"maxRoll", 0.06},
		{"maxYaw", 0.06},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_novaldex_singularity, "object/tangible/ship/components/engine/engine_novaldex_singularity.iff")
