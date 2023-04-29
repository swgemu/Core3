object_tangible_ship_components_weapon_capacitor_cap_mandal_powersoak = object_tangible_ship_components_weapon_capacitor_shared_cap_mandal_powersoak:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_mandal_powersoak",

	attributes = {
		{"currentEnergy", 1098.07},
		{"maxEnergy", 1098.07},
		{"rechargeRate", 43.92},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 56400},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_mandal_powersoak, "object/tangible/ship/components/weapon_capacitor/cap_mandal_powersoak.iff")
