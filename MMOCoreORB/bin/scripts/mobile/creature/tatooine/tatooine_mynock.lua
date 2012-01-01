tatooine_mynock = Creature:new {
	objectName = "@mob/creature_names:tatooine_mynock",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 3,
	chanceHit = 0.23,
	damageMin = 35,
	damageMax = 45,
	baseXp = 45,
	baseHAM = 90,
	baseHAMmax = 110,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 50,
	hideType = "hide_leathery",
	hideAmount = 70,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/mynock.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(tatooine_mynock, "tatooine_mynock")