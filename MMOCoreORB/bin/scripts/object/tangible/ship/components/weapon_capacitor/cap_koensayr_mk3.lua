object_tangible_ship_components_weapon_capacitor_cap_koensayr_mk3 = object_tangible_ship_components_weapon_capacitor_shared_cap_koensayr_mk3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_koensayr_mk3",

	attributes = {
		{"currentEnergy", 514.25},
		{"maxEnergy", 514.25},
		{"rechargeRate", 20.57},
		{"currentHitpoints", 603.06},
		{"maximumHitpoints", 603.06},
		{"maximumArmorHitpoints", 301.53},
		{"currentArmorHitpoints", 301.53},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 6562.5},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_koensayr_mk3, "object/tangible/ship/components/weapon_capacitor/cap_koensayr_mk3.iff")
