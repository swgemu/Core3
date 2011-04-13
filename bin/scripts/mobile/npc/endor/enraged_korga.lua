enraged_korga = Creature:new {
	objectName = "@mob/creature_names:enraged_korga",
	socialGroup = "Korga Tribe",
	pvpFaction = "Korga Tribe",
	faction = "",
	level = 32,
	chanceHit = 0.390000,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3279,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {0,0,0,100,100,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(enraged_korga, "enraged_korga")