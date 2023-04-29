object_tangible_ship_components_weapon_capacitor_cap_sds_imperial_1 = object_tangible_ship_components_weapon_capacitor_shared_cap_sds_imperial_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sds_imperial_1",

	attributes = {
		{"currentEnergy", 712.5},
		{"maxEnergy", 712.5},
		{"rechargeRate", 28.5},
		{"currentHitpoints", 213.75},
		{"maximumHitpoints", 213.75},
		{"maximumArmorHitpoints", 106.875},
		{"currentArmorHitpoints", 106.875},
		{"efficiency", 1},
		{"energyMaintenance", 950},
		{"mass", 1662.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sds_imperial_1, "object/tangible/ship/components/weapon_capacitor/cap_sds_imperial_1.iff")
