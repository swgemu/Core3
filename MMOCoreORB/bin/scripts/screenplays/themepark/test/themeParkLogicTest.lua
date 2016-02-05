local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
includeFile = spy.new(function() end)

require("screenplays.themepark.themeParkLogic")

describe("Theme Park Logic", function()
  it("Defines the value of the sit property to 1.", function()
    assert.same(1, SIT)
  end)

  it("Defines the value of the stand property to 0.", function()
    assert.same(0, STAND)
  end)
end)
