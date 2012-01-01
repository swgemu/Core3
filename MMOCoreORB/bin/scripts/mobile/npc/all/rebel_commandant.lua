rebel_commandant = Creature:new {
	objectName = "@mob/creature_names:Rebel_Commandant",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 151,
	chanceHit = 8.5,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14314,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 0,
	resists = {50,65,0,0,30,30,80,65,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(rebel_commandant, "rebel_commandant")