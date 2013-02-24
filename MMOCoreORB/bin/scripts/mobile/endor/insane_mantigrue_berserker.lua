insane_mantigrue_berserker = Creature:new {
	objectName = "@mob/creature_names:mantigrue_insane_berserker",
	socialGroup = "mantigrue",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.43,
	damageMin = 400,
	damageMax = 510,
	baseXp = 4916,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 1,
	resists = {50,50,100,50,-1,20,20,100,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_wooly",
	hideAmount = 75,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mantigrue_night_stalker.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(insane_mantigrue_berserker, "insane_mantigrue_berserker")
