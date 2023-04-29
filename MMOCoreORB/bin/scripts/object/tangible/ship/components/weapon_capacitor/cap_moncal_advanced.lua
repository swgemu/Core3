object_tangible_ship_components_weapon_capacitor_cap_moncal_advanced = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_advanced",

	attributes = {
		{"currentEnergy", 632.225},
		{"maxEnergy", 632.225},
		{"rechargeRate", 25.289},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 15600},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_advanced, "object/tangible/ship/components/weapon_capacitor/cap_moncal_advanced.iff")
