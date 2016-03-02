giant_crystal_snake = Creature:new {
	objectName = "@mob/creature_names:giant_crystal_snake",
	socialGroup = "snake",
	faction = "",
	level = 31,
	chanceHit = 0.39,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {20,20,20,20,20,20,20,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_crystal_snake.iff"},
	controlDeviceTemplate = "object/intangible/pet/crystal_snake.iff",
	scale = 1.4,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_crystal_snake, "giant_crystal_snake")
