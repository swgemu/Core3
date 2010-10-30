berserk_marauder = Creature:new {
	objectName = "@mob/creature_names:berserk_marauder",
	socialGroup = "Marauder",
	pvpFaction = "Marauder",
	faction = "",
	level = 55,
	chanceHit = 0.550000,
	damageMin = 495,
	damageMax = 700,
	baseXp = 5373,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {40,40,0,-1,0,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(berserk_marauder, "berserk_marauder")