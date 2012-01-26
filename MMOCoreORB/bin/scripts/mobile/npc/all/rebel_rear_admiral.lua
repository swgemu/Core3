rebel_rear_admiral = Creature:new {
	objectName = "@mob/creature_names:corvette_rebel_rear_admiral",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 200,
	chanceHit = 16,
	damageMin = 1145,
	damageMax = 2000,
	baseXp = 19008,
	baseHAM = 160000,
	baseHAMmax = 195000,
	armor = 3,
	resists = {70,75,0,0,30,30,80,65,-1},
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

CreatureTemplates:addCreatureTemplate(rebel_rear_admiral, "rebel_rear_admiral")