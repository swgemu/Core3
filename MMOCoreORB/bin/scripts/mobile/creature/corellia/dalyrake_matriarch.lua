dalyrake_matriarch = Creature:new {
	objectName = "@mob/creature_names:dalyrake_matriarch",
	socialGroup = "Dalyrake",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4550,
	armor = 0,
	resists = {20,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
	hideType = "hide_scale",
	hideAmount = 60,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mildpoison",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dalyrake_matriarch, "dalyrake_matriarch")
