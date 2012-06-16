deliver_npc = Creature:new {
	objectName = "@mob/creature_names:Deliver_NPC",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 100,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {-1,-1,-1,-1,-1,-1,-1,-1,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = 264,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/dressed_commoner_fat_zabrak_male_01.iff","object/mobile/dressed_commoner_fat_zabrak_male_02.iff","object/mobile/dressed_commoner_fat_zabrak_female_01.iff","object/mobile/dressed_commoner_fat_zabrak_female_02.iff","object/mobile/dressed_commoner_fat_human_male_01.iff","object/mobile/dressed_commoner_fat_human_male_02.iff","object/mobile/dressed_commoner_fat_human_female_01.iff","object/mobile/dressed_commoner_fat_human_female_02.iff","object/mobile/dressed_commoner_fat_twilek_male_01.iff","object/mobile/dressed_commoner_fat_twilek_male_02.iff","object/mobile/dressed_commoner_fat_twilek_female_01.iff","object/mobile/dressed_commoner_fat_twilek_female_02.iff","object/mobile/dressed_commoner_old_zabrak_male_01.iff","object/mobile/dressed_commoner_old_zabrak_male_02.iff","object/mobile/dressed_commoner_old_zabrak_female_01.iff","object/mobile/dressed_commoner_old_zabrak_female_02.iff","object/mobile/dressed_commoner_old_human_male_01.iff","object/mobile/dressed_commoner_old_human_male_02.iff","object/mobile/dressed_commoner_old_human_female_01.iff","object/mobile/dressed_commoner_old_human_female_02.iff","object/mobile/dressed_commoner_old_twilek_male_01.iff","object/mobile/dressed_commoner_old_twilek_male_02.iff","object/mobile/dressed_commoner_old_twilek_female_01.iff","object/mobile/dressed_commoner_old_twilek_female_02.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "deliver_npc",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(deliver_npc, "deliver_npc")