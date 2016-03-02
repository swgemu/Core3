voritor_dasher = Creature:new {
	objectName = "@mob/creature_names:voritor_dasher",
	socialGroup = "voritor",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3005,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {20,-1,20,-1,-1,-1,-1,20,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_leathery",
	hideAmount = 30,
	boneType = "bone_avian",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_dasher.iff"},
	scale = 1.05,
	lootGroups = {
		{
			groups = {
				{group = "voritor_lizard_common", chance = 10000000}
			},
			lootChance = 1600000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"creatureareapoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(voritor_dasher, "voritor_dasher")
