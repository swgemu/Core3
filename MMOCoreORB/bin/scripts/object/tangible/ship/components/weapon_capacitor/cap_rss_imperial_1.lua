object_tangible_ship_components_weapon_capacitor_cap_rss_imperial_1 = object_tangible_ship_components_weapon_capacitor_shared_cap_rss_imperial_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_rss_imperial_1",

	attributes = {
		{"currentEnergy", 425},
		{"maxEnergy", 425},
		{"rechargeRate", 17},
		{"currentHitpoints", 142.5},
		{"maximumHitpoints", 142.5},
		{"maximumArmorHitpoints", 71.25},
		{"currentArmorHitpoints", 71.25},
		{"efficiency", 1},
		{"energyMaintenance", 950},
		{"mass", 950},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_rss_imperial_1, "object/tangible/ship/components/weapon_capacitor/cap_rss_imperial_1.iff")
