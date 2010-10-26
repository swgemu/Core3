desert_gurreck_charger = Creature:new {
	objectName = "@mob/creature_names:desert_gurreck_charger",
	socialGroup = "Gurreck",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5550,
	armor = 0,
	resists = {20,20,0,-1,0,-1,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(desert_gurreck_charger, "desert_gurreck_charger")
