serene_floater = Creature:new {
	objectName = "",
	customName = "Serene Floater",
	socialGroup = "bomarr",
	faction = "",
	level = 32,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 870,
	baseHAM = 1280,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/bomarr_spider_monk_droid.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "hedon_istee_mission_target_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(serene_floater, "serene_floater")
