bocatt = Creature:new {
	objectName = "@monster_name:bocatt",
	socialGroup = "Bocatt",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2006,
	baseHAM = 7000,
	baseHAMmax = 7000,
	armor = 0,
	resists = {0,0,-1,-1,50,50,-1,-1,-1},
	meatType = "",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bocatt.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bocatt, "bocatt")