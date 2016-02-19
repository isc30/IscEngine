#pragma once

#include <iostream>
using namespace std;

namespace IscEngine {

	class Resource {

        private:

            static const string RESOURCE_PATH;
            static const string ERROR_TEXTURE;

        public:

            template <typename T>
            static T* load(const char* fileName);

            template <typename T>
            static T* load(const char* fileName0, const char* fileName1);

    };

}
