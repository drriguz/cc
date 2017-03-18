#include <iostream>
#include <string>
#include <tmxparser/Tmx.h>

#include "cc.h"

int main(int argc, char* argv[])
{
    Tmx::Map map;
    map.ParseFile("../maps/2.5d-simple.tmx");
    if(map.HasError()) {
        std::cerr << "Failed to open map:" << map.GetErrorText().c_str() << std::endl;
        return map.GetErrorCode();
    }    
    std::cout << "Ok" << std::endl;

    try {
        cc::Game game("hello", 800, 600);
        
        game.execute();
    } catch(cc::Exception ex) {
        cc::Logger::error(ex.getError().c_str());
        return 1;
    }
    return 0;
}
