/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/fea_rawpkt4_client_xif.hh,v 1.10 2007/07/12 21:37:28 pavlin Exp $
 */

#ifndef __XRL_INTERFACES_FEA_RAWPKT4_CLIENT_XIF_HH__
#define __XRL_INTERFACES_FEA_RAWPKT4_CLIENT_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifFeaRawpkt4Client"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlRawPacket4ClientV0p1Client {
public:
    XrlRawPacket4ClientV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlRawPacket4ClientV0p1Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr RecvCB;
    /**
     *  Send Xrl intended to:
     *
     *  Receive an IPv4 packet from a raw socket.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param if_name the interface name the packet arrived on.
     *
     *  @param vif_name the vif name the packet arrived on.
     *
     *  @param src_address the IP source address.
     *
     *  @param dst_address the IP destination address.
     *
     *  @param ip_protocol the IP protocol number.
     *
     *  @param ip_ttl the IP TTL (hop-limit). If it has a negative value, then
     *  the received value is unknown.
     *
     *  @param ip_tos the Type of Service (Diffserv/ECN bits for IPv4). If it
     *  has a negative value, then the received value is unknown.
     *
     *  @param ip_router_alert if true, the IP Router Alert option was included
     *  in the IP packet.
     *
     *  @param ip_internet_control if true, then this is IP control traffic.
     *
     *  @param payload the payload, everything after the IP header and options.
     */
    bool send_recv(
	const char*	dst_xrl_target_name,
	const string&	if_name,
	const string&	vif_name,
	const IPv4&	src_address,
	const IPv4&	dst_address,
	const uint32_t&	ip_protocol,
	const int32_t&	ip_ttl,
	const int32_t&	ip_tos,
	const bool&	ip_router_alert,
	const bool&	ip_internet_control,
	const vector<uint8_t>&	payload,
	const RecvCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_recv(
	const XrlError&	e,
	XrlArgs*	a,
	RecvCB		cb
    );

};

#endif /* __XRL_INTERFACES_FEA_RAWPKT4_CLIENT_XIF_HH__ */
