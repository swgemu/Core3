remmer_dune_scavenger = Creature:new {
	objectName = "@mob/creature_names:remmer_dune_scavenger",
	socialGroup = "Remmer",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {15,0,25,35,-1,0,0,-1,-1},
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
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(remmer_dune_scavenger, "remmer_dune_scavenger")