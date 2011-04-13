majestic_plumed_rasp = Creature:new {
	objectName = "@mob/creature_names:majestic_plumed_rasp",
	socialGroup = "Rasp",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 514,
	baseHAM = 450,
	baseHAMmax = 450,
	armor = 0,
	resists = {0,0,0,0,0,10,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 5,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 4,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/plumed_rasp.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(majestic_plumed_rasp, "majestic_plumed_rasp")