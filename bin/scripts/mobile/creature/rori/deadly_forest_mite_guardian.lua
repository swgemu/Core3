deadly_forest_mite_guardian = Creature:new {
	objectName = "@mob/creature_names:deadly_forest_mite_guardian",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 3200,
	armor = 0,
	resists = {0,15,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(deadly_forest_mite_guardian, "deadly_forest_mite_guardian")
