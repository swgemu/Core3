volatile_scyk = Creature:new {
	objectName = "@mob/creature_names:scyk_volatile",
	socialGroup = "scyk",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_bristley",
	hideAmount = 25,
	boneType = "bone_mammal",
	boneAmount = 18,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 0,
	diet = CARNIVORE,

	templates = {"object/mobile/scyk.iff"},
	controlDeviceTemplate = "object/intangible/pet/dune_lizard_hue.iff",
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(volatile_scyk, "volatile_scyk")
