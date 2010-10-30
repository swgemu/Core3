lice_ridden_remmer_queen = Creature:new {
	objectName = "@mob/creature_names:lice_ridden_remmer_queen",
	socialGroup = "Remmer",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3642,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {55,35,60,0,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/lice_ridden_remmer_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(lice_ridden_remmer_queen, "lice_ridden_remmer_queen")