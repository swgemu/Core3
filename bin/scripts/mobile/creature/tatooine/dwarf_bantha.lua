dwarf_bantha = Creature:new {
	objectName = "@mob/creature_names:dwarf_bantha",
	socialGroup = "Bantha",
	pvpFaction = "",
	faction = "",
	level = 11,
	chanceHit = 0.290000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 1300,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,0,0,15,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 300,
	hideType = "hide_wooly",
	hideAmount = 200,
	boneType = "bone_mammal",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/dwarf_bantha.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dwarf_bantha, "dwarf_bantha")