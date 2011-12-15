#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "vlc/vlc.h"
using namespace std;

int main(int argc, char** argv) {
cout << "Phitherek_' s Experimental LibVLC Streamer v. 0.1 (c) 2011 by Phitherek_" << endl;
bool loop = false;
libvlc_instance_t* inst;
libvlc_time_t time;
libvlc_time_t length;
vector<string> playlist;
for(int i = 1; i < argc; i++) {
if((string)argv[i] == "--loop") {
loop = true;
} else {
playlist.push_back(argv[i]);
}
}
if(playlist.size() != 0) {
	inst = libvlc_new(argc, argv);
	libvlc_vlm_add_broadcast(inst, "stream", NULL, "#std{access=http,mux=ts,dst=localhost:8080,slp,name=phevlcs}:display{novideo}",0,NULL,true,false);
	if(loop == true) {
		while(true) {
			for(int i = 0; i < playlist.size(); i++) {
				libvlc_vlm_set_input(inst, "stream", playlist[i].c_str());
				libvlc_vlm_play_media(inst, "stream");
				sleep(1);
				time = libvlc_vlm_get_media_instance_position(inst, "stream", NULL);
				length = libvlc_vlm_get_media_instance_length(inst, "stream", NULL);
				while(time < length) {
					cout << "Streaming: " << playlist[i] << " (" << time << "/" << length << ")\r";
					time = libvlc_vlm_get_media_instance_position(inst, "stream", NULL);
				length = libvlc_vlm_get_media_instance_length(inst, "stream", NULL);
				}
			}
		}
	} else {
		for(int i = 0; i < playlist.size(); i++) {
				libvlc_vlm_set_input(inst, "stream", playlist[i].c_str());
				libvlc_vlm_play_media(inst, "stream");
				sleep(1);
				time = libvlc_vlm_get_media_instance_position(inst, "stream", NULL);
				length = libvlc_vlm_get_media_instance_length(inst, "stream", NULL);
				while(time < length) {
					cout << "Streaming: " << playlist[i] << " (" << time << "/" << length << ")\r";
					time = libvlc_vlm_get_media_instance_position(inst, "stream", NULL);
				length = libvlc_vlm_get_media_instance_length(inst, "stream", NULL);
				}
				cout << endl;
			}
	}
	libvlc_vlm_del_media(inst, "stream");
				libvlc_vlm_release(inst);
				libvlc_release(inst);
} else {
cerr << "Empty playlist! Exiting..." << endl;
return EXIT_FAILURE;
}
cout << "Done! Thank you for using Phitherek_' s Experimental LibVLC Streamer!" << endl;
return EXIT_SUCCESS;
}
