purbole_hunter = Creature:new {
	objectName = "@mob/creature_names:purbole_hunter",
	socialGroup = "Purbole",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 2006,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {25,25,0,-1,-1,45,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 10,
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
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(purbole_hunter, "purbole_hunter")