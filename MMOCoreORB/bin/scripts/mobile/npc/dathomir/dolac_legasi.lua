dolac_legasi = Creature:new {
	objectName = "@mob/creature_names:dolac_legasi",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 2,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dolac_legasi.iff"},
	lootgroups = {},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "dolac_legasi_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dolac_legasi, "dolac_legasi")