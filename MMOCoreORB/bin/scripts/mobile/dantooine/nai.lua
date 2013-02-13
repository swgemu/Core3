nai = Creature:new {
	objectName = "",
	customName = "Nai (a Rogue Trooper)",	
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 18,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {15,15,15,15,15,15,15,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_first_lieutenant_bothan_male_01.iff",
		"object/mobile/dressed_rebel_first_lieutenant_human_female_01.iff",
		"object/mobile/dressed_rebel_first_lieutenant_human_male_01.iff",
		"object/mobile/dressed_rebel_first_lieutenant_moncal_female_01.iff",
		"object/mobile/dressed_rebel_first_lieutenant_moncal_female_02.iff",
		"object/mobile/dressed_rebel_first_lieutenant_sullustan_male_01.iff"},
	lootGroups = {
		{
	        groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 5700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
                {group = "melee_weapons", chance = 1000000},
                {group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000}
			},
			lootChance = 3000000
		}	
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "jatrian_lytus_mission_target_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nai, "nai")
