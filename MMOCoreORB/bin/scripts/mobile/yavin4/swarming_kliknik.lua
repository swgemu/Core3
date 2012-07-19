swarming_kliknik = Creature:new {
	objectName = "@mob/creature_names:kliknik_swarming",
	socialGroup = "kliknik",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.27,
	damageMin = 170,
	damageMax = 180,
	baseXp = 356,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {20,0,0,-1,0,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik_hue.iff"},
	lootGroups = {
	 {
	        groups = {
				{group = "kliknik_common", chance = 3300000}
			},
			lootChance = 4300000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(swarming_kliknik, "swarming_kliknik")