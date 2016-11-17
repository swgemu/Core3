critic_quest_venthan = Creature:new {
	objectName = "@mob/creature_names:quest_crowd_pleaser_judge",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 85,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {10,10,10,10,10,10,10,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dressed_noble_fat_human_male_01.iff",
			"object/mobile/dressed_noble_fat_human_male_02.iff",
			"object/mobile/dressed_noble_fat_twilek_male_01.iff",
			"object/mobile/dressed_noble_fat_twilek_male_02.iff",
			"object/mobile/dressed_noble_fat_zabrak_male_01.iff",
			"object/mobile/dressed_noble_fat_zabrak_male_02.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "wearables_common", chance = 4000000}
			}
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = brawlernovice
}

CreatureTemplates:addCreatureTemplate(critic_quest_venthan, "critic_quest_venthan")
