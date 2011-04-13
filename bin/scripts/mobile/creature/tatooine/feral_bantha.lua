feral_bantha = Creature:new {
	objectName = "@mob/creature_names:feral_bantha",
	socialGroup = "Bantha",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 1300,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,10,0,30,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 415,
	hideType = "hide_wooly",
	hideAmount = 305,
	boneType = "bone_mammal",
	boneAmount = 215,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/bantha.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(feral_bantha, "feral_bantha")