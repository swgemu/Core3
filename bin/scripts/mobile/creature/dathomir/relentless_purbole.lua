relentless_purbole = Creature:new {
	objectName = "@mob/creature_names:purbole_relentless",
	socialGroup = "Purbole",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1803,
	baseHAM = 7000,
	baseHAMmax = 7000,
	armor = 0,
	resists = {10,10,20,0,0,40,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 12,
	hideType = "hide_bristley",
	hideAmount = 8,
	boneType = "bone_mammal",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/purbole.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(relentless_purbole, "relentless_purbole")