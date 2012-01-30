imperial_research_captain_coa3 = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_army_captain",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 45,
	chanceHit = 0.46,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4461,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {0,35,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imperial_research_captain_coa3, "imperial_research_captain_coa3")