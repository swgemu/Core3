kunga_loreweaver = Creature:new {
	objectName = "@mob/creature_names:kunga_loreweaver",
	socialGroup = "Kunga Tribe",
	pvpFaction = "Kunga Tribe",
	faction = "",
	level = 51,
	chanceHit = 0.48,
	damageMin = 425,
	damageMax = 560,
	baseXp = 5007,
	baseHAM = 9900,
	baseHAMmax = 12100,
	armor = 1,
	resists = {0,60,0,-1,-1,65,40,-1,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dantari_male.iff"},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kunga_loreweaver, "kunga_loreweaver")