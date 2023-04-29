object_tangible_ship_components_weapon_capacitor_cap_unknown_experimental = object_tangible_ship_components_weapon_capacitor_shared_cap_unknown_experimental:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_unknown_experimental",

	attributes = {
		{"currentEnergy", 632.225},
		{"maxEnergy", 632.225},
		{"rechargeRate", 25.289},
		{"currentHitpoints", 887.708},
		{"maximumHitpoints", 887.708},
		{"maximumArmorHitpoints", 443.854},
		{"currentArmorHitpoints", 443.854},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 17160},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_unknown_experimental, "object/tangible/ship/components/weapon_capacitor/cap_unknown_experimental.iff")
