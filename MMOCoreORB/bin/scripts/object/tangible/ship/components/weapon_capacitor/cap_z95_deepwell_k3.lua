object_tangible_ship_components_weapon_capacitor_cap_z95_deepwell_k3 = object_tangible_ship_components_weapon_capacitor_shared_cap_z95_deepwell_k3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_z95_deepwell_k3",

	attributes = {
		{"currentEnergy", 675},
		{"maxEnergy", 675},
		{"rechargeRate", 27},
		{"currentHitpoints", 202.5},
		{"maximumHitpoints", 202.5},
		{"maximumArmorHitpoints", 101.25},
		{"currentArmorHitpoints", 101.25},
		{"efficiency", 1},
		{"energyMaintenance", 900},
		{"mass", 1575},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_z95_deepwell_k3, "object/tangible/ship/components/weapon_capacitor/cap_z95_deepwell_k3.iff")
