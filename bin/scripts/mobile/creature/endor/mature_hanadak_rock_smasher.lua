mature_hanadak_rock_smasher = Creature:new {
	objectName = "@mob/creature_names:mature_hanadak_rock_smasher",
	socialGroup = "Hanadak",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3460,
	baseHAM = 9700,
	baseHAMmax = 9700,
	armor = 0,
	resists = {0,60,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/hanadak.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mature_hanadak_rock_smasher, "mature_hanadak_rock_smasher")