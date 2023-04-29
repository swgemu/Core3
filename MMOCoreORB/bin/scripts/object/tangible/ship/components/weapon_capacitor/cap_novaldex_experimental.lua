object_tangible_ship_components_weapon_capacitor_cap_novaldex_experimental = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_experimental:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_experimental",

	attributes = {
		{"currentEnergy", 1152.98},
		{"maxEnergy", 1152.98},
		{"rechargeRate", 46.116},
		{"currentHitpoints", 1733.1},
		{"maximumHitpoints", 1733.1},
		{"maximumArmorHitpoints", 866.549},
		{"currentArmorHitpoints", 866.549},
		{"efficiency", 1},
		{"energyMaintenance", 1250},
		{"mass", 58750},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_experimental, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_experimental.iff")
