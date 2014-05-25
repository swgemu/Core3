sidoras_bey_missions =
  {
    {
      missionType = "retrieve",
      primarySpawns =
      {
        { npcTemplate = "sidoras_artisan", planetName = "rori", npcName = "Artisan" }
      },
      secondarySpawns = {},
      itemSpawns =
      {
        { itemTemplate = "object/tangible/mission/quest_item/sidoras_bey_q1_needed.iff", itemName = "Narmle Arts Gala Winner" }
      },
      rewards =
      {
        { rewardType = "credits", amount = 25 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "silaras_bey", planetName = "rori", npcName = "Silaras Bey" }
      },
      secondarySpawns = {
        { npcTemplate = "sidoras_thug", planetName = "rori", npcName = "a Thug" },
        { npcTemplate = "sidoras_thug", planetName = "rori", npcName = "a Thug" }
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 50 },
      }
    }
  }

npcMapSidorasBey =
  {
    {
      spawnData = { planetName = "rori", npcTemplate = "sidoras_bey", x = -5248.1, z = 80, y = -2387.4, direction = 90, cellID = 0, position = STAND },
      worldPosition = { x = -5248, y = -2387 },
      npcNumber = 1,
      stfFile = "@static_npc/rori/rori_narmle_sidoras_bey",
      missions = sidoras_bey_missions
    },

  }

SidorasBey = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapSidorasBey,
  className = "SidorasBey",
  screenPlayState = "sidoras_bey_quest",
  distance = 600
}

registerScreenPlay("SidorasBey", true)

sidoras_bey_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = SidorasBey
}
sidoras_bey_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = SidorasBey
}