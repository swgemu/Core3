megan_drlar = Creature:new {
	objectName = "@mob/creature_names:megan_drlar",
	socialGroup = "thug",
	pvpFaction = "thug",
	faction = "thug",
	level = 22,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {30,30,0,0,-1,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/megan_drlar.iff"},
	lootGroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(megan_drlar, "megan_drlar")