seeker = Creature:new {
	objectName = "@droid_name:probe_droid",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 1,
	chanceHit = 0.0,
	damageMin = 0,
	damageMax = 0,
	baseXp = 0,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/creature/npc/droid/crafted/probe_droid.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(seeker, "seeker")