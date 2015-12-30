gambler = Creature:new {
	objectName = "@mob/creature_names:gambler",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "thug",
	faction = "thug",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = STALKER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_commoner_tatooine_nikto_male_02.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_01.iff",
		"object/mobile/dressed_commoner_naboo_twilek_female_01.iff",
		"object/mobile/dressed_commoner_naboo_human_female_03.iff",
		"object/mobile/dressed_commoner_tatooine_devaronian_male_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 2000000},
				{group = "pistols", chance = 1000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000}
			}
		}
	},
	weapons = {"pirate_weapons_light"},
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(gambler, "gambler")
