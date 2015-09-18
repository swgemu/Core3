fbase_rebel_command_security_guard_hard = Creature:new {
	objectName = "@mob/creature_names:fbase_rebel_command_security_guard_hard",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rebel",
	faction = "rebel",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 5000,
	baseHAM = 10000,
	baseHAMmax = 12500,
	armor = 1,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rebel_scout_bothan_male_01.iff",
			"object/mobile/dressed_rebel_scout_human_female_01.iff",
			"object/mobile/dressed_rebel_scout_human_female_02.iff",
			"object/mobile/dressed_rebel_scout_human_male_01.iff",
			"object/mobile/dressed_rebel_scout_rodian_male_01.iff",
			"object/mobile/dressed_rebel_scout_zabrak_female_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 4700000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(marksmanmid,brawlermid)
}

CreatureTemplates:addCreatureTemplate(fbase_rebel_command_security_guard_hard, "fbase_rebel_command_security_guard_hard")
