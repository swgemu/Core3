aakuan_anarchist = Creature:new {
	objectName = "",
	customName = "Aa'kuan Anarchist",
	socialGroup = "Aa'kuan",
	pvpFaction = "Aa'kuan",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3097,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {30,30,0,0,-1,-1,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_aakuan_follower_trandoshan_female_01.iff"},
	lootGroups = {
	    {
		    groups = {
				{group = "aakuan_common", chance = 4000000},
				{group = "armor_attachments", chance = 2000000},
				{group = "rifles", chance = 1300000},
				{group = "carbines", chance = 1300000},
				{group = "pistols", chance = 1400000}				
			},
		    lootChance = 7500000
		}
	},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aakuan_anarchist, "aakuan_anarchist")