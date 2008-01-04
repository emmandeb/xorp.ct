/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/rip_base.hh,v 1.36 2007/11/21 10:37:36 pavlin Exp $
 */


#ifndef __XRL_TARGETS_RIP_BASE_HH__
#define __XRL_TARGETS_RIP_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlRipTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlRipTargetBase {
protected:
    XrlCmdMap* _cmds;

public:
    /**
     * Constructor.
     *
     * @param cmds an XrlCmdMap that the commands associated with the target
     *		   should be added to.  This is typically the XrlRouter
     *		   associated with the target.
     */
    XrlRipTargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlRipTargetBase();

    /**
     * Set command map.
     *
     * @param cmds pointer to command map to associate commands with.  This
     * argument is typically a pointer to the XrlRouter associated with the
     * target.
     *
     * @return true on success, false if cmds is null or a command map has
     * already been supplied.
     */
    bool set_command_map(XrlCmdMap* cmds);

    /**
     * Get Xrl instance name associated with command map.
     */
    const string& name() const { return _cmds->name(); }

    /**
     * Get version string of instance.
     */
    const char* version() const { return "rip/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values,
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values,
	string&	version) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get status of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_status(
	// Output values,
	uint32_t&	status,
	string&	reason) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Request clean shutdown of Xrl Target
     */
    virtual XrlCmdError common_0_1_shutdown() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Announce target birth to observer.
     *
     *  @param target_class the target class name.
     *
     *  @param target_instance the target instance name.
     */
    virtual XrlCmdError finder_event_observer_0_1_xrl_target_birth(
	// Input values,
	const string&	target_class,
	const string&	target_instance) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Announce target death to observer.
     *
     *  @param target_class the target class name.
     *
     *  @param target_instance the target instance name.
     */
    virtual XrlCmdError finder_event_observer_0_1_xrl_target_death(
	// Input values,
	const string&	target_class,
	const string&	target_instance) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Configure a policy filter.
     *
     *  @param filter the identifier of the filter to configure.
     *
     *  @param conf the configuration of the filter.
     */
    virtual XrlCmdError policy_backend_0_1_configure(
	// Input values,
	const uint32_t&	filter,
	const string&	conf) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Reset a policy filter.
     *
     *  @param filter the identifier of the filter to reset.
     */
    virtual XrlCmdError policy_backend_0_1_reset(
	// Input values,
	const uint32_t&	filter) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Push all available routes through all filters for re-filtering.
     */
    virtual XrlCmdError policy_backend_0_1_push_routes() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Start route redistribution for an IPv4 route.
     *
     *  @param network the route to advertise.
     *
     *  @param unicast whether the route is unicast.
     *
     *  @param multicast whether the route is multicast.
     *
     *  @param nexthop the nexthop of the route.
     *
     *  @param metric the metric of the route.
     *
     *  @param policytags the set of policy-tags associated with the route.
     */
    virtual XrlCmdError policy_redist4_0_1_add_route4(
	// Input values,
	const IPv4Net&	network,
	const bool&	unicast,
	const bool&	multicast,
	const IPv4&	nexthop,
	const uint32_t&	metric,
	const XrlAtomList&	policytags) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Terminate route redistribution for an IPv4 route.
     *
     *  @param network the route for which advertisements should cease.
     *
     *  @param unicast whether the route is unicast.
     *
     *  @param multicast whether the route is multicast.
     */
    virtual XrlCmdError policy_redist4_0_1_delete_route4(
	// Input values,
	const IPv4Net&	network,
	const bool&	unicast,
	const bool&	multicast) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Add an address to run RIP process on. The addition of address is not
     *  instantaneous, RIP has to instantiate state in the FEA to send and
     *  receive packets. Once instantiated the address must be explicitly
     *  enabled with set_rip_address_enabled.
     *
     *  @param ifname the interface that owns vif that has address.
     *
     *  @param vifname virtual interface owning address.
     *
     *  @param addr the address to be added.
     */
    virtual XrlCmdError rip_0_1_add_rip_address(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Remove an address RIP process is running on.
     *
     *  @param ifname the interface that owns vif that has address.
     *
     *  @param vifname virtual interface owning address.
     *
     *  @param addr the address to be removed.
     */
    virtual XrlCmdError rip_0_1_remove_rip_address(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr) = 0;

    virtual XrlCmdError rip_0_1_set_rip_address_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	enabled) = 0;

    virtual XrlCmdError rip_0_1_rip_address_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	bool&	enabled) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set cost metric associated with address.
     */
    virtual XrlCmdError rip_0_1_set_cost(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	cost) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get cost metric associated with address.
     */
    virtual XrlCmdError rip_0_1_cost(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	cost) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set horizon type applied to routes advertised from address.
     *
     *  @param horizon name of horizon type. Permitted values: "none",
     *  "poison-reverse" "split-horizon-poison-reverse"
     */
    virtual XrlCmdError rip_0_1_set_horizon(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const string&	horizon) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get horizon type applied to routes advertised from address.
     */
    virtual XrlCmdError rip_0_1_horizon(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	string&	horizon) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Make RIP passive (receive only) on interface/vif/address.
     */
    virtual XrlCmdError rip_0_1_set_passive(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	passive) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get value indicating whether RIP is passive (receive only) on
     *  interface/vif/address.
     */
    virtual XrlCmdError rip_0_1_passive(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	bool&	passive) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Accept and respond to non-RIP requests.
     */
    virtual XrlCmdError rip_0_1_set_accept_non_rip_requests(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get value indicating whether non-RIP requests are accepted and
     *  responded to on interface/vif/address.
     */
    virtual XrlCmdError rip_0_1_accept_non_rip_requests(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Accept default route from peers.
     */
    virtual XrlCmdError rip_0_1_set_accept_default_route(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Accessor for whether default route is accepted from peers.
     */
    virtual XrlCmdError rip_0_1_accept_default_route(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Advertise default route (if present).
     */
    virtual XrlCmdError rip_0_1_set_advertise_default_route(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	advertise) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Accessor for whether default route is advertised.
     */
    virtual XrlCmdError rip_0_1_advertise_default_route(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	bool&	advertise) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period that routes associated with reception address will expire in
     *  the absence of updates.
     */
    virtual XrlCmdError rip_0_1_set_route_timeout(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get period that routes associated with reception address will expire in
     *  the absence of updates.
     */
    virtual XrlCmdError rip_0_1_route_timeout(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period that routes associated with reception address will be
     *  deleted after they've expired.
     */
    virtual XrlCmdError rip_0_1_set_deletion_delay(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get period that routes associated with reception address will be
     *  deleted after they've expired.
     */
    virtual XrlCmdError rip_0_1_deletion_delay(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period that route table requests should be sent from address when
     *  no peers are associated with it.
     */
    virtual XrlCmdError rip_0_1_set_request_interval(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period that route table requests should be sent from address when
     *  no peers are associated with it.
     */
    virtual XrlCmdError rip_0_1_request_interval(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period between the unsolicited sending of the routing table from
     *  address.
     */
    virtual XrlCmdError rip_0_1_set_update_interval(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get period between the unsolicited sending of the routing table from
     *  address.
     */
    virtual XrlCmdError rip_0_1_update_interval(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set jitter between the unsolicited sending of the routing table from
     *  address (in percents of the period).
     */
    virtual XrlCmdError rip_0_1_set_update_jitter(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_jitter) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get jitter between the unsolicited sending of the routing table from
     *  address (in percents of the period).
     */
    virtual XrlCmdError rip_0_1_update_jitter(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	t_jitter) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period between sending triggered updates from address.
     */
    virtual XrlCmdError rip_0_1_set_triggered_update_delay(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get period between sending triggered updates from address.
     */
    virtual XrlCmdError rip_0_1_triggered_update_delay(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set jitter between sending triggered updates from address (in percents
     *  of the period).
     */
    virtual XrlCmdError rip_0_1_set_triggered_update_jitter(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_jitter) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get jitter between sending triggered updates from address (in percents
     *  of the period).
     */
    virtual XrlCmdError rip_0_1_triggered_update_jitter(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	t_jitter) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set the inter-packet delay between the output of packets from address.
     */
    virtual XrlCmdError rip_0_1_set_interpacket_delay(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	t_msecs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get the inter-packet delay between the output of packets from address.
     */
    virtual XrlCmdError rip_0_1_interpacket_delay(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	uint32_t&	t_msecs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set simple password authentication key.
     *
     *  @param ifname the interface name.
     *
     *  @param vifname the vif name.
     *
     *  @param addr the address.
     *
     *  @param password the authentication password.
     */
    virtual XrlCmdError rip_0_1_set_simple_authentication_key(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const string&	password) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Delete simple password authentication key.
     *
     *  @param ifname the interface name.
     *
     *  @param vifname the vif name.
     *
     *  @param addr the address.
     */
    virtual XrlCmdError rip_0_1_delete_simple_authentication_key(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set MD5 authentication key.
     *
     *  @param ifname the interface name.
     *
     *  @param vifname the vif name.
     *
     *  @param addr the address.
     *
     *  @param key_id the key ID (must be an integer in the interval [0, 255]).
     *
     *  @param password the authentication password.
     *
     *  @param start_time the authentication start time (YYYY-MM-DD.HH:MM).
     *
     *  @param end_time the authentication end time (YYYY-MM-DD.HH:MM).
     */
    virtual XrlCmdError rip_0_1_set_md5_authentication_key(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	key_id,
	const string&	password,
	const string&	start_time,
	const string&	end_time) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Delete MD5 authentication key.
     *
     *  @param ifname the interface name.
     *
     *  @param vifname the vif name.
     *
     *  @param addr the address.
     *
     *  @param key_id the key ID (must be an integer in the interval [0, 255]).
     */
    virtual XrlCmdError rip_0_1_delete_md5_authentication_key(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	key_id) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get a textual description of the status of address RIP is running upon.
     *
     *  @param ifname the interface that owns vif that has the address.
     *
     *  @param vifname virtual interface owns the address.
     *
     *  @param addr the address to query.
     */
    virtual XrlCmdError rip_0_1_rip_address_status(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	string&	status) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get addresses running RIP.
     */
    virtual XrlCmdError rip_0_1_get_all_addresses(
	// Output values,
	XrlAtomList&	ifnames,
	XrlAtomList&	vifnames,
	XrlAtomList&	addrs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get counters associated with interface / vif /address.
     */
    virtual XrlCmdError rip_0_1_get_counters(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	XrlAtomList&	counter_descriptions,
	XrlAtomList&	counter_values) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get the list of peers associated with interface / vif / address.
     */
    virtual XrlCmdError rip_0_1_get_peers(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	// Output values,
	XrlAtomList&	peers) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get list of all peers known to RIP. There is a 1-to-1 correspondence
     *  between the items in the lists of peers, ifnames, vifnames, addrs.
     */
    virtual XrlCmdError rip_0_1_get_all_peers(
	// Output values,
	XrlAtomList&	peers,
	XrlAtomList&	ifnames,
	XrlAtomList&	vifnames,
	XrlAtomList&	addrs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get counters associated with peer of interface / vif /address.
     *
     *  @param counter_descriptions textual descriptions of counters.
     *
     *  @param counter_values values associated with counters.
     *
     *  @param peer_last_active is the number of seconds since TimeVal(0,0).
     */
    virtual XrlCmdError rip_0_1_get_peer_counters(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const IPv4&	peer,
	// Output values,
	XrlAtomList&	counter_descriptions,
	XrlAtomList&	counter_values,
	uint32_t&	peer_last_active) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when a packet arrives
     *  from an IPv4 source.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     *
     *  @param if_name the interface name the packet arrived on, if known. If
     *  unknown, then it is an empty string.
     *
     *  @param vif_name the vif name the packet arrived on, if known. If
     *  unknown, then it is an empty string.
     *
     *  @param src_host the originating host.
     *
     *  @param src_port the originating IP port.
     *
     *  @param data the data received.
     */
    virtual XrlCmdError socket4_user_0_1_recv_event(
	// Input values,
	const string&	sockid,
	const string&	if_name,
	const string&	vif_name,
	const IPv4&	src_host,
	const uint32_t&	src_port,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when a connection
     *  request is received from an IPv4 source. It applies only to TCP
     *  sockets.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     *
     *  @param src_host the connecting host.
     *
     *  @param src_port the connecting IP port.
     *
     *  @param new_sockid the identifier associated with the new socket that
     *  has been created to handle the new connection.
     *
     *  @param accept if true, the connection request has been accepted,
     *  otherwise it has been rejected.
     */
    virtual XrlCmdError socket4_user_0_1_inbound_connect_event(
	// Input values,
	const string&	sockid,
	const IPv4&	src_host,
	const uint32_t&	src_port,
	const string&	new_sockid,
	// Output values,
	bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when an outgoing
     *  connection request originated by the local host is completed. It
     *  applies only to TCP sockets. Note that if the connection failed, the
     *  error_event will be dispatched instead.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     */
    virtual XrlCmdError socket4_user_0_1_outgoing_connect_event(
	// Input values,
	const string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when an error occurs.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     *
     *  @param error a textual description of the error.
     *
     *  @param fatal indication of whether socket is shutdown because of error.
     */
    virtual XrlCmdError socket4_user_0_1_error_event(
	// Input values,
	const string&	sockid,
	const string&	error,
	const bool&	fatal) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket4/0.1 when the peer has
     *  closed the connection. It applies only to TCP sockets. Note that the
     *  socket itself is left open and must be explicitly closed.
     *
     *  @param sockid the identifier associated with socket where the event
     *  occurred.
     */
    virtual XrlCmdError socket4_user_0_1_disconnect_event(
	// Input values,
	const string&	sockid) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_observer_0_1_xrl_target_birth(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_observer_0_1_xrl_target_death(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_policy_backend_0_1_configure(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_policy_backend_0_1_reset(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_policy_backend_0_1_push_routes(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_policy_redist4_0_1_add_route4(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_policy_redist4_0_1_delete_route4(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_add_rip_address(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_remove_rip_address(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_rip_address_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_rip_address_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_cost(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_cost(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_horizon(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_horizon(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_passive(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_passive(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_accept_non_rip_requests(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_accept_non_rip_requests(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_accept_default_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_accept_default_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_advertise_default_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_advertise_default_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_route_timeout(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_route_timeout(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_deletion_delay(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_deletion_delay(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_request_interval(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_request_interval(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_update_interval(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_update_interval(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_update_jitter(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_update_jitter(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_triggered_update_delay(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_triggered_update_delay(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_triggered_update_jitter(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_triggered_update_jitter(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_interpacket_delay(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_interpacket_delay(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_simple_authentication_key(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_delete_simple_authentication_key(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_set_md5_authentication_key(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_delete_md5_authentication_key(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_rip_address_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_get_all_addresses(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_get_counters(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_get_peers(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_get_all_peers(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_rip_0_1_get_peer_counters(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_recv_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_inbound_connect_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_outgoing_connect_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_error_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_user_0_1_disconnect_event(const XrlArgs& in, XrlArgs* out);

    void add_handlers();
    void remove_handlers();
};

#endif // __XRL_TARGETS_RIP_BASE_HH__
