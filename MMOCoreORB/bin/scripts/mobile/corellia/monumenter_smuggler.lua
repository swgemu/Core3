monumenter_smuggler = Creature:new {
	objectName = "@mob/creature_names:monumenter_smuggler",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "monumenter",
	faction = "monumenter",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1200,
	baseHAMmax = 1400,
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mugger.iff",
		"object/mobile/dressed_criminal_thug_human_male_01.iff",
		"object/mobile/dressed_criminal_thug_human_male_02.iff",
		"object/mobile/dressed_criminal_thug_rodian_female_01.iff",
		"object/mobile/dressed_criminal_thug_rodian_male_01.iff",
		"object/mobile/dressed_criminal_thug_trandoshan_female_01.iff",
		"object/mobile/dressed_criminal_thug_trandoshan_male_01.iff",
		"object/mobile/dressed_criminal_thug_zabrak_female_01.iff",
		"object/mobile/dressed_criminal_thug_zabrak_male_01.iff",
		"object/mobile/dressed_crook_zabrak_female_01.iff",
		"object/mobile/dressed_crook_zabrak_male_01.iff",
		"object/mobile/dressed_desperado_bith_female_01.iff",
		"object/mobile/dressed_desperado_bith_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 2000000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
				{group = "carbines", chance = 1000000},
			}
		}
	},
	weapons = {"ranged_weapons"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(monumenter_smuggler, "monumenter_smuggler")
