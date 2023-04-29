object_tangible_ship_components_weapon_capacitor_cap_koensayr_mk5 = object_tangible_ship_components_weapon_capacitor_shared_cap_koensayr_mk5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_koensayr_mk5",

	attributes = {
		{"currentEnergy", 512.435},
		{"maxEnergy", 512.435},
		{"rechargeRate", 20.496},
		{"currentHitpoints", 770.266},
		{"maximumHitpoints", 770.266},
		{"maximumArmorHitpoints", 385.133},
		{"currentArmorHitpoints", 385.133},
		{"efficiency", 1},
		{"energyMaintenance", 900},
		{"mass", 35100},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_koensayr_mk5, "object/tangible/ship/components/weapon_capacitor/cap_koensayr_mk5.iff")
