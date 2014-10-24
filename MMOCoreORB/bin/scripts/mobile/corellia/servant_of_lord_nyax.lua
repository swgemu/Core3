servant_of_lord_nyax = Creature:new {
	objectName = "@mob/creature_names:lord_nyax_servant",
	socialGroup = "followers_of_lord_nyax",
	pvpFaction = "followers_of_lord_nyax",
	faction = "followers_of_lord_nyax",
	level = 8,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_criminal_organized_human_male_01.iff",
		"object/mobile/dressed_emperors_hand_zabrak_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "nyax", chance = 2000000},
				{group = "pistols", chance = 4000000},
				{group = "rifles", chance = 4000000},
			},
			lootChance = 3300000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(servant_of_lord_nyax, "servant_of_lord_nyax")
