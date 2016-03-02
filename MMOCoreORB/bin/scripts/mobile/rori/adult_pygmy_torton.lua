adult_pygmy_torton = Creature:new {
	objectName = "@mob/creature_names:torton_pygmy_adult",
	socialGroup = "torton",
	faction = "",
	level = 20,
	chanceHit = 0.31,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {120,120,5,5,5,-1,-1,200,-1},
	meatType = "meat_carnivore",
	meatAmount = 600,
	hideType = "hide_wooly",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 600,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/torton_hue.iff"},
	scale = .55,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(adult_pygmy_torton, "adult_pygmy_torton")
