gambler = Creature:new {
	objectName = "@mob/creature_names:gambler",
	socialGroup = "thug",
	pvpFaction = "thug",
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
	lootGroups = {},
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(gambler, "gambler")