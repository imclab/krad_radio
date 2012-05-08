#ifndef KRAD_OGG_H
#define KRAD_OGG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <malloc.h>
#include <math.h>
#include <signal.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdarg.h>
#include <limits.h>

#include <ogg/ogg.h>
#include <theora/theora.h>
#include <vorbis/vorbisenc.h>
#include <theora/theoradec.h>
#include <theora/theoraenc.h>

#include "krad_io.h"

typedef struct krad_ogg_St krad_ogg_t;
typedef struct krad_ogg_track_St krad_ogg_track_t;

#define KRAD_OGG_MAX_TRACKS 10

#define KRAD_OGG_NO_SERIAL -420

#ifndef KRAD_CODEC_T
typedef enum {
	VORBIS = 6666,
	OPUS,
	FLAC,
	VP8,
	DIRAC,
	THEORA,
	NOCODEC,
	SKELETON,
	MJPEG
} krad_codec_t;
#define KRAD_CODEC_T 1
#endif

struct krad_ogg_track_St {

	krad_codec_t codec;
	
	int channels;
	float sample_rate;
	int bit_depth;
	float frame_rate;
	int keyframe_shift;
	
	int width;
	int height;
		
	int header_count;
	unsigned char *header[3];
	int header_len[3];
	
	ogg_stream_state stream_state;
	int serial;
	int last_serial;
	
	int ready;
	
	uint64_t last_granulepos;
	
};

struct krad_ogg_St {

	int track_count;
	krad_ogg_track_t *tracks;
	ogg_sync_state sync_state;
	krad_io_t *krad_io;
	unsigned char *input_buffer;

};


// READING FUNCS

//int krad_ogg_track_header_data_size(krad_ogg_t *krad_ogg, int track, int header);
int krad_ogg_track_count (krad_ogg_t *krad_ogg);
krad_codec_t krad_ogg_track_codec (krad_ogg_t *krad_ogg, int track);
int krad_ogg_track_header_count (krad_ogg_t *krad_ogg, int track);
int krad_ogg_track_header_size (krad_ogg_t *krad_ogg, int track, int header);
int krad_ogg_read_track_header (krad_ogg_t *krad_ogg, unsigned char *buffer, int track, int header);
int krad_ogg_track_active (krad_ogg_t *krad_ogg, int track);
int krad_ogg_track_changed (krad_ogg_t *krad_ogg, int track);
int krad_ogg_read_packet (krad_ogg_t *krad_ogg, int *track, uint64_t *timecode, unsigned char *buffer);
int krad_ogg_write (krad_ogg_t *krad_ogg, unsigned char *buffer, int length);
void krad_ogg_process (krad_ogg_t *krad_ogg);

// WRITING FUNCS

/*	
krad_link->video_track = krad_ogg_add_video_track (krad_link->krad_ebml, "V_VP8", 30000, 1000,
															krad_link->encoding_width, krad_link->encoding_height);	
krad_link->audio_track = krad_ogg_add_audio_track(krad_link->krad_ebml, "A_VORBIS", 48000, krad_link->audio_channels, krad_link->krad_vorbis->header, 
																 krad_link->krad_vorbis->headerpos);
krad_ogg_add_video(krad_link->krad_ebml, krad_link->video_track, packet, packet_size, keyframe);
krad_ogg_add_audio(krad_link->krad_ebml, krad_link->audio_track, packet, packet_size, frames);
*/

krad_ogg_t *krad_ogg_open_file(char *filename, krad_io_mode_t mode);
krad_ogg_t *krad_ogg_open_stream(char *host, int port, char *mount, char *password);

krad_ogg_t *krad_ogg_create();
void krad_ogg_destroy(krad_ogg_t *krad_ogg);
#endif
