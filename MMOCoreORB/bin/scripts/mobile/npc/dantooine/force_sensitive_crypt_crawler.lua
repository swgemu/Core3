force_sensitive_crypt_crawler = Creature:new {
	objectName = "@mob/creature_names:force_sensitive_crypt_crawler",
	socialGroup = "Remn. Of Kun",
	pvpFaction = "",
	faction = "",
	level = 95,
	chanceHit = 0.9,
	damageMin = 685,
	damageMax = 1080,
	baseXp = 9057,
	baseHAM = 16000,
	baseHAMmax = 19000,
	armor = 2,
	resists = {45,45,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_force_sensitive_crypt_crawler.iff"},
	lootGroups = {
		{
			groups = {
				{group = "crystals_good", chance = 900000},
				{group = "color_crystals", chance = 950000},
				{group = "melee_weapons", chance = 2500000},
				{group = "armor_attachments", chance = 2750000},
				{group = "holocron_dark", chance = 150000},
				{group = "clothing_attachments", chance = 2750000}
			},
			lootChance = 4800000
		}				
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(force_sensitive_crypt_crawler, "force_sensitive_crypt_crawler")