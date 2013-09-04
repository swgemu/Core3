cor_imperial_pilot = Creature:new {
	objectName = "",
	customName = "an Imperial Pilot",
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/tatooine_npc/hedon_istee.iff"}, -- Need a naked human male template for clothing (see below.)
	lootGroups = {},
	weapons = {},
	conversationTemplate = "ImperialPilotConversationTemplate",
	outfit = "imperial_pilot_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(cor_imperial_pilot, "cor_imperial_pilot")
