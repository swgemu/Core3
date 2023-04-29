object_tangible_ship_components_weapon_capacitor_cap_sorosuub_dynamo_mk3 = object_tangible_ship_components_weapon_capacitor_shared_cap_sorosuub_dynamo_mk3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sorosuub_dynamo_mk3",

	attributes = {
		{"currentEnergy", 998.25},
		{"maxEnergy", 998.25},
		{"rechargeRate", 39.93},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 12017.5},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxEnergy", 0.2},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sorosuub_dynamo_mk3, "object/tangible/ship/components/weapon_capacitor/cap_sorosuub_dynamo_mk3.iff")
