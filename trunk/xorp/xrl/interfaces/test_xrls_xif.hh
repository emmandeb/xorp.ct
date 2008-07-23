/*
 * Copyright (c) 2001-2008 XORP, Inc.
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/test_xrls_xif.hh,v 1.8 2008/01/04 03:18:02 pavlin Exp $
 */

#ifndef __XRL_INTERFACES_TEST_XRLS_XIF_HH__
#define __XRL_INTERFACES_TEST_XRLS_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifTestXrls"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlTestXrlsV0p1Client {
public:
    XrlTestXrlsV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlTestXrlsV0p1Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr StartTransmissionCB;

    bool send_start_transmission(
	const char*	dst_xrl_target_name,
	const StartTransmissionCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr EndTransmissionCB;

    bool send_end_transmission(
	const char*	dst_xrl_target_name,
	const EndTransmissionCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddXrl0CB;

    bool send_add_xrl0(
	const char*	dst_xrl_target_name,
	const AddXrl0CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddXrl1CB;

    bool send_add_xrl1(
	const char*	dst_xrl_target_name,
	const string&	data1,
	const AddXrl1CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddXrl2CB;

    bool send_add_xrl2(
	const char*	dst_xrl_target_name,
	const string&	data1,
	const string&	data2,
	const AddXrl2CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddXrl9CB;

    bool send_add_xrl9(
	const char*	dst_xrl_target_name,
	const bool&	data1,
	const int32_t&	data2,
	const IPv4&	data3,
	const IPv4Net&	data4,
	const IPv6&	data5,
	const IPv6Net&	data6,
	const Mac&	data7,
	const string&	data8,
	const vector<uint8_t>&	data9,
	const AddXrl9CB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddXrlxCB;

    bool send_add_xrlx(
	const char*	dst_xrl_target_name,
	const XrlAtomList&	data,
	const AddXrlxCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_start_transmission(
	const XrlError&	e,
	XrlArgs*	a,
	StartTransmissionCB		cb
    );

    void unmarshall_end_transmission(
	const XrlError&	e,
	XrlArgs*	a,
	EndTransmissionCB		cb
    );

    void unmarshall_add_xrl0(
	const XrlError&	e,
	XrlArgs*	a,
	AddXrl0CB		cb
    );

    void unmarshall_add_xrl1(
	const XrlError&	e,
	XrlArgs*	a,
	AddXrl1CB		cb
    );

    void unmarshall_add_xrl2(
	const XrlError&	e,
	XrlArgs*	a,
	AddXrl2CB		cb
    );

    void unmarshall_add_xrl9(
	const XrlError&	e,
	XrlArgs*	a,
	AddXrl9CB		cb
    );

    void unmarshall_add_xrlx(
	const XrlError&	e,
	XrlArgs*	a,
	AddXrlxCB		cb
    );

};

#endif /* __XRL_INTERFACES_TEST_XRLS_XIF_HH__ */
