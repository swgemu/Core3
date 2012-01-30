ree_yees = Creature:new {
	objectName = "@mob/creature_names:ree_yees",
	socialGroup = "Jabba",
	pvpFaction = "Jabba",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1426,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/gran_male.iff"},
	lootGroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(ree_yees, "ree_yees")