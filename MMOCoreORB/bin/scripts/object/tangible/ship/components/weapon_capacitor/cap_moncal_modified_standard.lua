object_tangible_ship_components_weapon_capacitor_cap_moncal_modified_standard = object_tangible_ship_components_weapon_capacitor_shared_cap_moncal_modified_standard:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_moncal_modified_standard",

	attributes = {
		{"currentEnergy", 742.5},
		{"maxEnergy", 742.5},
		{"rechargeRate", 29.7},
		{"currentHitpoints", 465.75},
		{"maximumHitpoints", 465.75},
		{"maximumArmorHitpoints", 232.875},
		{"currentArmorHitpoints", 232.875},
		{"efficiency", 1},
		{"energyMaintenance", 950},
		{"mass", 8531.25},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_moncal_modified_standard, "object/tangible/ship/components/weapon_capacitor/cap_moncal_modified_standard.iff")
