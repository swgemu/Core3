talus_liberation_party_activist = Creature:new {
	objectName = "@mob/creature_names:liberation_activist",
	socialGroup = "liberation_party",
	pvpFaction = "liberation_party",
	faction = "liberation_party",
	level = 21,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1803,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {10,25,10,-1,10,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_talus_sif_mercenary_rodian_01.iff"},
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
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(talus_liberation_party_activist, "talus_liberation_party_activist")