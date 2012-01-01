bewitching_donkuwah_shaman = Creature:new {
	objectName = "@mob/creature_names:bewitching_donkuwah_shaman",
	socialGroup = "Donkuwah Tr.",
	pvpFaction = "Donkuwah Tr.",
	faction = "",
	level = 21,
	chanceHit = 0.34,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {0,0,0,0,-1,30,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_ewok_m_11.iff"},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bewitching_donkuwah_shaman, "bewitching_donkuwah_shaman")