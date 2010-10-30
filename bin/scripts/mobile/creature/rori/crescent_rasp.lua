crescent_rasp = Creature:new {
	objectName = "@mob/creature_names:crescent_rasp",
	socialGroup = "Rasp",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 147,
	baseHAM = 150,
	baseHAMmax = 150,
	armor = 0,
	resists = {0,0,0,0,0,15,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/crowned_rasp.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(crescent_rasp, "crescent_rasp")