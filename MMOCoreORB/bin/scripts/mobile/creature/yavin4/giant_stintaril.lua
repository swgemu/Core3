giant_stintaril = Creature:new {
	objectName = "@mob/creature_names:giant_stintaril",
	socialGroup = "Stinaril",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {20,20,10,-1,10,-1,-1,-1,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_stintaril.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_stintaril, "giant_stintaril")