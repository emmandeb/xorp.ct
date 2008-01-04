/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/fea_ifmgr_mirror_base.hh,v 1.24 2007/11/29 01:52:41 pavlin Exp $
 */


#ifndef __XRL_TARGETS_FEA_IFMGR_MIRROR_BASE_HH__
#define __XRL_TARGETS_FEA_IFMGR_MIRROR_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlFeaIfmgrMirrorTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlFeaIfmgrMirrorTargetBase {
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
    XrlFeaIfmgrMirrorTargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlFeaIfmgrMirrorTargetBase();

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
    const char* version() const { return "fea_ifmgr_mirror/0.0"; }

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

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_add(
	// Input values,
	const string&	ifname) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_remove(
	// Input values,
	const string&	ifname) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_set_enabled(
	// Input values,
	const string&	ifname,
	const bool&	enabled) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_set_discard(
	// Input values,
	const string&	ifname,
	const bool&	discard) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_set_unreachable(
	// Input values,
	const string&	ifname,
	const bool&	unreachable) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_set_management(
	// Input values,
	const string&	ifname,
	const bool&	management) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_set_mtu(
	// Input values,
	const string&	ifname,
	const uint32_t&	mtu) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_set_mac(
	// Input values,
	const string&	ifname,
	const Mac&	mac) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_set_pif_index(
	// Input values,
	const string&	ifname,
	const uint32_t&	pif_index) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_interface_set_no_carrier(
	// Input values,
	const string&	ifname,
	const bool&	no_carrier) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_add(
	// Input values,
	const string&	ifname,
	const string&	vifname) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_remove(
	// Input values,
	const string&	ifname,
	const string&	vifname) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const bool&	enabled) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_multicast_capable(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const bool&	capable) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_broadcast_capable(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const bool&	capable) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_p2p_capable(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const bool&	capable) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_loopback(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const bool&	loopback) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_pim_register(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const bool&	pim_register) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_pif_index(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const uint32_t&	pif_index) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_vif_index(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const uint32_t&	vif_index) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_vlan(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const bool&	is_vlan) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_vif_set_vlan_id(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const uint32_t&	vlan_id) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv4_add(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv4_remove(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv4_set_prefix(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const uint32_t&	prefix_len) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv4_set_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	enabled) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv4_set_multicast_capable(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	capable) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv4_set_loopback(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const bool&	loopback) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv4_set_broadcast(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const IPv4&	broadcast_addr) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv4_set_endpoint(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv4&	addr,
	const IPv4&	endpoint_addr) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv6_add(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv6_remove(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv6_set_prefix(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	prefix_len) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv6_set_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const bool&	enabled) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv6_set_loopback(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const bool&	loopback) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv6_set_multicast_capable(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const bool&	capable) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_ipv6_set_endpoint(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const IPv6&	endpoint_addr) = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_hint_tree_complete() = 0;

    virtual XrlCmdError fea_ifmgr_mirror_0_1_hint_updates_made() = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_add(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_remove(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_set_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_set_discard(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_set_unreachable(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_set_management(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_set_mtu(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_set_mac(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_set_pif_index(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_interface_set_no_carrier(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_add(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_remove(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_multicast_capable(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_broadcast_capable(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_p2p_capable(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_loopback(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_pim_register(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_pif_index(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_vif_index(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_vlan(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_vif_set_vlan_id(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv4_add(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv4_remove(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv4_set_prefix(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv4_set_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv4_set_multicast_capable(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv4_set_loopback(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv4_set_broadcast(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv4_set_endpoint(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv6_add(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv6_remove(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv6_set_prefix(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv6_set_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv6_set_loopback(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv6_set_multicast_capable(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_ipv6_set_endpoint(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_hint_tree_complete(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_fea_ifmgr_mirror_0_1_hint_updates_made(const XrlArgs& in, XrlArgs* out);

    void add_handlers();
    void remove_handlers();
};

#endif // __XRL_TARGETS_FEA_IFMGR_MIRROR_BASE_HH__
