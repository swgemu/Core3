object_tangible_ship_components_weapon_capacitor_cap_sorosuub_enhanced_dynamo_mk1 = object_tangible_ship_components_weapon_capacitor_shared_cap_sorosuub_enhanced_dynamo_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sorosuub_enhanced_dynamo_mk1",

	attributes = {
		{"currentEnergy", 750},
		{"maxEnergy", 750},
		{"rechargeRate", 36},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 1750},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sorosuub_enhanced_dynamo_mk1, "object/tangible/ship/components/weapon_capacitor/cap_sorosuub_enhanced_dynamo_mk1.iff")
