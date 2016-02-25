#pragma once

#include <iostream>
#include <string>
using namespace std;

namespace IscEngine {

	class Resource {

        public:

            static const string RESOURCE_PATH;
            static const string ERROR_TEXTURE;

            template <typename T0, typename... T1>
            static T0* load(T1...);

    };

}
