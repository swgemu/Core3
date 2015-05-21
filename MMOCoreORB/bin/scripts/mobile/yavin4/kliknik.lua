kliknik = Creature:new {
	objectName = "@mob/creature_names:kliknik",
	socialGroup = "kliknik",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {120,5,5,-1,5,-1,5,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	controlDeviceTemplate = "object/intangible/pet/kliknik_hue.iff",
	scale = 0.9,
	lootGroups = {
	    {
	        groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 1360000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik, "kliknik")
