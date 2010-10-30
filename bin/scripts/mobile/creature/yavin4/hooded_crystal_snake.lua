hooded_crystal_snake = Creature:new {
	objectName = "@mob/creature_names:crystal_snake_hooded",
	socialGroup = "Crystal Snake",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {20,20,0,0,-1,-1,60,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 2,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
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

CreatureTemplates:addCreatureTemplate(hooded_crystal_snake, "hooded_crystal_snake")