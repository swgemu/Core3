object_tangible_ship_components_weapon_capacitor_cap_novaldex_small_capacitor = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_small_capacitor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_small_capacitor",

	attributes = {
		{"currentEnergy", 475},
		{"maxEnergy", 475},
		{"rechargeRate", 19},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_small_capacitor, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_small_capacitor.iff")
