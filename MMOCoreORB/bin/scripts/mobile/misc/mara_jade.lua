mara_jade = Creature:new {
	objectName = "@mob/creature_names:mara_jade",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
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
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 264,
	diet = HERBIVORE,

	templates = {"object/mobile/mara_jade.iff"},
	lootGroups = {},
	weapons = {},
	outfit = "mara_jade_outfit",
	conversationTemplate = "theme_park_imperial_mission_target_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mara_jade, "mara_jade")
