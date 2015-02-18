kardeer = Creature:new {
	objectName = "@mob/creature_names:kardeer",
	socialGroup = "valarian",
	faction = "valarian",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {20,0,40,60,-1,-1,-1,-1,-1},
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/kardeer.iff"},
	lootGroups = {},
	weapons = {},
	reactionStf = "@npc_reaction/slang",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(kardeer, "kardeer")
