singing_mountain_clan_sentry = Creature:new {
	objectName = "@mob/creature_names:singing_mountain_clan_sentry",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "mtn_clan",
	faction = "mtn_clan",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {65,65,65,65,65,65,65,65,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_sing_mt_clan_sentry.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 1500000},
				{group = "crystals_okay", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "armor_attachments", chance = 300000},
				{group = "clothing_attachments", chance = 300000},
				{group = "melee_weapons", chance = 2900000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 1400000
		}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_sentry, "singing_mountain_clan_sentry")
