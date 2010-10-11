bol_pack_runner = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:bol_pack_runner",
	socialGroup = "Bol",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 230,
	damageMax = 240,
	range = 0,
	baseXp = 2637,
	baseHAM = 9100,
	armor = 0,
	resists = {25,25,0,0,-1,-1,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bol_pack_runner, "bol_pack_runner")
