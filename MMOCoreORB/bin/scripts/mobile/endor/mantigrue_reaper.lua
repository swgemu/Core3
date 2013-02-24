mantigrue_reaper = Creature:new {
	objectName = "@mob/creature_names:mantigrue_reaper",
	socialGroup = "mantigrue",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.47,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4825,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {40,40,70,0,70,70,70,70,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mantigrue_reaper, "mantigrue_reaper")
