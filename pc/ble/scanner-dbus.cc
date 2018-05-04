#include <dbus-c++/dbus.h>
#include <iostream>

using namespace std;

DBus::BusDispatcher dispatcher;

int
main(int argc, char *argv[])
{
	int	result;

	DBus::default_dispatcher = &dispatcher;
	DBus::Connection bus = DBus::Connection::SessionBus();
}
