//
//  main.cpp
//  
//
//  Created by Bret Jackson on 1/29/17.
//
//

#include <stdio.h>

#include "ExampleApp.h"

using namespace basicgraphics;

int main(int argc, char** argv)
{
	ExampleApp *app = new ExampleApp(argc, argv, "Basic graphics application Example", 640, 480);
	app->run();
	delete app;

	return 0;

}
