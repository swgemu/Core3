majordomo_quest_bardo = Creature:new {
	objectName = "@mob/creature_names:noble",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,


	templates = {"object/mobile/dressed_noble_old_twk_female_02.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "bardo_klinj_mission_target_convotemplate",
	attacks = merge(brawlermaster,teraskasinovice)
}

CreatureTemplates:addCreatureTemplate(majordomo_quest_bardo, "majordomo_quest_bardo")
