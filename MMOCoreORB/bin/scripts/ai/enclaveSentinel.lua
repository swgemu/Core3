awareEnclavesentinel = {
	{id="1074780145",	name="Selector",	pid="none"},
	{id="2877429880",	name="LookForTarget",	pid="1074780145"},
	{id="1842231240",	name="Sequence",	pid="2877429880"},
	{id="2100210710",	name="Selector",	pid="1842231240"},
	{id="2453213506",	name="If",	pid="2100210710"},
	{id="2897258589",	name="CheckProspectIsType",	pid="2453213506",	args={condition=PLAYER}},
	{id="2845873207",	name="If",	pid="2100210710"},
	{id="119310356",	name="CheckProspectJediTrial",	pid="2845873207"},
	{id="680465367",	name="If",	pid="1842231240"},
	{id="14270026",	name="CheckProspectInRange",	pid="680465367",	args={condition=32.0}},
	{id="954339847",	name="AlwaysFail",	pid="1074780145"},
	{id="1358554592",	name="Sequence",	pid="954339847"},
	{id="2583246458",	name="EraseBlackboard",	pid="1358554592",	args={param="aggroMod"}},
	{id="966727443",	name="EraseBlackboard",	pid="1358554592",	args={param="targetProspect"}}}
addAiTemplate("awareEnclavesentinel", awareEnclavesentinel)

