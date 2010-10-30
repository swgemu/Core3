purbole_youth = Creature:new {
	objectName = "@mob/creature_names:purbole_youth",
	socialGroup = "Purbole",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 12,
	hideType = "hide_bristley",
	hideAmount = 8,
	boneType = "bone_mammal",
	boneAmount = 8,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/purbole_youth.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(purbole_youth, "purbole_youth")