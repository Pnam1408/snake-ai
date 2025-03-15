#include <random>
#include "Random.hpp"

namespace Random {
    int ri() {
        return gen();
    }
    float rf() {
        return Random::dis(Random::gen);
    }
}
