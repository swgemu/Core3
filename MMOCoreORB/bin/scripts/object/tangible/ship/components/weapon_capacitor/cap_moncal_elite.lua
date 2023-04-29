object_tangible_ship_components_weapon_capacitor_cap_moncal_elite = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_elite",

	attributes = {
		{"currentEnergy", 768.653},
		{"maxEnergy", 768.653},
		{"rechargeRate", 30.744},
		{"currentHitpoints", 1210.42},
		{"maximumHitpoints", 1210.42},
		{"maximumArmorHitpoints", 605.209},
		{"currentArmorHitpoints", 605.209},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 48750},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_elite, "object/tangible/ship/components/weapon_capacitor/cap_moncal_elite.iff")
