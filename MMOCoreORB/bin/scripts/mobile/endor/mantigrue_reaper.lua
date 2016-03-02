mantigrue_reaper = Creature:new {
	objectName = "@mob/creature_names:mantigrue_reaper",
	socialGroup = "mantigrue",
	faction = "",
	level = 50,
	chanceHit = 0.47,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4825,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {140,140,170,0,170,170,170,170,-1},
	meatType = "meat_carnivore",
	meatAmount = 110,
	hideType = "hide_wooly",
	hideAmount = 95,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	scale = 1.15,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mantigrue_reaper, "mantigrue_reaper")
