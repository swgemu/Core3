object_tangible_ship_components_weapon_capacitor_cap_moncal_charged_light = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_charged_light:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_charged_light",

	attributes = {
		{"currentEnergy", 712.5},
		{"maxEnergy", 712.5},
		{"rechargeRate", 31.5},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_charged_light, "object/tangible/ship/components/weapon_capacitor/cap_moncal_charged_light.iff")
