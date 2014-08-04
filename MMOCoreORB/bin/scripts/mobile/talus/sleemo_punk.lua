sleemo_punk = Creature:new {
	objectName = "@mob/creature_names:sleemo_punk",
	socialGroup = "sleemo_gang",
	pvpFaction = "",
	faction = "",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
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
	creatureBitmask = STALKER + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_hooligan_rodian_male_01.iff"},
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

CreatureTemplates:addCreatureTemplate(sleemo_punk, "sleemo_punk")
