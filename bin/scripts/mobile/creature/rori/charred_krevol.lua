charred_krevol = Creature:new {
	objectName = "@mob/creature_names:charred_krevol",
	socialGroup = "Krevol",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2700,
	armor = 0,
	resists = {0,0,30,30,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scale",
	hideAmount = 15,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(charred_krevol, "charred_krevol")
