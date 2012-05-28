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
				{group = "junk", chance = 3000000},
				{group = "aakuan_common", chance = 1500000},
				{group = "armor_attachments", chance = 500000},
				{group = "rifles", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "pistols", chance = 1000000}				
			},
		    lootChance = 3500000
		}
	},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(aakuari_assassin, "aakuari_assassin")