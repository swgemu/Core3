dragonet = Creature:new {
	objectName = "@mob/creature_names:dragonet",
	socialGroup = "lizard",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2914,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {125,140,15,15,15,-1,15,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 125,
	hideType = "hide_bristley",
	hideAmount = 75,
	boneType = "bone_mammal",
	boneAmount = 68,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/dune_lizard.iff"},
	controlDeviceTemplate = "object/intangible/pet/dune_lizard_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dragonet, "dragonet")
