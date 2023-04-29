object_tangible_ship_components_weapon_capacitor_cap_subpro_improved_valiant_z1 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_improved_valiant_z1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_improved_valiant_z1",

	attributes = {
		{"currentEnergy", 675},
		{"maxEnergy", 675},
		{"rechargeRate", 27},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 1400},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_improved_valiant_z1, "object/tangible/ship/components/weapon_capacitor/cap_subpro_improved_valiant_z1.iff")
