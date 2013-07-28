event_canyon_krayt_dragon = Creature:new {
	objectName = "@mob/creature_names:canyon_krayt_dragon",
	customName = "a canyon krayt dragon (event)",
	socialGroup = "Krayt",
	pvpFaction = "",
	faction = "",
	level = 275,
	chanceHit = 272.5,
	damageMin = 1520,
	damageMax = 2750,
	baseXp = 0,
	baseHAM = 321000,
	baseHAMmax = 392000,
	armor = 3,
	resists = {60,60,60,60,50,60,60,60,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 20,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/canyon_krayt_dragon.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(event_canyon_krayt_dragon, "event_canyon_krayt_dragon")
