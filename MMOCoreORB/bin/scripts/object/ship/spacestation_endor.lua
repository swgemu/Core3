object_ship_spacestation_endor = object_ship_shared_spacestation_neutral:new {
	objectName = "@space/space_mobile_type:station_endor",
	conversationTemplate = "spacestation_endor_convotemplate",
	conversationMobile = "object/mobile/shared_space_comm_station_endor.iff",
	conversationMessage = "@conversation/station_endor:s_e1c14e1d", -- Too Far Message

	faction = "civilian",
	type = "spacestation_neutral",
	name = "spacestation_neutral",

	slideFactor = 1.76,
	chassisHitpoints = 30000,
	chassisMass = 50000,

	reactor = { name = "rct_generic", hitpoints = 4966.639, armor = 1916.958,},
	shield_0 = { name = "shd_generic", hitpoints = 9612.102, armor = 2876.292, regen = 49.71952, front = 5983.614, back = 5995.161,},
	shield_1 = { name = "shd_generic", hitpoints = 4842.518, armor = 2969.425, regen = 39.20972, front = 2873.469, back = 2937.772,},
	armor_0 = { name = "arm_generic", hitpoints = 4961.945, armor = 4917.142,},
	armor_1 = { name = "arm_generic", hitpoints = 4897.431, armor = 4877.487,},
	capacitor = { name = "cap_generic", hitpoints = 4922.489, armor = 954.791, rechargeRate = 123.3029, energy = 2292.475,},
	bridge = { name = "bdg_generic", hitpoints = 1977.12, armor = 1964.19,},
	hangar = { name = "hgr_generic", hitpoints = 1946.25, armor = 1917.841,},
}

ObjectTemplates:addTemplate(object_ship_spacestation_endor, "object/ship/spacestation_endor.iff")
