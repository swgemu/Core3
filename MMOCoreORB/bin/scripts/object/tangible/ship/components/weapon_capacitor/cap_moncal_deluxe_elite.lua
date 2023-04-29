object_tangible_ship_components_weapon_capacitor_cap_moncal_deluxe_elite = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_deluxe_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_deluxe_elite",

	attributes = {
		{"currentEnergy", 1152.98},
		{"maxEnergy", 1152.98},
		{"rechargeRate", 46.116},
		{"currentHitpoints", 1815.63},
		{"maximumHitpoints", 1815.63},
		{"maximumArmorHitpoints", 907.813},
		{"currentArmorHitpoints", 907.813},
		{"efficiency", 1},
		{"energyMaintenance", 1250},
		{"mass", 56400},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_deluxe_elite, "object/tangible/ship/components/weapon_capacitor/cap_moncal_deluxe_elite.iff")
