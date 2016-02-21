#pragma once

#include "LigthSource.hpp"

#include <list>
#include <vector>
using namespace std;

namespace IscEngine { namespace Graphics { namespace Lighting {

	class LightSetup {

	private:

		list<LightSource*> lightSources;

	public:
		
		void add(LightSource* const light);
		void add(const vector<LightSource*>& light);
		void add(const list<LightSource*>& light);
		void remove(LightSource* const light);
		void clear();

	};

} } }