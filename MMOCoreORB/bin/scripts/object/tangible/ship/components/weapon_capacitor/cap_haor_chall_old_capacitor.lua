object_tangible_ship_components_weapon_capacitor_cap_haor_chall_old_capacitor = object_tangible_ship_components_weapon_capacitor_shared_cap_haor_chall_old_capacitor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_haor_chall_old_capacitor",

	attributes = {
		{"currentEnergy", 350},
		{"maxEnergy", 350},
		{"rechargeRate", 14},
		{"currentHitpoints", 105},
		{"maximumHitpoints", 105},
		{"maximumArmorHitpoints", 52.5},
		{"currentArmorHitpoints", 52.5},
		{"efficiency", 1},
		{"energyMaintenance", 700},
		{"mass", 700},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_haor_chall_old_capacitor, "object/tangible/ship/components/weapon_capacitor/cap_haor_chall_old_capacitor.iff")
