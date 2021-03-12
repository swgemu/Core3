criminal_target_thug = Creature:new {
  objectName = "@mob/creature_names:thug",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "thug",
  faction = "thug",
  level = 7,
  chanceHit = 0.26,
  damageMin = 55,
  damageMax = 65,
  baseXp = 187,
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
  tamingChance = 0,
  ferocity = 0,
  pvpBitmask = ATTACKABLE,
  creatureBitmask = PACK,
  optionsBitmask = AIENABLED,
  diet = HERBIVORE,

  templates = {"thug"},
  lootGroups = {
    {
      groups = {
        {group = "task_loot_medallion_black_sun", chance = 10000000}
      },
      lootChance = 10000000
    }
  },
  weapons = {"pirate_weapons_light"},
  conversationTemplate = "",
  attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(criminal_target_thug, "criminal_target_thug")
