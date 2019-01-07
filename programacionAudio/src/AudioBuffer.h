#pragma once
#include <cstdint>
#include <string>

class AudioBuffer {
	private:
		AudioBuffer();

		uint32_t buffer;

		~AudioBuffer();

	public:
		static AudioBuffer*	load(const char*);
		uint32_t getAlBuffer() const;
		static std::string extractExt(const std::string&);

};