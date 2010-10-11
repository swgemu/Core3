pygmy_torton_protector = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:torton_pygmy_protector",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.330000,
	damageMin = 220,
	damageMax = 230,
	range = 0,
	baseXp = 2219,
	baseHAM = 3900,
	armor = 0,
	resists = {25,25,0,0,0,-1,-1,45,-1},
	meatType = "meat_carnivore",
	meatAmount = 600,
	hideType = "hide_wooly",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 600,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(pygmy_torton_protector, "pygmy_torton_protector")
