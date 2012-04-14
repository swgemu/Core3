aakuan_spice_guard = Creature:new {
	objectName = "",
	customName = "Aa'kuan Spice Guard",
	socialGroup = "Aa'kuan",
	pvpFaction = "Aa'kuan",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {30,30,-1,0,0,-1,0,-1,-1},
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

	templates = {"object/mobile/dressed_aakuan_defender_human_male_01.iff"},
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

CreatureTemplates:addCreatureTemplate(aakuan_spice_guard, "aakuan_spice_guard")