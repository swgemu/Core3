moveWaveattack = {
	{id="2047096269",	name="SelectorSpace",	pid="none"},
	{id="2726820896",	name="SequenceSpace",	pid="2047096269"},
	{id="3499818116",	name="IfSpace",	pid="2726820896"},
	{id="3004739680",	name="CheckEnginesDisabled",	pid="3499818116"},
	{id="2694634428",	name="SetDisabledEngineSpeed",	pid="2726820896"},
	{id="1232766482",	name="SequenceSpace",	pid="2047096269"},
	{id="2548093309",	name="IfSpace",	pid="1232766482"},
	{id="2990870941",	name="CheckDestination",	pid="2548093309"},
	{id="1338767648",	name="AlwaysFailSpace",	pid="1232766482"},
	{id="4112371132",	name="FindNextPosition",	pid="1338767648"}}
addAiTemplate("moveWaveattack", moveWaveattack)

