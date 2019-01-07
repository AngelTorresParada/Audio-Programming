#include "AudioStream.h"
#include "al.h"

std::vector<AudioStream*> AudioStream::streams;

AudioStream *AudioStream::load(const char *_filename, AudioSource *_source)
{
	AudioStream *s = new AudioStream();

	s->source = _source;
	s->shouldLoop = false;

	s->stream = stb_vorbis_open_filename(_filename, nullptr, nullptr);
	s->info = stb_vorbis_get_info(s->stream);
	s->samplesLeft = stb_vorbis_stream_length_in_samples(s->stream) * s->info.channels;
	alGenBuffers(2, s->buffers.data());

	s->streamB(s->buffers[0]);
	s->streamB(s->buffers[1]);
	alSourceQueueBuffers(s->source->getSource(), 2, s->buffers.data());

	
	AudioStream::streams.push_back(s);
	return s;
}


AudioStream::~AudioStream() {
	for (auto ss = AudioStream::streams.begin(); ss != AudioStream::streams.end(); ++ss) {
		if (*ss == this) {
			AudioStream::streams.erase(ss);
			alDeleteBuffers(2, (*ss)->buffers.data());
			break;
		}
	}
}


void AudioStream::updateAll() {
	for (auto ss = AudioStream::streams.begin(); ss != AudioStream::streams.end(); ss++) {
		(*ss)->update();
	}
}


AudioStream::AudioStream()
{
}


void AudioStream::update() {
	ALint buffer = 0;
	alGetSourcei(source->getSource(), AL_BUFFERS_PROCESSED, &buffer);

	printf("%d", buffer);

	if (buffer > 0) {
		ALuint uBuffer = 0;
		alSourceUnqueueBuffers(source->getSource(), buffer, &uBuffer);

		bool isRequeued = streamB(uBuffer);

		if (isRequeued) {
			alSourceQueueBuffers(source->getSource(), buffer, &uBuffer);
		}
		else {
			if (shouldLoop) {
				stb_vorbis_seek_start(stream);
				samplesLeft = stb_vorbis_stream_length_in_samples(stream) * info.channels;
				isRequeued = streamB(uBuffer);
				if (isRequeued)
					alSourceQueueBuffers(source->getSource(), buffer, &uBuffer);
			}
		}
	}
}


bool AudioStream::streamB(uint32_t _buffer) {
	const size_t sampleSize = 32768;
	std::array<int16_t, sampleSize> pcm;
	size_t size = stb_vorbis_get_samples_short_interleaved(stream, info.channels, pcm.data(), sampleSize);
	if (size == 0) {
		return false;
	}

	else {
		alBufferData(_buffer, info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, pcm.data(), 
			size * info.channels * sizeof(short), info.sample_rate);
		samplesLeft -= size;
		return true;
	}
}



