feral_orphan = Creature:new {
	objectName = "@mob/creature_names:dire_cat_feral_orphan",
	socialGroup = "dire_cat",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.3,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {20,20,0,10,10,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/dire_cat.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(feral_orphan, "feral_orphan")