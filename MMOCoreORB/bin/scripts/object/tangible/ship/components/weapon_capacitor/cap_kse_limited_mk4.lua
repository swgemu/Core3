object_tangible_ship_components_weapon_capacitor_cap_kse_limited_mk4 = object_tangible_ship_components_weapon_capacitor_shared_cap_kse_limited_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_kse_limited_mk4",

	attributes = {
		{"currentEnergy", 1048.16},
		{"maxEnergy", 1048.16},
		{"rechargeRate", 41.927},
		{"currentHitpoints", 1471.73},
		{"maximumHitpoints", 1471.73},
		{"maximumArmorHitpoints", 735.864},
		{"currentArmorHitpoints", 735.864},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 32760},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_kse_limited_mk4, "object/tangible/ship/components/weapon_capacitor/cap_kse_limited_mk4.iff")
