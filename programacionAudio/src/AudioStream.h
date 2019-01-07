#pragma once

#include <vector>
#include <array>
#include "AudioSource.h"

#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"


class AudioStream {
	public:
		static AudioStream* load(const char*, AudioSource*);
		~AudioStream();

		void setLooping(bool looping) { shouldLoop = looping; }

		static void updateAll();
	protected:
		AudioStream();
		void update();
		bool streamB(uint32_t);
	private:
		static std::vector<AudioStream*> streams;

		AudioSource *source;
		stb_vorbis *stream;
		stb_vorbis_info info;
		std::array<uint32_t, 2>	buffers;
		size_t samplesLeft;
		bool shouldLoop;

};
