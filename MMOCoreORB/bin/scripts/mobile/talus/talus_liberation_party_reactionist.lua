talus_liberation_party_reactionist = Creature:new {
	objectName = "@mob/creature_names:liberation_reactionist",
	socialGroup = "liberation_party",
	pvpFaction = "liberation_party",
	faction = "liberation_party",
	level = 19,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1426,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_talus_sif_mercenary_trand_01.iff"},
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

CreatureTemplates:addCreatureTemplate(talus_liberation_party_reactionist, "talus_liberation_party_reactionist")