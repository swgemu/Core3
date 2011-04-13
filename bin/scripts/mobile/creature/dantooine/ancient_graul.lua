ancient_graul = Creature:new {
	objectName = "@mob/creature_names:ancient_graul",
	socialGroup = "Graul",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.470000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4825,
	baseHAM = 10800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {60,45,70,70,70,-1,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 875,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/graul.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ancient_graul, "ancient_graul")