object_tangible_ship_components_booster_bst_mission_reward_imperial_rss_ion_booster = object_tangible_ship_components_booster_shared_bst_mission_reward_imperial_rss_ion_booster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_mission_reward_imperial_rss_ion_booster",

	attributes = {
		{"currentEnergy", 1980},
		{"maximumEnergy", 1980},
		{"rechargeRate", 49.5},
		{"consumptionRate", 198},
		{"acceleration", 36.3},
		{"maxSpeed", 24.975},
		{"currentHitpoints", 672.75},
		{"maximumHitpoints", 672.75},
		{"maximumArmorHitpoints", 336.375},
		{"currentArmorHitpoints", 336.375},
		{"efficiency", 1},
		{"energyMaintenance", 450},
		{"mass", 3150},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maximumEnergy", 0.0001},
		{"rechargeRate", 0.0001},
		{"consumptionRate", 0.0001},
		{"acceleration", 0.0001},
		{"maxSpeed", 0.0001},
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0.0001},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_mission_reward_imperial_rss_ion_booster, "object/tangible/ship/components/booster/bst_mission_reward_imperial_rss_ion_booster.iff")
