local Glowing = require("managers.jedi.village.glowing")
local realCheckForceStatusCommand
local realOnPlayerLoggedIn

local GlowingMocks = Glowing
GlowingMocks.mocks = {}
GlowingMocks.realObject = Glowing

function GlowingMocks.mocks.setup()
	realCheckForceStatusCommand = Glowing.checkForceStatusCommand
	realOnPlayerLoggedIn = Glowing.onPlayerLoggedIn
end

function GlowingMocks.mocks.teardown()
	Glowing.checkForceStatusCommand = realCheckForceStatusCommand
	Glowing.onPlayerLoggedIn = realOnPlayerLoggedIn
end

function GlowingMocks.mocks.before_each()
	Glowing.checkForceStatusCommand = spy.new(function() end)
	Glowing.onPlayerLoggedIn = spy.new(function() end)
end

function GlowingMocks.mocks.after_each()
end

return GlowingMocks
