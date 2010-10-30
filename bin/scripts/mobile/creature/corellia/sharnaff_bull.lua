sharnaff_bull = Creature:new {
	objectName = "@mob/creature_names:sharnaff_bull",
	socialGroup = "Sharnaff",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.410000,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3733,
	baseHAM = 10400,
	baseHAMmax = 10400,
	armor = 0,
	resists = {0,0,0,20,20,20,20,50,-1},
	meatType = "meat_carnivore",
	meatAmount = 482,
	hideType = "hide_scaley",
	hideAmount = 335,
	boneType = "bone_mammal",
	boneAmount = 200,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/sharnaff_bull.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sharnaff_bull, "sharnaff_bull")