cu_pa = Creature:new {
	objectName = "@mob/creature_names:cu_pa",
	socialGroup = "cu_pa",
	pvpFaction = "",
	faction = "",
	level = 11,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 356,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 215,
	hideType = "hide_bristley",
	hideAmount = 100,
	boneType = "bone_mammal",
	boneAmount = 115,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/cu_pa.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cu_pa, "cu_pa")