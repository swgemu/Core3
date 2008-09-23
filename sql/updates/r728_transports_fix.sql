UPDATE ticket_terminals,transports SET ticket_terminals.pos_z = transports.spawn_z WHERE transport_id = transports.id AND ticket_terminals.id < 42;

UPDATE ticket_collectors,transports SET ticket_collectors.pos_z = transports.spawn_z WHERE transport_id = transports.id AND ticket_collectors.id < 42;



