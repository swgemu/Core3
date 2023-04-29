object_tangible_ship_components_weapon_capacitor_cap_novaldex_deluxe_wampa_s1 = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_deluxe_wampa_s1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_deluxe_wampa_s1",

	attributes = {
		{"currentEnergy", 598.95},
		{"maxEnergy", 598.95},
		{"rechargeRate", 23.958},
		{"currentHitpoints", 840.987},
		{"maximumHitpoints", 840.987},
		{"maximumArmorHitpoints", 420.493},
		{"currentArmorHitpoints", 420.493},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 16380},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_deluxe_wampa_s1, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_deluxe_wampa_s1.iff")
