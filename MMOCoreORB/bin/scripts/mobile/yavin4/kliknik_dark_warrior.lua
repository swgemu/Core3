kliknik_dark_warrior = Creature:new {
	objectName = "@mob/creature_names:kliknik_dark_warrior",
	socialGroup = "kliknik",
	faction = "",
	level = 40,
	chanceHit = 0.43,
	damageMin = 340,
	damageMax = 390,
	baseXp = 4006,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 0,
	resists = {160,140,25,25,25,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.15,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/kliknik_hue.iff",
	scale = 1.2,
	lootGroups = {
		{
			groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 1800000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_dark_warrior, "kliknik_dark_warrior")
