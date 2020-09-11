#include "MessageBus.h"

using namespace bus;
using namespace std;

int main()
{
    MessageBus messageBus;
    Listener listen(&messageBus);
    Service serv(&messageBus);
    
    listen.update();
    serv.update();
    messageBus.notify();

    return 0;
}