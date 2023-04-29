object_tangible_ship_components_weapon_capacitor_cap_incom_bjn825 = object_tangible_ship_components_weapon_capacitor_shared_cap_incom_bjn825:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_incom_bjn825",

	attributes = {
		{"currentEnergy", 605},
		{"maxEnergy", 605},
		{"rechargeRate", 24.2},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 2625},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxEnergy", 0.2},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_incom_bjn825, "object/tangible/ship/components/weapon_capacitor/cap_incom_bjn825.iff")
