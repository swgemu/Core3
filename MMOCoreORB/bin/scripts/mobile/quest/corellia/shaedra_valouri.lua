shaedra_valouri = Creature:new {
	objectName = "@mob/creature_names:corsec_investigator",
	socialGroup = "corsec",
	faction = "corsec",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,5,5,5,5,5,5,5,-1},
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

	templates = {"object/mobile/dressed_corsec_detective_human_female_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "denell_kel_vannon_mission_target_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(shaedra_valouri, "shaedra_valouri")