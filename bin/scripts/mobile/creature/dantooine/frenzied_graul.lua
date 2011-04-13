frenzied_graul = Creature:new {
	objectName = "@mob/creature_names:frenzied_graul",
	socialGroup = "Graul",
	pvpFaction = "",
	faction = "",
	level = 56,
	chanceHit = 0.500000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5464,
	baseHAM = 10600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {65,35,90,90,90,-1,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 950,
	boneType = "bone_mammal",
	boneAmount = 855,
	milk = 0,
	tamingChance = 0.010000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/frenzied_graul.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareableeding",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(frenzied_graul, "frenzied_graul")