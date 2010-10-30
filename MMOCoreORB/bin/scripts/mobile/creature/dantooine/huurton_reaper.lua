huurton_reaper = Creature:new {
	objectName = "@mob/creature_names:huurton_reaper",
	socialGroup = "Huurton",
	pvpFaction = "",
	faction = "",
	level = 84,
	chanceHit = 0.900000,
	damageMin = 620,
	damageMax = 950,
	baseXp = 8038,
	baseHAM = 13500,
	baseHAMmax = 13500,
	armor = 0,
	resists = {35,35,0,40,100,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 25,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/huurton.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(huurton_reaper, "huurton_reaper")