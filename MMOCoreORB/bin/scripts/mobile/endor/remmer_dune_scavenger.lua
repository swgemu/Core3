remmer_dune_scavenger = Creature:new {
	objectName = "@mob/creature_names:remmer_dune_scavenger",
	socialGroup = "remmer",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {15,5,25,35,-1,5,5,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/remmer.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(remmer_dune_scavenger, "remmer_dune_scavenger")