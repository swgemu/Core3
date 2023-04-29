object_tangible_ship_components_weapon_wpn_koensayr_ion_accelerator = object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_koensayr_ion_accelerator",

	attributes = {
		{"minDamage", 609},
		{"maxDamage", 858},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 22.44},
		{"refireRate", 0.34},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
		{"mass", 2625},
		{"reverseEngineeringLevel", 3},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_koensayr_ion_accelerator, "object/tangible/ship/components/weapon/wpn_koensayr_ion_accelerator.iff")
