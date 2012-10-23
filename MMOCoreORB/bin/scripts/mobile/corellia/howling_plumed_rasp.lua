howling_plumed_rasp = Creature:new {
	objectName = "@mob/creature_names:howling_plumed_rasp",
	socialGroup = "rasp",
	pvpFaction = "",
	faction = "",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 85,
	baseHAM = 113,
	baseHAMmax = 135,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 3,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/plumed_rasp_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(howling_plumed_rasp, "howling_plumed_rasp")