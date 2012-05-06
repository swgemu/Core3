CREATE TABLE  `swgemu`.`character_bans` (
  `ban_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `account_id` int(10) unsigned NOT NULL,
  `issuer_id` int(10) unsigned NOT NULL,
  `name` tinytext NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `expires` int(10) unsigned NOT NULL DEFAULT '0',
  `reason` tinytext NOT NULL,
  PRIMARY KEY (`ban_id`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=28 DEFAULT CHARSET=latin1

CREATE TABLE  `swgemu`.`galaxy_bans` (
  `ban_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `account_id` int(10) unsigned NOT NULL,
  `issuer_id` int(10) unsigned NOT NULL,
  `galaxy_id` int(11) NOT NULL,
  `created` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `expires` int(10) unsigned NOT NULL DEFAULT '0',
  `reason` tinytext NOT NULL,
  PRIMARY KEY (`ban_id`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=23 DEFAULT CHARSET=latin1
