object_tangible_ship_components_weapon_capacitor_cap_sorosuub_flash = object_tangible_ship_components_weapon_capacitor_shared_cap_sorosuub_flash:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_sorosuub_flash",

	attributes = {
		{"currentEnergy", 988.268},
		{"maxEnergy", 988.268},
		{"rechargeRate", 39.528},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 47000},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_sorosuub_flash, "object/tangible/ship/components/weapon_capacitor/cap_sorosuub_flash.iff")
