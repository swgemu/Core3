gurreck_forest_stalker = Creature:new {
	objectName = "@mob/creature_names:woodland_gurreck",
	socialGroup = "gurreck",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.39,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3188,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {25,50,20,20,-1,-1,20,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 1,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gurreck_forest_stalker, "gurreck_forest_stalker")