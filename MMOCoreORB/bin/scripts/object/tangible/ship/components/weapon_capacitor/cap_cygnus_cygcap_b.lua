object_tangible_ship_components_weapon_capacitor_cap_cygnus_cygcap_b = object_tangible_ship_components_weapon_capacitor_shared_cap_cygnus_cygcap_b:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_cygnus_cygcap_b",

	attributes = {
		{"currentEnergy", 522.5},
		{"maxEnergy", 522.5},
		{"rechargeRate", 20.9},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 2250},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_cygnus_cygcap_b, "object/tangible/ship/components/weapon_capacitor/cap_cygnus_cygcap_b.iff")
