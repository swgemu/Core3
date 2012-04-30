swooper = Creature:new {
	objectName = "@mob/creature_names:swooper",
	socialGroup = "swoop",
	pvpFaction = "cor_swoop",
	faction = "cor_swoop",
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_swooper_human_female_01.iff",
		"object/mobile/dressed_criminal_swooper_human_male_01.iff",
		"object/mobile/dressed_criminal_swooper_zabrak_female_01.iff",
		"object/mobile/dressed_criminal_swooper_zabrak_male_01.iff"},
	lootGroups = {
      	{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "loot_kits", chance = 3500000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 4500000
		}	
	},
	weapons = {"pirate_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(swooper, "swooper")
