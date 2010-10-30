giant_crystal_snake = Creature:new {
	objectName = "@mob/creature_names:giant_crystal_snake",
	socialGroup = "Crystal Snake",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.390000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 9200,
	baseHAMmax = 9200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_crystal_snake.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_crystal_snake, "giant_crystal_snake")