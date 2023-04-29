object_tangible_ship_components_weapon_capacitor_cap_novaldex_wampa_s1 = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_wampa_s1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_wampa_s1",

	attributes = {
		{"currentEnergy", 952.875},
		{"maxEnergy", 952.875},
		{"rechargeRate", 38.115},
		{"currentHitpoints", 999.81},
		{"maximumHitpoints", 999.81},
		{"maximumArmorHitpoints", 499.905},
		{"currentArmorHitpoints", 499.905},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 12563.8},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_wampa_s1, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_wampa_s1.iff")
