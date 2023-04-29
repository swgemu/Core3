object_tangible_ship_components_weapon_capacitor_cap_rendili_overseer_j7 = object_tangible_ship_components_weapon_capacitor_shared_cap_rendili_overseer_j7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_rendili_overseer_j7",

	attributes = {
		{"currentEnergy", 500},
		{"maxEnergy", 500},
		{"rechargeRate", 20},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 1000},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maxEnergy", 0.25},
		{"rechargeRate", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.25},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_rendili_overseer_j7, "object/tangible/ship/components/weapon_capacitor/cap_rendili_overseer_j7.iff")
