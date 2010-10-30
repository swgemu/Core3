kamurith_snapper = Creature:new {
	objectName = "@mob/creature_names:kamurith_snapper",
	socialGroup = "Kamurith",
	pvpFaction = "",
	faction = "",
	level = 44,
	chanceHit = 0.460000,
	damageMin = 405,
	damageMax = 520,
	baseXp = 4370,
	baseHAM = 9900,
	baseHAMmax = 9900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_lizard.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kamurith_snapper, "kamurith_snapper")