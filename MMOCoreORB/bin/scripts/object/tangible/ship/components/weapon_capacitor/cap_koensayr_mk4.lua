object_tangible_ship_components_weapon_capacitor_cap_koensayr_mk4 = object_tangible_ship_components_weapon_capacitor_shared_cap_koensayr_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_koensayr_mk4",

	attributes = {
		{"currentEnergy", 598.95},
		{"maxEnergy", 598.95},
		{"rechargeRate", 23.958},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 14820},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_koensayr_mk4, "object/tangible/ship/components/weapon_capacitor/cap_koensayr_mk4.iff")
