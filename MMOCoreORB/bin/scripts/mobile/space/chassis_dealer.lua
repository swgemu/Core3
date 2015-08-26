chassis_dealer = Creature:new {
	objectName = "",
	customName = "Chassis Dealer",
	socialGroup = "townsperson",
	faction = "townsperson",
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

	templates = {
		"object/mobile/space_chassis_broker_01.iff",
		"object/mobile/space_chassis_broker_02.iff",
		"object/mobile/space_chassis_broker_03.iff",
		"object/mobile/space_chassis_broker_04.iff",
		"object/mobile/space_chassis_broker_05.iff"
	},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "chassis_dealer_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(chassis_dealer, "chassis_dealer")
