sharnaff = Creature:new {
	objectName = "@monster_name:sharnaff",
	socialGroup = "Sharnaff",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.380000,
	damageMin = 300,
	damageMax = 310,
	baseXp = 3005,
	baseHAM = 9600,
	baseHAMmax = 9600,
	armor = 0,
	resists = {0,0,0,20,20,20,20,50,-1},
	meatType = "meat_carnivore",
	meatAmount = 450,
	hideType = "hide_scaley",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/sharnaff.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sharnaff, "sharnaff")