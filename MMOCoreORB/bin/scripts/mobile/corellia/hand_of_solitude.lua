hand_of_solitude = Creature:new {
	objectName = "@mob/creature_names:hand_of_solitude",
	socialGroup = "solitude",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	diet = HERBIVORE,

	templates = {"object/mobile/human_male.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(hand_of_solitude, "hand_of_solitude")
