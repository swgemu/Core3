object_tangible_ship_components_weapon_capacitor_cap_qualdex_miser_light = object_tangible_ship_components_weapon_capacitor_shared_cap_qualdex_miser_light:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_qualdex_miser_light",

	attributes = {
		{"currentEnergy", 450},
		{"maxEnergy", 450},
		{"rechargeRate", 18},
		{"currentHitpoints", 135},
		{"maximumHitpoints", 135},
		{"maximumArmorHitpoints", 67.5},
		{"currentArmorHitpoints", 67.5},
		{"efficiency", 1},
		{"energyMaintenance", 900},
		{"mass", 900},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_qualdex_miser_light, "object/tangible/ship/components/weapon_capacitor/cap_qualdex_miser_light.iff")
