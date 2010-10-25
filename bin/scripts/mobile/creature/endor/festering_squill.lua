festering_squill = Creature:new {
	objectName = "@mob/creature_names:festering_squill",
	socialGroup = "Endor Squill",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.380000,
	damageMin = 305,
	damageMax = 320,
	range = 0,
	baseXp = 3097,
	baseHAM = 7000,
	armor = 0,
	resists = {40,40,0,-1,0,0,50,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(festering_squill, "festering_squill")
