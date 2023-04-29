object_tangible_ship_components_weapon_capacitor_cap_moncal_light = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_light:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_light",

	attributes = {
		{"currentEnergy", 475},
		{"maxEnergy", 475},
		{"rechargeRate", 19},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 850},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_light, "object/tangible/ship/components/weapon_capacitor/cap_moncal_light.iff")
