object_tangible_ship_components_weapon_capacitor_cap_qualdex_miser_standard = object_tangible_ship_components_weapon_capacitor_shared_cap_qualdex_miser_standard:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_qualdex_miser_standard",

	attributes = {
		{"currentEnergy", 900},
		{"maxEnergy", 900},
		{"rechargeRate", 30},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 1750},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_qualdex_miser_standard, "object/tangible/ship/components/weapon_capacitor/cap_qualdex_miser_standard.iff")
