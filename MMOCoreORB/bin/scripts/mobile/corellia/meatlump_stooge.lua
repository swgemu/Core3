meatlump_stooge = Creature:new {
  objectName = "@mob/creature_names:meatlump_stooge",
  randomNameType = NAME_GENERIC,
  randomNameTag = true,
  socialGroup = "meatlump",
  faction = "meatlump",
  level = 7,
  chanceHit = 0.260000,
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
  tamingChance = 0.000000,
  ferocity = 0,
  pvpBitmask = ATTACKABLE,
  creatureBitmask = PACK,
  diet = HERBIVORE,

  templates = {"thug"},
  lootGroups = {
    {
      groups = {
        {group = "junk", chance = 2900000},
        {group = "loot_kit_parts", chance = 1500000},
        {group = "color_crystals", chance = 100000},
        {group = "tailor_components", chance = 500000},
        {group = "meatlump_common", chance = 5000000}
      }
    }
  },
  weapons = {"pirate_weapons_light"},
  reactionStf = "@npc_reaction/slang",
  attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(meatlump_stooge, "meatlump_stooge")
