USE `swgemu`;

DROP TABLE IF EXISTS `account_log`;
CREATE TABLE  `account_log` (
  `acclog_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` int(10) unsigned NOT NULL,
  `timestamp` int(10) unsigned NOT NULL,
  `ip_address` varchar(15) NOT NULL,
  PRIMARY KEY  (`acclog_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `account_bans`;
CREATE TABLE  `account_bans` (
  `ban_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` int(10) unsigned NOT NULL,
  `issuer_id` int(10) unsigned NOT NULL,
  `created` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `expires` int(10) unsigned NOT NULL default 0,
  `reason` tinytext NOT NULL,
  PRIMARY KEY  USING BTREE (`ban_id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1
