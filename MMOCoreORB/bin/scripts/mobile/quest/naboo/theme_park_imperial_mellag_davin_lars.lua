theme_park_imperial_mellag_davin_lars = Creature:new {
	objectName = "",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1200,
	baseHAMmax = 1400,
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

	templates = {"object/mobile/dressed_naboo_dissident.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "theme_park_loot_information", chance = 10000000},
			},
			lootChance = 10000000
		}			
	},
	weapons = {"rebel_weapons_light"},
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_mellag_davin_lars, "theme_park_imperial_mellag_davin_lars")
