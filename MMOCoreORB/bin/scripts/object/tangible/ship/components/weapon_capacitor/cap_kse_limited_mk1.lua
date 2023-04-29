object_tangible_ship_components_weapon_capacitor_cap_kse_limited_mk1 = object_tangible_ship_components_weapon_capacitor_shared_cap_kse_limited_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_kse_limited_mk1",

	attributes = {
		{"currentEnergy", 525},
		{"maxEnergy", 525},
		{"rechargeRate", 21},
		{"currentHitpoints", 157.5},
		{"maximumHitpoints", 157.5},
		{"maximumArmorHitpoints", 78.75},
		{"currentArmorHitpoints", 78.75},
		{"efficiency", 1},
		{"energyMaintenance", 700},
		{"mass", 1225},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_kse_limited_mk1, "object/tangible/ship/components/weapon_capacitor/cap_kse_limited_mk1.iff")
