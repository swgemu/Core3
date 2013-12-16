medic = Creature:new {
	objectName = "@mob/creature_names:medic",
	generateRandomName = true,
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 55,
	damageMax = 65,
	baseXp = 147,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {
				"object/mobile/dressed_doctor_trainer_human_female_01.iff",
				"object/mobile/dressed_doctor_trainer_moncal_male_01.iff",
				"object/mobile/dressed_mercenary_elite_medic_human_male_01.iff",
	},
	lootGroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(medic, "medic")
