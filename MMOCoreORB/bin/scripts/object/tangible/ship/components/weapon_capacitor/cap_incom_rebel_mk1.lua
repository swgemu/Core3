object_tangible_ship_components_weapon_capacitor_cap_incom_rebel_mk1 = object_tangible_ship_components_weapon_capacitor_shared_cap_incom_rebel_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_incom_rebel_mk1",

	attributes = {
		{"currentEnergy", 475},
		{"maxEnergy", 475},
		{"rechargeRate", 21},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 950},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_incom_rebel_mk1, "object/tangible/ship/components/weapon_capacitor/cap_incom_rebel_mk1.iff")
