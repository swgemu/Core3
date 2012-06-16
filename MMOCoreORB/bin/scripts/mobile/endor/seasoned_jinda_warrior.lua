seasoned_jinda_warrior = Creature:new {
	objectName = "@mob/creature_names:seasoned_jinda_warrior",
	socialGroup = "jinda_tribe",
	pvpFaction = "jinda_tribe",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3460,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {-1,50,-1,50,50,70,50,-1,-1},
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
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
			"object/mobile/jinda_male.iff",
			"object/mobile/jinda_female.iff",
			"object/mobile/jinda_male_01.iff",
			"object/mobile/jinda_female_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(seasoned_jinda_warrior, "seasoned_jinda_warrior")