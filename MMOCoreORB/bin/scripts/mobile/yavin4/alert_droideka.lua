alert_droideka = Creature:new {
	objectName = "@mob/creature_names:geonosian_droideka_crazed",
	socialGroup = "geonosian",
	pvpFaction = "geonosian",
	faction = "",
	level = 39,
	chanceHit = 0.56,
	damageMin = 426,
	damageMax = 564,
	baseXp = 5650,
	baseHAM = 13183,
	baseHAMmax = 15124,
	armor = 1,
	resists = {30,30,-1,0,30,0,30,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/droideka.iff"},
	lootGroups = {
         {
			groups = {
				{group = "junk", chance = 6500000},
				{group = "nyms_common", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 3500000
	    }	
	},
	weapons = {"droid_droideka_ranged"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(alert_droideka, "alert_droideka")