object_tangible_ship_components_weapon_capacitor_cap_z95_deepwell_k5 = object_tangible_ship_components_weapon_capacitor_shared_cap_z95_deepwell_k5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_z95_deepwell_k5",

	attributes = {
		{"currentEnergy", 605},
		{"maxEnergy", 605},
		{"rechargeRate", 24.2},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 6875},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_z95_deepwell_k5, "object/tangible/ship/components/weapon_capacitor/cap_z95_deepwell_k5.iff")
