object_tangible_ship_components_weapon_capacitor_cap_sorosuub_supercharged_dynamo_mk4 = object_tangible_ship_components_weapon_capacitor_shared_cap_sorosuub_supercharged_dynamo_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sorosuub_supercharged_dynamo_mk4",

	attributes = {
		{"currentEnergy", 695.447},
		{"maxEnergy", 695.447},
		{"rechargeRate", 27.816},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 40950},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sorosuub_supercharged_dynamo_mk4, "object/tangible/ship/components/weapon_capacitor/cap_sorosuub_supercharged_dynamo_mk4.iff")
