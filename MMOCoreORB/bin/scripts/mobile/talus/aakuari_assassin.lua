aakuari_assassin = Creature:new {
	objectName = "",
	customName = "an Aa'kuan Assassin",
	socialGroup = "aakuans",
	pvpFaction = "aakuans",
	faction = "aakuans",
	level = 31,
	chanceHit = 0.37,
	damageMin = 270,
	damageMax = 280,
	baseXp = 3188,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {40,40,0,0,0,-1,0,0,-1},
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

	templates = {
		"object/mobile/dressed_aakuan_follower_trandoshan_female_01.iff",
		"object/mobile/dressed_aakuan_follower_trandoshan_male_01.iff"},
	lootGroups = {
	    {
		    groups = {
				{group = "aakuan_common", chance = 4000000},
				{group = "armor_attachments", chance = 2000000},
				{group = "rifles", chance = 1300000},
				{group = "carbines", chance = 1300000},
				{group = "pistols", chance = 1400000}				
			},
		    lootChance = 6000000
		}	
	},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aakuari_assassin, "aakuari_assassin")