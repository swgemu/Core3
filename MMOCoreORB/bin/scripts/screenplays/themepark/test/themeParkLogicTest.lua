local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
includeFile = spy.new(function() end)

require("screenplays.themepark.themeParkLogic")

describe("Theme Park Logic", function()
  it("Defines the purple color of waypoints to the value 5.", function()
    assert.same(5, WAYPOINT_COLOR_PURPLE)
  end)

  it("Defines the value of the sit property to 1.", function()
    assert.same(1, SIT)
  end)

  it("Defines the value of the stand property to 0.", function()
    assert.same(0, STAND)
  end)

  it("Defines the crc code for the imperial faction.", function()
    assert.same(0xDB4ACC54, FACTIONIMPERIAL)
  end)

  it("Defines the crc code for the rebel faction.", function()
    assert.same(0x16148850, FACTIONREBEL)
  end)
end)
