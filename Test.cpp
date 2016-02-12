#include <iostream>
using namespace std;

typedef int Model;
typedef float Texture;

class Kek {

	private:

	int num;

	public:

	static Kek* load(const char* fileName) {
		return new Kek(4);
	}

	Kek(int num) {
		this->num = num;
	}


};

class ContentManager {

	public:

	template<class T>
	static T load(char* fileName);

};

template<>
Kek ContentManager::load<Kek>(char* filename) {

	cout << "KEK";
	return *Kek::load(filename);

}

template<>
Model ContentManager::load<Model>(char* fileName) {
	cout << fileName << " Model = ";
	return 2;
}

template<>
Texture ContentManager::load<Texture>(char* fileName) {
	cout << fileName << " Texture = ";
	return 2.5f;
}

int main(int argc, char** argv) {

	cout << ContentManager::load<Model>("hola") << endl;
	cout << ContentManager::load<Texture>("woat") << endl;
	ContentManager::load<Kek>("hola");

	cin.get();

	return 0;

}
