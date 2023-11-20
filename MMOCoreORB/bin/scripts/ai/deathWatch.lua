awareDeathwatch = {
	{id="3576396563",	name="Selector",	pid="none"},
	{id="2392826049",	name="LookForTarget",	pid="3576396563"},
	{id="1753986571",	name="Sequence",	pid="2392826049"},
	{id="709193771",	name="If",	pid="1753986571"},
	{id="1717463806",	name="CheckProspectIsType",	pid="709193771",	args={condition=PLAYERTYPE}},
	{id="742936927",	name="If",	pid="1753986571"},
	{id="1696039854",	name="CheckProspectInRange",	pid="742936927",	args={condition=32.0}},
	{id="4189435154",	name="TreeSocket",	pid="1753986571",	args={slot=AGGRO}},
	{id="1630441813",	name="AlwaysFail",	pid="3576396563"},
	{id="3623506489",	name="Sequence",	pid="1630441813"},
	{id="3030419901",	name="EraseBlackboard",	pid="3623506489",	args={param="aggroMod"}},
	{id="4221251452",	name="EraseBlackboard",	pid="3623506489",	args={param="targetProspect"}}}
addAiTemplate("awareDeathwatch", awareDeathwatch)
