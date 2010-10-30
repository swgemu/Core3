erratic_swirl_prong = Creature:new {
	objectName = "@mob/creature_names:erratic_swirl_prong",
	socialGroup = "Swirl Prong",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {25,35,0,50,50,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/swirl_prong.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(erratic_swirl_prong, "erratic_swirl_prong")