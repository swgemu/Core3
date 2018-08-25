giant_stintaril = Creature:new {
	objectName = "@mob/creature_names:giant_stintaril",
	socialGroup = "stinaril",
	faction = "",
	level = 22,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {120,120,10,-1,10,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 9,
	hideType = "hide_bristley",
	hideAmount = 7,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_stintaril.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/stintaril_hue.iff",
	scale = 1.3,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_stintaril, "giant_stintaril")
