kliknik_defender = Creature:new {
	objectName = "@mob/creature_names:kliknik_defender",
	socialGroup = "kliknik",
	faction = "",
	level = 27,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2730,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {140,125,135,135,135,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
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

	templates = {"object/mobile/kliknik_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/kliknik_hue.iff",
	scale = 1.05,
	lootGroups = {
	 {
	        groups = {
				{group = "kliknik_common", chance = 10000000}
			},
			lootChance = 2000000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_defender, "kliknik_defender")
