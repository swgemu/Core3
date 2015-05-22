singing_mountain_clan_initiate = Creature:new {
	objectName = "@mob/creature_names:singing_mtn_clan_initiate",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "mtn_clan",
	faction = "mtn_clan",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4916,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {30,30,75,-1,75,-1,-1,35,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_sing_mt_clan_initiate.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 1500000},
				{group = "crystals_okay", chance = 500000},
				{group = "color_crystals", chance = 500000},
				{group = "armor_attachments", chance = 350000},
				{group = "clothing_attachments", chance = 350000},
				{group = "melee_weapons", chance = 2800000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "wearables_common", chance = 500000},
				{group = "wearables_uncommon", chance = 500000}
			}
		}
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,pikemanmaster)
}

CreatureTemplates:addCreatureTemplate(singing_mountain_clan_initiate, "singing_mountain_clan_initiate")
