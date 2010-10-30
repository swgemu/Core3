perlek_ravager = Creature:new {
	objectName = "@mob/creature_names:perlek_ravager",
	socialGroup = "Perlek",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1426,
	baseHAM = 2700,
	baseHAMmax = 2700,
	armor = 0,
	resists = {0,0,0,50,50,-1,50,-1,-1},
	meatType = "meat_avian",
	meatAmount = 275,
	hideType = "hide_leathery",
	hideAmount = 115,
	boneType = "bone_avian",
	boneAmount = 190,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/perlek.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(perlek_ravager, "perlek_ravager")