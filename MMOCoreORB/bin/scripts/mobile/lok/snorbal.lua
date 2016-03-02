snorbal = Creature:new {
	objectName = "@mob/creature_names:snorbal",
	socialGroup = "snorbal",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 260,
	damageMax = 270,
	baseXp = 3005,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 545,
	hideType = "hide_leathery",
	hideAmount = 440,
	boneType = "bone_mammal",
	boneAmount = 400,
	milkType = "milk_wild",
	milk = 280,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/snorbal.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(snorbal, "snorbal")
