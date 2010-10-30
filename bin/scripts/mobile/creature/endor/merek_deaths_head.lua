merek_deaths_head = Creature:new {
	objectName = "@mob/creature_names:merek_deaths_head",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 56,
	chanceHit = 0.550000,
	damageMin = 480,
	damageMax = 670,
	baseXp = 5464,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/merek.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(merek_deaths_head, "merek_deaths_head")