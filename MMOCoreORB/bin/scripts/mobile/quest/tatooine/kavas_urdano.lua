kavas_urdano = Creature:new {
	objectName = "@mob/creature_names:patron_chiss_female",
	customName = "Kavas Urdano",
	socialGroup = "valarian",
	faction = "valarian",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_kavas_urdano.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "theme_park_valarian_mission_giver_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kavas_urdano, "kavas_urdano")
