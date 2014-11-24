enhanced_kliknik = Creature:new {
	objectName = "@mob/creature_names:geonosian_kliknik_force_strong",
	socialGroup = "geonosian_creature",
	pvpFaction = "",
	faction = "",
	level = 109,
	chanceHit = 2.2,
	damageMin = 675,
	damageMax = 1060,
	baseXp = 10360,
	baseHAM = 34000,
	baseHAMmax = 42000,
	armor = 2,
	resists = {40,40,10,195,-1,110,110,10,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "hide_scaley",
	hideAmount = 40,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 15,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/kliknik.iff"},
	scale = 1.4,
	lootGroups = {
	 {
	        groups = {
				{group = "geo_kliknik", chance = 10000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_kliknik, "enhanced_kliknik")
