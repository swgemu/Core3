alkhara_bandit = Creature:new {
	objectName = "@mob/creature_names:alkhara_bandit",
	socialGroup = "alkhara",
	pvpFaction = "alkhara",
	faction = "alkhara",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,10,10,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_alkhara_bandit.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 1500000}
			},
			lootChance = 3200000
		}				
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(alkhara_bandit, "alkhara_bandit")
