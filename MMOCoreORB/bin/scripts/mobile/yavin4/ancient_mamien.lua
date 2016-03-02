ancient_mamien = Creature:new {
	objectName = "@mob/creature_names:mamien_ancient",
	socialGroup = "mamien",
	faction = "",
	level = 24,
	chanceHit = 0.34,
	damageMin = 200,
	damageMax = 210,
	baseXp = 2543,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {120,135,10,10,10,10,10,-1,-1},
	meatType = "meat_wild",
	meatAmount = 20,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/mamien_ancient.iff"},
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(ancient_mamien, "ancient_mamien")
