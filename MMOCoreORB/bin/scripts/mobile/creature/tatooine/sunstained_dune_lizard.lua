sunstained_dune_lizard = Creature:new {
	objectName = "@mob/creature_names:dune_lizard_sunstained",
	socialGroup = "Dune Lizard",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {0,15,0,45,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_bristley",
	hideAmount = 50,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/dune_lizard.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sunstained_dune_lizard, "sunstained_dune_lizard")