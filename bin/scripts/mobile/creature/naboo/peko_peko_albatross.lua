peko_peko_albatross = Creature:new {
	objectName = "@mob/creature_names:peko_peko_albatross",
	socialGroup = "Great Peko Peko",
	pvpFaction = "",
	faction = "",
	level = 155,
	chanceHit = 7.750000,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 14694,
	baseHAM = 82500,
	baseHAMmax = 82500,
	armor = 0,
	resists = {100,80,30,80,80,90,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 400,
	hideType = "hide_wooly",
	hideAmount = 120,
	boneType = "bone_avian",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/peko_peko.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareacombo",""},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(peko_peko_albatross, "peko_peko_albatross")