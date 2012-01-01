wooded_paralope = Creature:new {
	objectName = "@mob/creature_names:wooded_parapole",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 147,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_wooly",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = 0,
	diet = HERBIVORE,

	templates = {"object/mobile/paralope.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(wooded_paralope, "wooded_paralope")