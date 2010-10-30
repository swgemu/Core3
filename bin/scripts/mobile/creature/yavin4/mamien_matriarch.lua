mamien_matriarch = Creature:new {
	objectName = "@mob/creature_names:mamien_matriarch",
	socialGroup = "Mamien",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,20,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 17,
	hideType = "hide_wooly",
	hideAmount = 20,
	boneType = "bone_mammal",
	boneAmount = 20,
	milk = 0,
	tamingChance = 0.100000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mamien.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mamien_matriarch, "mamien_matriarch")