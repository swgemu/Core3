mature_snorbal_female = Creature:new {
	objectName = "@mob/creature_names:mature_snorbal_female",
	socialGroup = "Snorbal",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3097,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {40,40,0,-1,-1,-1,-1,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 545,
	hideType = "hide_leathery",
	hideAmount = 440,
	boneType = "bone_mammal",
	boneAmount = 400,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/elder_snorbal_female.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mature_snorbal_female, "mature_snorbal_female")