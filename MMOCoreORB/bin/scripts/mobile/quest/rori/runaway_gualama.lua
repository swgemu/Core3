runaway_gualama = Creature:new {
	objectName = "@mob/creature_names:gualama",
	socialGroup = "gualama",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1000,
	baseHAMmax = 1200,
	armor = 1,
	resists = {5,5,5,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 200,
	hideType = "hide_wooly",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 90,
	milkType = "milk_wild",
	milk = 100,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 264,
	diet = CARNIVORE,

	templates = {"object/mobile/gualama.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "hefsen_zindalai_mission_target_convotemplate",
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(runaway_gualama, "runaway_gualama")
