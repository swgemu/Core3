om_aynat_chef = Creature:new {
	objectName = "@mob/creature_names:commoner",
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

	templates = {	"object/mobile/dressed_chef_trainer_devaronian_male_01.iff",
			"object/mobile/dressed_chef_trainer_human_female_01.iff",
			"object/mobile/dressed_chef_trainer_human_male_01.iff"},

	lootGroups = {},
	weapons = {},
	conversationTemplate = "om_aynat_mission_target_convotemplate",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(om_aynat_chef, "om_aynat_chef")
