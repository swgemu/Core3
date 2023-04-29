object_tangible_ship_components_weapon_capacitor_cap_koensayr_improved_light = object_tangible_ship_components_weapon_capacitor_shared_cap_koensayr_improved_light:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_koensayr_improved_light",

	attributes = {
		{"currentEnergy", 577.5},
		{"maxEnergy", 577.5},
		{"rechargeRate", 23.1},
		{"currentHitpoints", 362.25},
		{"maximumHitpoints", 362.25},
		{"maximumArmorHitpoints", 181.125},
		{"currentArmorHitpoints", 181.125},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 2750},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_koensayr_improved_light, "object/tangible/ship/components/weapon_capacitor/cap_koensayr_improved_light.iff")
