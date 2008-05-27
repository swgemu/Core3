DROP TABLE `mail`

CREATE TABLE `mail` (
  `mail_id` int(11) NOT NULL auto_increment,
  `sender_name` text NOT NULL,
  `recv_name` text NOT NULL,
  `subject` text NOT NULL,
  `body` text,
  `time` int(10) unsigned default NULL,
  `attachment_id` mediumint(8) unsigned default NULL,
  `read` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (`mail_id`)
) ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1;
