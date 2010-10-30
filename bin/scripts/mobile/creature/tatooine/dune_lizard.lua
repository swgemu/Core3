dune_lizard = Creature:new {
	objectName = "@monster_name:dune_lizard",
	socialGroup = "Dune Lizard",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {0,15,0,45,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_bristley",
	hideAmount = 50,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/dune_lizard.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dune_lizard, "dune_lizard")