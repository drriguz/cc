#include "game.h"
#include "logger.h"
#include "exceptions.h"

int main(int argc, char* argv[])
{
    try {
        cc::Game game("cc", 800, 600);
        game.execute();
    } catch(cc::Exception& ex) {
        cc::Logger::error(ex.getError().c_str());
        return 1;
    }
    return 0;
}
