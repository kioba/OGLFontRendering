#include <iostream>
#include "App.hpp"

int main (int /*argc*/, char** /*argv*/){

	App::getSingleton().execute();
	return 0;
}
