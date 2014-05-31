xarot_singing_mountain_clan_witch = Creature:new {
	objectName = "",
	socialGroup = "mtn_clan",
	pvpFaction = "mtn_clan",
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
				{group = "task_loot_singing_mountain_clan_force_crystal", chance = 10000000},

			},
			lootChance = 10000000
		},
	},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,pikemanmaster)
}

CreatureTemplates:addCreatureTemplate(xarot_singing_mountain_clan_witch, "xarot_singing_mountain_clan_witch")