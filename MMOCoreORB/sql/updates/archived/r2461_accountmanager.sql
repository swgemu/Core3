
/** Kill the old account table to avoid confusion **/
DROP TABLE IF EXISTS `swgemu`.`account`;

DROP TABLE IF EXISTS `swgemu`.`account_bans`;
CREATE TABLE  `swgemu`.`account_bans` (
  `ban_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` int(10) unsigned NOT NULL,
  `issuer_id` int(10) unsigned NOT NULL,
  `created` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `expires` timestamp NOT NULL default '0000-00-00 00:00:00',
  `reason` tinytext NOT NULL,
  PRIMARY KEY  USING BTREE (`ban_id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `swgemu`.`account_log`;
CREATE TABLE  `swgemu`.`account_log` (
  `acclog_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` int(10) unsigned NOT NULL,
  `timestamp` int(10) unsigned NOT NULL,
  `event_type` bit(1) NOT NULL,
  PRIMARY KEY  (`acclog_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `swgemu`.`accounts`;
CREATE TABLE  `swgemu`.`accounts` (
  `account_id` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(32) NOT NULL,
  `password` varchar(255) NOT NULL,
  `station_id` int(10) unsigned NOT NULL,
  `created` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `active` tinyint(1) NOT NULL default '1',
  `email` varchar(255) NOT NULL,
  `ban_id` int(10) unsigned NOT NULL,
  `admin_level` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  USING BTREE (`account_id`)
) ENGINE=MyISAM AUTO_INCREMENT=5 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

DROP TABLE IF EXISTS `swgemu`.`sessions`;
CREATE TABLE  `swgemu`.`sessions` (
  `account_id` int(10) unsigned NOT NULL default '0',
  `session_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  USING BTREE (`account_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;