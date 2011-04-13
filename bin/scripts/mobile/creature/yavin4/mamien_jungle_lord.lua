mamien_jungle_lord = Creature:new {
	objectName = "@mob/creature_names:mamien_junglelord",
	socialGroup = "Mamien",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 2443,
	baseHAM = 7000,
	baseHAMmax = 7000,
	armor = 0,
	resists = {0,20,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 18,
	hideType = "hide_wooly",
	hideAmount = 18,
	boneType = "bone_mammal",
	boneAmount = 18,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mamien.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mamien_jungle_lord, "mamien_jungle_lord")