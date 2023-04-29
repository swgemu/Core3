object_tangible_ship_components_weapon_wpn_koensayr_deluxe_ion_accelerator = object_tangible_ship_components_weapon_shared_wpn_koensayr_deluxe_ion_accelerator:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_koensayr_deluxe_ion_accelerator",

	attributes = {
		{"minDamage", 761.25},
		{"maxDamage", 1072.5},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 28.05},
		{"refireRate", 0.425},
		{"currentHitpoints", 388.125},
		{"maximumHitpoints", 388.125},
		{"maximumArmorHitpoints", 194.062},
		{"currentArmorHitpoints", 194.062},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
		{"mass", 4156.25},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"minDamage", 0.12},
		{"maxDamage", 0.12},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_koensayr_deluxe_ion_accelerator, "object/tangible/ship/components/weapon/wpn_koensayr_deluxe_ion_accelerator.iff")
