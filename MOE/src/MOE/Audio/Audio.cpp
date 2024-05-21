//
// Created by gru on 4/10/24.
//

#include "Audio.h"

namespace MOE {
    ALCdevice* Audio::device = nullptr;
    ALCcontext* Audio::context = nullptr;
    std::vector<ALuint> Audio::buffers;
    std::vector<ALuint> Audio::sources;
    void Audio::Init() {
        // Open the default audio device
        device = alcOpenDevice(NULL);
        if (!device) {
            ALCenum error = alcGetError(NULL);
            std::cerr << "Failed to open default audio device: " << alcGetString(NULL, error) << std::endl;
            return;
        }


        // Create audio context
        context = alcCreateContext(device, NULL);
        if (!context || !alcMakeContextCurrent(context)) {
            ALCenum error = alcGetError(device);
            std::cerr << "Failed to create audio context: " << alcGetString(device, error) << std::endl;
            alcCloseDevice(device);
            return;
        }

        std::cout << "Audio initialized successfully" << std::endl;
    }

    void Audio::ShutDown() {
        // Delete sources and buffers
        for (ALuint source : sources) {
            alDeleteSources(1, &source);
        }
        sources.clear();

        for (ALuint buffer : buffers) {
            alDeleteBuffers(1, &buffer);
        }
        buffers.clear();

        // Release context and close device
        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

    void Audio::loadWav(const std::string& filename) {
        ALuint buffer;
        alGenBuffers(1, &buffer);

        SF_INFO sfInfo;
        SNDFILE* sndFile = sf_open(filename.c_str(), SFM_READ, &sfInfo);
        if (!sndFile) {
            std::cerr << "Failed to open sound file: " << filename << std::endl;
            return;
        }

        // Read PCM data
        std::vector<int16_t> pcmData(sfInfo.frames * sfInfo.channels);
        sf_count_t framesRead = sf_readf_short(sndFile, pcmData.data(), sfInfo.frames);
        sf_close(sndFile);

        if (framesRead > 0) {
            ALenum format = (sfInfo.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
            alBufferData(buffer, format, pcmData.data(), framesRead * sfInfo.channels * sizeof(int16_t), sfInfo.samplerate);
            buffers.push_back(buffer);
        } else {
            std::cerr << "Error reading sound file: " << filename << std::endl;
        }
    }
    void Audio::playGlobal(const std::string &filename) {
        ALuint source;
        alGenSources(1, &source);
        sources.push_back(source);

        for (const ALuint buffer : buffers) {
            ALint bufferFormat;
            alGetBufferi(buffer, AL_FORMAT_MONO16, &bufferFormat); // Use AL_FORMAT_MONO16 and AL_FORMAT_STEREO16 here
            if (bufferFormat == AL_FORMAT_MONO16 || bufferFormat == AL_FORMAT_STEREO16) {
                alSourcei(source, AL_BUFFER, buffer);
                alSourcePlay(source);
                break;
            }
        }
    }

    void Audio::playDirectional(const std::string &filename, const glm::vec3 position, const glm::vec3 velocity) {
        ALuint source;
        alGenSources(1, &source);
        sources.push_back(source);

        for (const ALuint buffer : buffers) {
            ALint bufferFormat;
            alGetBufferi(buffer, AL_FORMAT_MONO16, &bufferFormat); // Use AL_FORMAT_MONO16 and AL_FORMAT_STEREO16 here
            if (bufferFormat == AL_FORMAT_MONO16 || bufferFormat == AL_FORMAT_STEREO16) {
                alSourcei(source, AL_BUFFER, buffer);
                alSource3f(source, AL_POSITION, position.x, position.y, position.z);
                alSource3f(source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
                alSourcePlay(source);
                break;
            }
        }
    }

    void Audio::setListenerPosition(const glm::vec3 position) {
        alListener3f(AL_POSITION, position.x, position.y, position.z);
    }
}