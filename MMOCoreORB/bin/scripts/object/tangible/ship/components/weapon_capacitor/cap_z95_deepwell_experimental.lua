object_tangible_ship_components_weapon_capacitor_cap_z95_deepwell_experimental = object_tangible_ship_components_weapon_capacitor_shared_cap_z95_deepwell_experimental:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_z95_deepwell_experimental",

	attributes = {
		{"currentEnergy", 1207.88},
		{"maxEnergy", 1207.88},
		{"rechargeRate", 48.312},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 1300},
		{"mass", 56400},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maxEnergy", 0.2},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_z95_deepwell_experimental, "object/tangible/ship/components/weapon_capacitor/cap_z95_deepwell_experimental.iff")
