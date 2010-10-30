deadly_hooded_rawl = Creature:new {
	objectName = "@mob/creature_names:rawl_deadly_hooded",
	socialGroup = "Fanned Rawl",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
	baseHAM = 1300,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,0,0,20,-1,0,0,0,-1},
	meatType = "",
	meatAmount = 25,
	hideType = "",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/fanned_rawl.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(deadly_hooded_rawl, "deadly_hooded_rawl")