object_tangible_ship_components_weapon_capacitor_cap_incom_special_bjn825 = object_tangible_ship_components_weapon_capacitor_shared_cap_incom_special_bjn825:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_incom_special_bjn825",

	attributes = {
		{"currentEnergy", 990},
		{"maxEnergy", 990},
		{"rechargeRate", 33},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 1250},
		{"mass", 4593.75},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_incom_special_bjn825, "object/tangible/ship/components/weapon_capacitor/cap_incom_special_bjn825.iff")
