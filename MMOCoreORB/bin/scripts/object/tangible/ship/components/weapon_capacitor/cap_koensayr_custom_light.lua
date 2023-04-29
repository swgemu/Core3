object_tangible_ship_components_weapon_capacitor_cap_koensayr_custom_light = object_tangible_ship_components_weapon_capacitor_shared_cap_koensayr_custom_light:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_koensayr_custom_light",

	attributes = {
		{"currentEnergy", 712.5},
		{"maxEnergy", 712.5},
		{"rechargeRate", 28.5},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 1487.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_koensayr_custom_light, "object/tangible/ship/components/weapon_capacitor/cap_koensayr_custom_light.iff")
