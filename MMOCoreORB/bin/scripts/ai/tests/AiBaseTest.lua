package.path = package.path .. ";scripts/ai/actions/?.lua;scripts/ai/?.lua"

includeFile = spy.new(function() end)
require("ai")

describe("Basic Behavior Tests", function()
  it("Defines the Behavior Object", function()
    assert.is.truthy(Behavior)
  end)

end)
