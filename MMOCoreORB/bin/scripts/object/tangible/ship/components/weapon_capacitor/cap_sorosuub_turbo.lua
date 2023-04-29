object_tangible_ship_components_weapon_capacitor_cap_sorosuub_turbo = object_tangible_ship_components_weapon_capacitor_shared_cap_sorosuub_turbo:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sorosuub_turbo",

	attributes = {
		{"currentEnergy", 423.5},
		{"maxEnergy", 423.5},
		{"rechargeRate", 16.94},
		{"currentHitpoints", 444.36},
		{"maximumHitpoints", 444.36},
		{"maximumArmorHitpoints", 222.18},
		{"currentArmorHitpoints", 222.18},
		{"efficiency", 1},
		{"energyMaintenance", 800},
		{"mass", 5000},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sorosuub_turbo, "object/tangible/ship/components/weapon_capacitor/cap_sorosuub_turbo.iff")
