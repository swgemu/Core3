dune_lizard = Creature:new {
	objectName = "@mob/creature_names:dune_lizard",
	socialGroup = "lizard",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {5,115,5,145,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_bristley",
	hideAmount = 50,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = HERD + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/dune_lizard_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/dune_lizard_hue.iff",
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(dune_lizard, "dune_lizard")
