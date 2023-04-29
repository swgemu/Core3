object_tangible_ship_components_weapon_capacitor_cap_qualdex_experimental = object_tangible_ship_components_weapon_capacitor_shared_cap_qualdex_experimental:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_qualdex_experimental",

	attributes = {
		{"currentEnergy", 988.268},
		{"maxEnergy", 988.268},
		{"rechargeRate", 39.528},
		{"currentHitpoints", 1485.51},
		{"maximumHitpoints", 1485.51},
		{"maximumArmorHitpoints", 742.756},
		{"currentArmorHitpoints", 742.756},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 51700},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_qualdex_experimental, "object/tangible/ship/components/weapon_capacitor/cap_qualdex_experimental.iff")
