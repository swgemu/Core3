draya_korbinari_bounty_hunter = Creature:new {
	objectName = "@mob/creature_names:bounty_hunter",
	customName = "",
	socialGroup = "",
	faction = "",
	level = 12,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 187,
	baseHAM = 500,
	baseHAMmax = 600,
	armor = 0,
	resists = {0,0,0,10,10,0,0,-1,-1},
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
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_kobola_miner_human_male_01.iff"},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	lootGroups = {
		{
			groups = {
				{ group = "junk", chance = 10000000},
			},
 			lootChance = 2200000
		},
	},
	outfit = "",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(draya_korbinari_bounty_hunter, "draya_korbinari_bounty_hunter")
