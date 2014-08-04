sleemo_delinquent = Creature:new {
	objectName = "@mob/creature_names:sleemo_delinquent",
	socialGroup = "sleemo_gang",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_thug_zabrak_male_01.iff",
				"object/mobile/dressed_hooligan_rodian_male_01.iff",
				"object/mobile/dressed_hoodlum_zabrak_male_01.iff"},
	lootGroups = {
	    {
	        groups = {
				{group = "junk", chance = 3200000},
				{group = "wearables_common", chance = 2000000},				
				{group = "rifles", chance = 700000},
				{group = "melee_knife", chance = 700000},
				{group = "pistols", chance = 700000},
				{group = "carbines", chance = 700000},
				{group = "printer_parts", chance = 1000000},
				{group = "loot_kit_parts", chance = 1000000},
				
	    	},
			lootChance = 2200000
		}
},
	weapons = {"pirate_weapons_light"},
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(sleemo_delinquent, "sleemo_delinquent")
