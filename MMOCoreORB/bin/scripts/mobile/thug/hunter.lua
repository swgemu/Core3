hunter = Creature:new {
	objectName = "@mob/creature_names:hunter",
	socialGroup = "Mercenary",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK + STALKER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_commoner_naboo_twilek_female_02.iff"},
	lootGroups = {},
	weapons = {"rebel_weapons_light"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(hunter, "hunter")