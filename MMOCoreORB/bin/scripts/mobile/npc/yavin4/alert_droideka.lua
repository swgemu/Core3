alert_droideka = Creature:new {
	objectName = "@mob/creature_names:geonosian_droideka_crazed",
	socialGroup = "Geonosian",
	pvpFaction = "Geonosian",
	faction = "",
	level = 39,
	chanceHit = 0.56,
	damageMin = 426,
	damageMax = 564,
	baseXp = 5650,
	baseHAM = 13183,
	baseHAMmax = 15124,
	armor = 2,
	resists = {30,30,-1,0,30,0,30,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/droideka.iff"},
	lootgroups = {},
	weapons = {"geonosian_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(alert_droideka, "alert_droideka")