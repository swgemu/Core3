kusak_stalker = Creature:new {
	objectName = "@mob/creature_names:kusak_stalker",
	socialGroup = "Kusak",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {30,15,10,-1,10,10,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 20,
	hideType = "hide_bristley",
	hideAmount = 14,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kusak.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kusak_stalker, "kusak_stalker")