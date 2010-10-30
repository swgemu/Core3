stunted_woolamander = Creature:new {
	objectName = "@mob/creature_names:stunted_woolamander",
	socialGroup = "Woolamander",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {10,0,0,0,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/stintaril.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stunted_woolamander, "stunted_woolamander")