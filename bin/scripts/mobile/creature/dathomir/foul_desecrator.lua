foul_desecrator = Creature:new {
	objectName = "@mob/creature_names:kamurith_foul_desecrator",
	socialGroup = "Kamurith",
	pvpFaction = "",
	faction = "",
	level = 60,
	chanceHit = 0.550000,
	damageMin = 470,
	damageMax = 650,
	baseXp = 5830,
	baseHAM = 12500,
	baseHAMmax = 12500,
	armor = 0,
	resists = {25,0,0,0,0,0,20,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_lizard.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongdisease",""},
		{"creatureareadisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(foul_desecrator, "foul_desecrator")