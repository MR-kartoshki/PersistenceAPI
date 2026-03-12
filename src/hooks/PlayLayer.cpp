#include "hooks/PlayLayer.hpp"

using namespace geode::prelude;
using namespace persistenceAPI;

#if defined(GEODE_IS_WINDOWS)
#define UNIQUE_ID_OFFSET 0x6ba158
#elif defined(GEODE_IS_ANDROID64)
#define UNIQUE_ID_OFFSET 0x122f018
#elif defined(GEODE_IS_ANDROID32)
#define UNIQUE_ID_OFFSET 0xab900c
#elif defined(GEODE_IS_ARM_MAC)
#define UNIQUE_ID_OFFSET 0x8b58ac
#elif defined(GEODE_IS_INTEL_MAC)
#define UNIQUE_ID_OFFSET 0x99e600
#elif defined(GEODE_IS_IOS)
#define UNIQUE_ID_OFFSET 0x84c1e8
#endif

// overrides

bool persistenceAPI::PAPlayLayer::init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects) {
    // reset uniqueID global to save/load GameObjects correctly using their index
    // should look into not having to do this but it's harder than it looks since there's
    // probably maps with object id as keys, it's not just us saving pointers so I'd have to find those.

    *reinterpret_cast<int*>(geode::base::get() + UNIQUE_ID_OFFSET) = 10;
    GameObject::resetMID();
    m_fields->m_uniqueIDBase = 12;

    if (!PlayLayer::init(i_level, i_useReplay, i_dontCreateObjects)) return false;

    return true;
}