spiked_slasher = Creature:new {
	objectName = "@mob/creature_names:voritor_spiked_slasher",
	socialGroup = "voritor",
	pvpFaction = "",
	faction = "",
	level = 58,
	chanceHit = 0.53,
	damageMin = 430,
	damageMax = 570,
	baseXp = 5647,
	baseHAM = 10000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {165,140,0,0,150,-1,120,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/voritor_lizard_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/voritor_lizard_hue.iff",
	scale = 1.3,
	lootGroups = {
		{
			groups = {
				{group = "voritor_lizard_common", chance = 10000000}
			},
			lootChance = 2600000
		}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(spiked_slasher, "spiked_slasher")
