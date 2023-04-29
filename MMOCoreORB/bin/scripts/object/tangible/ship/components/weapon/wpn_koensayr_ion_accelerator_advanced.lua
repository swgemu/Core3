object_tangible_ship_components_weapon_wpn_koensayr_ion_accelerator_advanced = object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_koensayr_ion_accelerator_advanced",

	attributes = {
		{"minDamage", 2040.74},
		{"maxDamage", 3305.73},
		{"shieldEffectiveness", 0.6},
		{"armorEffectiveness", 0.4},
		{"energyPerShot", 29.868},
		{"refireRate", 0.34},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 2600},
		{"mass", 46800},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"minDamage", 0.14},
		{"maxDamage", 0.14},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_koensayr_ion_accelerator_advanced, "object/tangible/ship/components/weapon/wpn_koensayr_ion_accelerator_advanced.iff")
