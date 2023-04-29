object_tangible_ship_components_weapon_capacitor_cap_sfs_imperial_1 = object_tangible_ship_components_weapon_capacitor_shared_cap_sfs_imperial_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sfs_imperial_1",

	attributes = {
		{"currentEnergy", 525},
		{"maxEnergy", 525},
		{"rechargeRate", 21},
		{"currentHitpoints", 165},
		{"maximumHitpoints", 165},
		{"maximumArmorHitpoints", 82.5},
		{"currentArmorHitpoints", 82.5},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 1050},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sfs_imperial_1, "object/tangible/ship/components/weapon_capacitor/cap_sfs_imperial_1.iff")
