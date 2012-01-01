dune_kimogila = Creature:new {
	objectName = "@mob/creature_names:dune_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 123,
	chanceHit = 4,
	damageMin = 785,
	damageMax = 1280,
	baseXp = 11671,
	baseHAM = 53000,
	baseHAMmax = 65000,
	armor = 2,
	resists = {40,65,15,100,-1,15,100,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kimogila.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dune_kimogila, "dune_kimogila")