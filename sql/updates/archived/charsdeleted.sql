# MySQL Navigator Xport
# Database: swgemu
# root@localhost

# CREATE DATABASE swgemu;
# USE swgemu;

#
# Table structure for table 'characters'
#

# DROP TABLE IF EXISTS characters;
CREATE TABLE `deleted_characters` (
  `character_oid` bigint(20) NOT NULL,
  `account_id` mediumint(8) unsigned NOT NULL default '0',
  `galaxy_id` int(5) unsigned NOT NULL default '0',
  `firstname` varchar(15) NOT NULL default '',
  `surname` varchar(20) default NULL,
  `race` tinyint(2) NOT NULL default '0',
  `gender` tinyint(1) NOT NULL default '0',
  `template` tinytext NOT NULL,
  PRIMARY KEY  (`character_oid`),
  KEY `acc_idx` (`account_id`)
) ENGINE=MyISAM AUTO_INCREMENT=4676 DEFAULT CHARSET=latin1;

