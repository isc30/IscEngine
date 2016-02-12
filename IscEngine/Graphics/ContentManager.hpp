#pragma once

#include <iostream>

namespace IscEngine {

	class ContentManager {

		public:

		template <int>
		static int loadContent<>() {

			std::cout << "int" << std::endl;

		}

	};

}