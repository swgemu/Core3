mind_of_solitude = Creature:new {
	objectName = "@mob/creature_names:mind_of_solitude",
	socialGroup = "solitude",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 21,
	chanceHit = 0.34,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {20,15,0,-1,0,0,-1,-1,-1},
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/human_male.iff"},
	lootGroups = {},
	weapons = {"rebel_weapons_heavy"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(mind_of_solitude, "mind_of_solitude")
