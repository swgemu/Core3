kelvus_miner = Creature:new {
	objectName = "",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {15,15,15,15,15,15,15,-1,-1},
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
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {	"commoner" },
				
	lootGroups = {},
	weapons = {},
	conversationTemplate = "kelvus_naria_mission_target_convotemplate",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(kelvus_miner, "kelvus_miner")
