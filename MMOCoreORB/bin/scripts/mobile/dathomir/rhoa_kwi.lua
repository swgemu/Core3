rhoa_kwi = Creature:new {
	objectName = "@mob/creature_names:rhoa_kwi",
	socialGroup = "kwi",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3551,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {25,25,25,80,25,25,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi, "rhoa_kwi")