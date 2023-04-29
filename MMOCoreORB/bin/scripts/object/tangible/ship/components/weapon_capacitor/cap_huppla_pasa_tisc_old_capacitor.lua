object_tangible_ship_components_weapon_capacitor_cap_huppla_pasa_tisc_old_capacitor = object_tangible_ship_components_weapon_capacitor_shared_cap_huppla_pasa_tisc_old_capacitor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_huppla_pasa_tisc_old_capacitor",

	attributes = {
		{"currentEnergy", 866.25},
		{"maxEnergy", 866.25},
		{"rechargeRate", 34.65},
		{"currentHitpoints", 543.375},
		{"maximumHitpoints", 543.375},
		{"maximumArmorHitpoints", 271.688},
		{"currentArmorHitpoints", 271.688},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 4812.5},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_huppla_pasa_tisc_old_capacitor, "object/tangible/ship/components/weapon_capacitor/cap_huppla_pasa_tisc_old_capacitor.iff")
