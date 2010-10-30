large_rock_beetle = Creature:new {
	objectName = "@mob/creature_names:large_rock_beetle",
	socialGroup = "Rock Beetle",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {20,20,0,15,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/rock_beetle.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(large_rock_beetle, "large_rock_beetle")