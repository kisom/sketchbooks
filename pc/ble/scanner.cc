#include <err.h>
#include <getopt.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
using namespace std;

const int default_scan_time = 1;

struct {
	int		 adapter;
	int		 socket;
	int		 flags;
	int		 max_resp;
	int		 num_resp;
	int		 scan_time;
	inquiry_info	*info;
} inquiry;

static bool
setup_socket(void)
{
	inquiry.adapter = hci_get_route(NULL);
	inquiry.socket = hci_open_dev(inquiry.adapter);
	if (inquiry.socket < 0) {
		cerr << "Failed to open socket." << endl;
		return false;
	}

	// Flush the "known-device" cache on each scan.
	inquiry.flags = IREQ_CACHE_FLUSH;
	inquiry.max_resp = 128;
	inquiry.info = static_cast<inquiry_info *>(
	    malloc(inquiry.max_resp * sizeof(inquiry_info))
	);

	if (inquiry.info == NULL) {
		cerr << "Failed to allocate memory for inquiries." << endl;
		return false;
	}

	return true;
}

static bool
start_scan(void)
{
	int	res;

	// scan parameters
	// type: passive v. active; in active, the scan response (second packet)
	//       is sent back.
	// the window is complicated, so I copied the parameters from the
	// default sketch.
	// own type, idk man. I just set it to 0.
	// no filter, I think
	res = hci_le_set_scan_parameters(inquiry.socket,
	    0, 160, 160, 0, 0, 1000);
	if (res < 0) {
		cerr << "hci_le_set_scan_parameters returned " << res << endl;
		return false;
	}

	// filter_dup: filter duplicates, 1 to enable
	if ((res = hci_le_set_scan_enable(inquiry.socket, 1, 0, 10000)) < 0) {
		cerr << "hci_le_set_scan_enable returned " << res << endl;
		return false;
	}

	inquiry.num_resp = hci_inquiry(inquiry.adapter, inquiry.scan_time,
	    inquiry.max_resp, NULL, &(inquiry.info), inquiry.flags);
	return inquiry.num_resp >= 0;
}

static void
show_info(void)
{
	char	s[256];

	for (int i = 0; i < inquiry.num_resp; i++) {
		ba2str(&(inquiry.info[i].bdaddr), s);
		cout << s << endl;
	}
}

static void
usage(ostream &out, const char *prog)
{
	out << "Usage: " << endl;
	out << prog << " [-h] [-t n]" << endl; 
	out << "	-h	Print this help message." << endl; 
	out << "	-t n	Scan for n seconds." << endl;
}

int
main(int argc, char *argv[])
{
	int	opt;

	inquiry.scan_time = default_scan_time;
	while ((opt = getopt(argc, argv, "ht:")) != -1) {
		switch (opt) {
		case 'h':
			usage(cout, argv[0]);
			exit(0);
		case 't':
			inquiry.scan_time = stoi(optarg);
			break;
		default:
			usage(cerr, argv[0]);
			exit(1);
		}
	}

	cout << "Setting up socket... " << flush;
	if (!setup_socket()) {
		cerr << "FAILED" << endl;
	}
	cout << "OK" << endl;

	cout << "Scanning for " << inquiry.scan_time << "s... " << flush;
	if (!start_scan()) {
		cerr << "FAILED" << endl;
		exit(1);
	}
	cout << "OK" << endl;

	show_info();

	hci_close_dev(inquiry.socket);
}
