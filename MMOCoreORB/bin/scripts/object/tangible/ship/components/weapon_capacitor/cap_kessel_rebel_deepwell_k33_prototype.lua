object_tangible_ship_components_weapon_capacitor_cap_kessel_rebel_deepwell_k33_prototype = object_tangible_ship_components_weapon_capacitor_shared_cap_kessel_rebel_deepwell_k33_prototype:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_kessel_rebel_deepwell_k33_prototype",

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
		{"maxEnergy", 0.25},
		{"rechargeRate", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.25},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_kessel_rebel_deepwell_k33_prototype, "object/tangible/ship/components/weapon_capacitor/cap_kessel_rebel_deepwell_k33_prototype.iff")
