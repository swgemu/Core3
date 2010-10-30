giant_dune_kimogila = Creature:new {
	objectName = "@mob/creature_names:giant_dune_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 153,
	chanceHit = 8.500000,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14504,
	baseHAM = 90000,
	baseHAMmax = 90000,
	armor = 0,
	resists = {65,80,65,100,65,65,100,65,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_dune_kimogila.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareacombo",""},
		{"creatureareadisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_dune_kimogila, "giant_dune_kimogila")