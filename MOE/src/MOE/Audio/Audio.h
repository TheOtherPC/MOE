//
// Created by gru on 4/10/24.
//

#ifndef MOE_AUDIO_H
#define MOE_AUDIO_H

#include "openal-soft/include/AL/al.h"
#include "openal-soft/include/AL/alc.h"
#include "libsndfile/include/sndfile.h"
#include "glm/glm.hpp"

#include "vector"
#include "string"
#include "iostream"


namespace MOE {
    class Audio {
    public:
        static void Init();
        static void ShutDown();

        static void loadWav(const std::string &filename);

        static void playGlobal(const std::string &filename);

        static void playDirectional(const std::string &filename, const glm::vec3 position, const glm::vec3 velocity);

        static void setListenerPosition(const glm::vec3 position);

    private:
        static ALCdevice *device;
        static ALCcontext *context;
        static std::vector<ALuint> buffers;
        static std::vector<ALuint> sources;
    };
}

#endif //MOE_AUDIO_H
