race_rival_quest_ignar = Creature:new {
	objectName = "@mob/creature_names:chadra_fan_male",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 1180,
	baseHAMmax = 1220,
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/chadra_fan_male.iff",
		"object/mobile/dressed_chadra_fan_m_01.iff",
		"object/mobile/dressed_chadra_fan_m_02.iff",
		"object/mobile/dressed_chadra_fan_m_03.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "ignar_ominaz_mission_target_convotemplate",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(race_rival_quest_ignar, "race_rival_quest_ignar")
