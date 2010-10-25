bile_drenched_quenker = Creature:new {
	objectName = "@mob/creature_names:bile_drenched_quenker",
	socialGroup = "Quenker",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 315,
	damageMax = 340,
	range = 25,
	baseXp = 3370,
	baseHAM = 9700,
	armor = 0,
	resists = {0,0,0,0,-1,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_scale",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"defaultattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(bile_drenched_quenker, "bile_drenched_quenker")
