object_tangible_ship_components_weapon_capacitor_cap_moncal_modified_heavy = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_modified_heavy:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_modified_heavy",

	attributes = {
		{"currentEnergy", 635.25},
		{"maxEnergy", 635.25},
		{"rechargeRate", 25.41},
		{"currentHitpoints", 666.54},
		{"maximumHitpoints", 666.54},
		{"maximumArmorHitpoints", 333.27},
		{"currentArmorHitpoints", 333.27},
		{"efficiency", 1},
		{"energyMaintenance", 800},
		{"mass", 8740},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_modified_heavy, "object/tangible/ship/components/weapon_capacitor/cap_moncal_modified_heavy.iff")
