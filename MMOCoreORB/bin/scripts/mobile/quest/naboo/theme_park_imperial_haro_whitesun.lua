theme_park_imperial_haro_whitesun = Creature:new {
	objectName = "@mob/creature_names:moisture_farmer",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 11,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 356,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_moisture_farmer.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "theme_park_loot_information", chance = 10000000},
			},
			lootChance = 10000000
		}			
	},
	weapons = {"rebel_weapons_light"},
	attacks = merge(marksmanmid,brawlermid)
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_haro_whitesun, "theme_park_imperial_haro_whitesun")
