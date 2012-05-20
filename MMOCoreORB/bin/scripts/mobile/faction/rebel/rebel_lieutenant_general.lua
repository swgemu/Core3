rebel_lieutenant_general = Creature:new {
	objectName = "@mob/creature_names:rebel_lieutenant_general",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 27,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2822,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {20,20,20,30,-1,30,-1,-1,-1},
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
		"object/mobile/dressed_rebel_lieutenant_general_human_male_01.iff",
		"object/mobile/dressed_rebel_lieutenant_general_moncal_female_01.iff",
		"object/mobile/dressed_rebel_lieutenant_general_moncal_male_01.iff",
		"object/mobile/dressed_rebel_lieutenant_general_rodian_male_01.iff",
		"object/mobile/dressed_rebel_lieutenant_general_twilek_female_01.iff",
		"object/mobile/dressed_rebel_lieutenant_general_twilek_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 3600000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 4000000
		}		
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(rebel_lieutenant_general, "rebel_lieutenant_general")