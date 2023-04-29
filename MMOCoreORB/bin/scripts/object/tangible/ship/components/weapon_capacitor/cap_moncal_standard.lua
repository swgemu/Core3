object_tangible_ship_components_weapon_capacitor_cap_moncal_standard = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_standard:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_standard",

	attributes = {
		{"currentEnergy", 550},
		{"maxEnergy", 550},
		{"rechargeRate", 26.4},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 2625},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_standard, "object/tangible/ship/components/weapon_capacitor/cap_moncal_standard.iff")
