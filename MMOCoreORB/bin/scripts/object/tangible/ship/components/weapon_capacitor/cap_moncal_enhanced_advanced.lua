object_tangible_ship_components_weapon_capacitor_cap_moncal_enhanced_advanced = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_enhanced_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_enhanced_advanced",

	attributes = {
		{"currentEnergy", 898.425},
		{"maxEnergy", 898.425},
		{"rechargeRate", 35.937},
		{"currentHitpoints", 1261.48},
		{"maximumHitpoints", 1261.48},
		{"maximumArmorHitpoints", 630.74},
		{"currentArmorHitpoints", 630.74},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 28665},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_enhanced_advanced, "object/tangible/ship/components/weapon_capacitor/cap_moncal_enhanced_advanced.iff")
