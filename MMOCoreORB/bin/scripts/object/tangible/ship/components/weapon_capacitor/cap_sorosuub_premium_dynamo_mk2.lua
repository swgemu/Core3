object_tangible_ship_components_weapon_capacitor_cap_sorosuub_premium_dynamo_mk2 = object_tangible_ship_components_weapon_capacitor_shared_cap_sorosuub_premium_dynamo_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sorosuub_premium_dynamo_mk2",

	attributes = {
		{"currentEnergy", 701.25},
		{"maxEnergy", 701.25},
		{"rechargeRate", 28.05},
		{"currentHitpoints", 491.625},
		{"maximumHitpoints", 491.625},
		{"maximumArmorHitpoints", 245.812},
		{"currentArmorHitpoints", 245.812},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 4812.5},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sorosuub_premium_dynamo_mk2, "object/tangible/ship/components/weapon_capacitor/cap_sorosuub_premium_dynamo_mk2.iff")
