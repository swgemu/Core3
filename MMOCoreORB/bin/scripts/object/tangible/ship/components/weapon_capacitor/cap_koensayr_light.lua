object_tangible_ship_components_weapon_capacitor_cap_koensayr_light = object_tangible_ship_components_weapon_capacitor_shared_cap_koensayr_light:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_koensayr_light",

	attributes = {
		{"currentEnergy", 450},
		{"maxEnergy", 450},
		{"rechargeRate", 18},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 800},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_koensayr_light, "object/tangible/ship/components/weapon_capacitor/cap_koensayr_light.iff")
