// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2008 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/libxipc/test_xrl_receiver.cc,v 1.15 2007/05/23 12:12:39 pavlin Exp $"


//
// Test XRLs receiver.
//

#include "xrl_module.h"

#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"
#include "libxorp/xorpfd.hh"
#include "libxorp/callback.hh"
#include "libxorp/eventloop.hh"
#include "libxorp/exceptions.hh"
#include "libxorp/status_codes.h"

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

#include "libxipc/xrl_std_router.hh"

#include "xrl/targets/test_xrls_base.hh"


//
// This is a receiver program for testing XRL performance. It is used
// as a pair with the "test_xrl_sender" program.
//
// Usage:
// 1. Start ./xorp_finder
// 2. Start ./test_xrl_receiver
// 3. Start ./test_xrl_sender
//
// Use the definitions below to change the receiver's behavior.
//

//
// Define to 1 to enable printing of debug output
//
#define PRINT_DEBUG			0

//
// Define to 1 to exit after end of transmission
//
#define RECEIVE_DO_EXIT			0


//
// Local functions prototypes
//
static	void usage(const char *argv0, int exit_value);

class TestReceiver : public XrlTestXrlsTargetBase {
public:
    TestReceiver(EventLoop& eventloop, XrlRouter* xrl_router)
	: XrlTestXrlsTargetBase(xrl_router),
	  _eventloop(eventloop),
	  _received_xrls(0),
	  _done(false)
    {}
    ~TestReceiver() {}

    bool done() const { return _done; }

    void print_xrl_received() const {
#if PRINT_DEBUG
    	printf(".");
	if (! (_received_xrls % 10000))
	    printf("Received %u\n", XORP_UINT_CAST(_received_xrls));
#endif // PRINT_DEBUG
    }

private:
    XrlCmdError common_0_1_get_target_name(
	// Output values,
	string&	name) {

	name = "TestReceiver";
	return XrlCmdError::OKAY();
    }

    XrlCmdError common_0_1_get_version(
	// Output values,
	string&	version) {

	version = "0.1";
	return XrlCmdError::OKAY();
    }

    XrlCmdError common_0_1_get_status(
	// Output values,
	uint32_t&	status,
	string&	reason) {
	return XrlCmdError::OKAY();

	reason = "Ready";
	status = PROC_READY;
	return XrlCmdError::OKAY();
    }

    XrlCmdError common_0_1_shutdown() {
	// TODO: XXX: PAVPAVPAV: implement it!
	return XrlCmdError::OKAY();
    }


    XrlCmdError test_xrls_0_1_start_transmission() {
	_received_xrls = 0;
	TimerList::system_gettimeofday(&_start_time);
	return XrlCmdError::OKAY();
    }

    XrlCmdError test_xrls_0_1_end_transmission() {
	TimerList::system_gettimeofday(&_end_time);
	print_statistics();
	return XrlCmdError::OKAY();
    }

    XrlCmdError test_xrls_0_1_add_xrl0() {
	print_xrl_received();
	_received_xrls++;
	return XrlCmdError::OKAY();
    }

    XrlCmdError test_xrls_0_1_add_xrl1(
	// Input values,
	const string&	data1) {
	print_xrl_received();
	_received_xrls++;
	return XrlCmdError::OKAY();
	UNUSED(data1);
    }

    XrlCmdError test_xrls_0_1_add_xrl2(
	// Input values,
	const string&	data1,
	const string&	data2) {
	print_xrl_received();
	_received_xrls++;
	return XrlCmdError::OKAY();
	UNUSED(data1);
	UNUSED(data2);
    }

    XrlCmdError test_xrls_0_1_add_xrl9(
	// Input values,
	const bool&	data1,
	const int32_t&	data2,
	const IPv4&	data3,
	const IPv4Net&	data4,
	const IPv6&	data5,
	const IPv6Net&	data6,
	const Mac&	data7,
	const string&	data8,
	const vector<uint8_t>& data9) {
	print_xrl_received();
	_received_xrls++;
	return XrlCmdError::OKAY();
	UNUSED(data1);
	UNUSED(data2);
	UNUSED(data3);
	UNUSED(data4);
	UNUSED(data5);
	UNUSED(data6);
	UNUSED(data7);
	UNUSED(data8);
	UNUSED(data9);
    }

    XrlCmdError
    test_xrls_0_1_add_xrlx(const XrlAtomList &)
    {
	print_xrl_received();
	_received_xrls++;
	return XrlCmdError::OKAY();
    }

    void print_statistics() {
	TimeVal delta_time = _end_time - _start_time;

	if (_received_xrls == 0) {
	    printf("No XRLs received\n");
	    return;
	}
	if (delta_time == TimeVal::ZERO()) {
	    printf("Received %u XRLs; delta-time = %s secs\n",
		   XORP_UINT_CAST(_received_xrls), delta_time.str().c_str());
	    return;
	}

	double double_time = delta_time.get_double();
	double speed = _received_xrls;
	speed /= double_time;

	printf("Received %u XRLs; delta_time = %s secs; speed = %f XRLs/s\n",
	       XORP_UINT_CAST(_received_xrls),
	       delta_time.str().c_str(), speed);

#if RECEIVE_DO_EXIT
	// XXX: if enabled, then exit after all XRLs have been received.
	if (_exit_timer.scheduled() == false)
	    _exit_timer = _eventloop.set_flag_after_ms(60000, &_done);
#endif

	return;
    }

    EventLoop&	_eventloop;
    TimeVal	_start_time;
    TimeVal	_end_time;
    size_t	_received_xrls;
    XorpTimer	_exit_timer;
    bool	_done;
};

/**
 * usage:
 * @argv0: Argument 0 when the program was called (the program name itself).
 * @exit_value: The exit value of the program.
 *
 * Print the program usage.
 * If @exit_value is 0, the usage will be printed to the standart output,
 * otherwise to the standart error.
 **/
static void
usage(const char *argv0, int exit_value)
{
    FILE *output;
    const char *progname = strrchr(argv0, '/');

    if (progname != NULL)
	progname++;		// Skip the last '/'
    if (progname == NULL)
	progname = argv0;

    //
    // If the usage is printed because of error, output to stderr, otherwise
    // output to stdout.
    //
    if (exit_value == 0)
	output = stdout;
    else
	output = stderr;

    fprintf(output, "Usage: %s [-F <finder_hostname>[:<finder_port>]]\n",
	    progname);
    fprintf(output, "           -F <finder_hostname>[:<finder_port>]  : finder hostname and port\n");
    fprintf(output, "           -h                                    : usage (this message)\n");
    fprintf(output, "\n");
    fprintf(output, "Program name:   %s\n", progname);
    fprintf(output, "Module name:    %s\n", XORP_MODULE_NAME);
    fprintf(output, "Module version: %s\n", XORP_MODULE_VERSION);

    exit (exit_value);

    // NOTREACHED
}

static void
test_xrls_receiver_main(const char* finder_hostname, uint16_t finder_port)
{
    //
    // Init stuff
    //
    EventLoop eventloop;

    //
    // Receiver
    //
    XrlStdRouter xrl_std_router_test_receiver(eventloop, "test_xrl_receiver",
					      finder_hostname, finder_port);
    TestReceiver test_receiver(eventloop, &xrl_std_router_test_receiver);
    wait_until_xrl_router_is_ready(eventloop, xrl_std_router_test_receiver);

    //
    // Run everything
    //
    while (! test_receiver.done()) {
	eventloop.run();
    }
}

int
main(int argc, char *argv[])
{
    int ch;
    string::size_type idx;
    const char *argv0 = argv[0];
    string finder_hostname = FinderConstants::FINDER_DEFAULT_HOST().str();
    uint16_t finder_port = FinderConstants::FINDER_DEFAULT_PORT();

    //
    // Initialize and start xlog
    //
    xlog_init(argv[0], NULL);
    xlog_set_verbose(XLOG_VERBOSE_LOW);		// Least verbose messages
    // XXX: verbosity of the error messages temporary increased
    xlog_level_set_verbose(XLOG_LEVEL_ERROR, XLOG_VERBOSE_HIGH);
    xlog_add_default_output();
    xlog_start();

    //
    // Get the program options
    //
    while ((ch = getopt(argc, argv, "F:h")) != -1) {
	switch (ch) {
	case 'F':
	    // Finder hostname and port
	    finder_hostname = optarg;
	    idx = finder_hostname.find(':');
	    if (idx != string::npos) {
		if (idx + 1 >= finder_hostname.length()) {
		    // No port number
		    usage(argv0, 1);
		    // NOTREACHED
		}
		char* p = &finder_hostname[idx + 1];
		finder_port = static_cast<uint16_t>(atoi(p));
		finder_hostname = finder_hostname.substr(0, idx);
	    }
	    break;
	case 'h':
	case '?':
	    // Help
	    usage(argv0, 0);
	    // NOTREACHED
	    break;
	default:
	    usage(argv0, 1);
	    // NOTREACHED
	    break;
	}
    }
    argc -= optind;
    argv += optind;
    if (argc != 0) {
	usage(argv0, 1);
	// NOTREACHED
    }

    //
    // Run everything
    //
    try {
	test_xrls_receiver_main(finder_hostname.c_str(), finder_port);
    } catch(...) {
	xorp_catch_standard_exceptions();
    }

    //
    // Gracefully stop and exit xlog
    //
    xlog_stop();
    xlog_exit();

    exit (0);
}
