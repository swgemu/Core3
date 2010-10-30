force_sensitive_crypt_crawler = Creature:new {
	objectName = "@mob/creature_names:force_sensitive_crypt_crawler",
	socialGroup = "Remn. Of Kun",
	pvpFaction = "",
	faction = "",
	level = 95,
	chanceHit = 0.900000,
	damageMin = 685,
	damageMax = 1080,
	baseXp = 9057,
	baseHAM = 16000,
	baseHAMmax = 19000,
	armor = 0,
	resists = {45,45,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(force_sensitive_crypt_crawler, "force_sensitive_crypt_crawler")