bestine_stone_merchant = Creature:new {
	objectName = "@bestine:merchant_title",
	customName = "Stone Merchant",
	socialGroup = "townsperson",
	faction = "townsperson",
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
	optionsBitmask = AIENABLED + INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_artisan_trainer_03.iff",
		"object/mobile/dressed_artisan_trainer_02.iff",
		"object/mobile/dressed_artisan_trainer_01.iff",
		"object/mobile/dressed_commoner_artisan_trandoshan_male_01.iff",
		"object/mobile/dressed_commoner_artisan_sullustan_male_01.iff",
		"object/mobile/dressed_commoner_artisan_bith_male_01.iff"
	},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "StoneMerchantConvoTemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(bestine_stone_merchant, "bestine_stone_merchant")
