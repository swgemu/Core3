#ifndef JUKEBOXSONG_H_
#define JUKEBOXSONG_H_

#include "engine/engine.h"

class JukeboxSong : public Object {

protected:
	String stringId, songFile;

public:
	JukeboxSong() {
	}

	~JukeboxSong() {
	}

	JukeboxSong(const JukeboxSong& obj) : Object() {
		stringId = obj.stringId;
		songFile = obj.songFile;
	}

	JukeboxSong(String sid, String sfile) : Object() {
		stringId = sid;
		songFile = sfile;
	}

	String getSongFile() {
		return songFile;
	}

	String getStringId() {
		return stringId;
	}
};

#endif /* JUKEBOXSONG_H_ */
