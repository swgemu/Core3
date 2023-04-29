object_tangible_ship_components_weapon_capacitor_cap_subpro_gallant_a1 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_gallant_a1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_gallant_a1",

	attributes = {
		{"currentEnergy", 577.5},
		{"maxEnergy", 577.5},
		{"rechargeRate", 23.1},
		{"currentHitpoints", 362.25},
		{"maximumHitpoints", 362.25},
		{"maximumArmorHitpoints", 181.125},
		{"currentArmorHitpoints", 181.125},
		{"efficiency", 1},
		{"energyMaintenance", 750},
		{"mass", 3281.25},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_gallant_a1, "object/tangible/ship/components/weapon_capacitor/cap_subpro_gallant_a1.iff")
