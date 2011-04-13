purbole_stalker = Creature:new {
	objectName = "@mob/creature_names:purbole_stalker",
	socialGroup = "Purbole",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.320000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {0,20,0,-1,-1,35,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 11,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/purbole.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(purbole_stalker, "purbole_stalker")