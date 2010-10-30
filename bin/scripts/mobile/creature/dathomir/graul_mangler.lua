graul_mangler = Creature:new {
	objectName = "@mob/creature_names:graul_mangler",
	socialGroup = "Graul",
	pvpFaction = "",
	faction = "",
	level = 39,
	chanceHit = 0.430000,
	damageMin = 340,
	damageMax = 390,
	baseXp = 3915,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {40,15,60,60,60,0,-1,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 875,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/graul.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(graul_mangler, "graul_mangler")