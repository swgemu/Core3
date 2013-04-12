sleemo_vandal = Creature:new {
	objectName = "",
	customName = "Sleemo Vandal",
	socialGroup = "Sleemo Gang",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 675,
	baseHAMmax = 825,
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_hoodlum_zabrak_female_01.iff"},
	lootGroups = {
	    {
	        groups = {
				{group = "junk", chance = 7200000},
				{group = "rifles", chance = 700000},
				{group = "melee_knife", chance = 700000},
				{group = "pistols", chance = 700000},
				{group = "carbines", chance = 700000},
				
	    	},
			lootChance = 3500000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(sleemo_vandal, "sleemo_vandal")
