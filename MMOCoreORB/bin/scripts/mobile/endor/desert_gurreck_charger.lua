desert_gurreck_charger = Creature:new {
	objectName = "@mob/creature_names:desert_gurreck_charger",
	socialGroup = "gurreck",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {20,20,10,-1,10,-1,10,10,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(desert_gurreck_charger, "desert_gurreck_charger")