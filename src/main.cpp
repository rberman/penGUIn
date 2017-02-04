//
//  main.cpp
//  
//
//  Created by Bret Jackson on 1/29/17.
//
//

#include <stdio.h>

#include "App.h"

int main(int argc, char** argv)
{   
    App *app = new App(argc, argv);
    app->run();
    delete app;
    
}