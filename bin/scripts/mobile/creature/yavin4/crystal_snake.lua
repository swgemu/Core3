crystal_snake = Creature:new {
	objectName = "@monster_name:crystal_snake",
	socialGroup = "Crystal Snake",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2543,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {20,20,0,0,-1,-1,60,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "",
	hideAmount = 2,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/crystal_snake.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"mediumpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crystal_snake, "crystal_snake")