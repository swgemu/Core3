object_tangible_ship_components_weapon_capacitor_cap_subpro_valiant_z1 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_valiant_z1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_valiant_z1",

	attributes = {
		{"currentEnergy", 500},
		{"maxEnergy", 500},
		{"rechargeRate", 24},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 1000},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_valiant_z1, "object/tangible/ship/components/weapon_capacitor/cap_subpro_valiant_z1.iff")
