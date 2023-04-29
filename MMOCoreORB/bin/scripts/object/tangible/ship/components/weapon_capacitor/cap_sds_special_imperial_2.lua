object_tangible_ship_components_weapon_capacitor_cap_sds_special_imperial_2 = object_tangible_ship_components_weapon_capacitor_shared_cap_sds_special_imperial_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sds_special_imperial_2",

	attributes = {
		{"currentEnergy", 907.5},
		{"maxEnergy", 907.5},
		{"rechargeRate", 36.3},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 4593.75},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maxEnergy", 0.2},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sds_special_imperial_2, "object/tangible/ship/components/weapon_capacitor/cap_sds_special_imperial_2.iff")
