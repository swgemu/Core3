scyk = Creature:new {
	objectName = "@mob/creature_names:scyk",
	socialGroup = "Scyk",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_bristley",
	hideAmount = 25,
	boneType = "bone_mammal",
	boneAmount = 18,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/scyk.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(scyk, "scyk")