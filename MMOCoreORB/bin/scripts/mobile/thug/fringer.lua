fringer = Creature:new {
	objectName = "@mob/creature_names:fringer",
	socialGroup = "Mercenary",
	pvpFaction = "",
	faction = "townsperson",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 55,
	damageMax = 65,
	baseXp = 147,
	baseHAM = 270,
	baseHAMmax = 330,
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/dressed_commoner_tatooine_rodian_male_02.iff",
				"object/mobile/dressed_commoner_naboo_human_male_02.iff",
				"object/mobile/dressed_commoner_tatooine_bith_male_05.iff"
	},
	lootGroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(fringer, "fringer")