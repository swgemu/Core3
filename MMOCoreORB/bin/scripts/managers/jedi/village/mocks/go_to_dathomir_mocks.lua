local GoToDathomir = require("managers.jedi.village.go_to_dathomir")

local realStart

local GoToDathomirMocks = GoToDathomir
GoToDathomirMocks.mocks = {}

function GoToDathomirMocks.mocks.setup()
	realStart = GoToDathomir.start
end

function GoToDathomirMocks.mocks.teardown()
	GoToDathomir.start = realStart
end

function GoToDathomirMocks.mocks.before_each()
	GoToDathomir.start = spy.new(function() end)
end

function GoToDathomirMocks.mocks.after_each()
end

return GoToDathomirMocks
