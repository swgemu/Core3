sith_shadow_thug = Creature:new {
	objectName = "@mob/creature_names:shadow_thug",
	socialGroup = "Sith Shadow",
	pvpFaction = "s.s. non-aggro",
	faction = "",
	level = 127,
	chanceHit = 4,
	damageMin = 770,
	damageMax = 1250,
	baseXp = 2503,
	baseHAM = 44300,
	baseHAMmax = 54300,
	armor = 2,
	resists = {75,85,80,65,80,80,80,80,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_sith_shadow_hum_m_01.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(sith_shadow_thug, "sith_shadow_thug")