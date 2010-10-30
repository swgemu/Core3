remmer_carrion_keeper = Creature:new {
	objectName = "@mob/creature_names:remmer_carrion_keeper",
	socialGroup = "Remmer",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2443,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {30,0,40,-1,-1,-1,50,-1,-1},
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

	templates = {"object/mobile/remmer.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(remmer_carrion_keeper, "remmer_carrion_keeper")