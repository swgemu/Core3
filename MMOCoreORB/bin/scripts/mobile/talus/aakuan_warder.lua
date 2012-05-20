aakuan_warder = Creature:new {
	objectName = "@mob/creature_names:aakuan_warder",
	socialGroup = "aakuans",
	pvpFaction = "aakuans",
	faction = "aakuans",
	level = 29,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 3005,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {30,30,15,15,15,-1,15,15,-1},
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
		"object/mobile/dressed_aakuan_warder_zabrak_female_01.iff",
		"object/mobile/dressed_aakuan_warder_zabrak_male_01.iff"},
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
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aakuan_warder, "aakuan_warder")