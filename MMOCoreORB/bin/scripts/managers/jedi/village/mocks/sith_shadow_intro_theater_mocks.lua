local SithShadowIntroTheater = require("managers.jedi.village.sith_shadow_intro_theater")

local realStart
local realUseTheaterDatapad

local SithShadowIntroTheaterMocks = SithShadowIntroTheater
SithShadowIntroTheaterMocks.mocks = {}

function SithShadowIntroTheaterMocks.mocks.setup()
	realStart = SithShadowIntroTheater.start
	realUseTheaterDatapad = SithShadowIntroTheater.useTheaterDatapad
end

function SithShadowIntroTheaterMocks.mocks.teardown()
	SithShadowIntroTheater.start = realStart
	SithShadowIntroTheater.useTheaterDatapad = realUseTheaterDatapad
end

function SithShadowIntroTheaterMocks.mocks.before_each()
	SithShadowIntroTheater.start = spy.new(function() end)
	SithShadowIntroTheater.useTheaterDatapad = spy.new(function() end)
end

function SithShadowIntroTheaterMocks.mocks.after_each()
end

return SithShadowIntroTheaterMocks
