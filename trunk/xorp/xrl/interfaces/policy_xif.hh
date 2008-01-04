/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/policy_xif.hh,v 1.15 2007/07/12 21:37:30 pavlin Exp $
 */

#ifndef __XRL_INTERFACES_POLICY_XIF_HH__
#define __XRL_INTERFACES_POLICY_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifPolicy"

#include "libxorp/xlog.h"
#include "libxorp/callback.hh"

#include "libxipc/xrl.hh"
#include "libxipc/xrl_error.hh"
#include "libxipc/xrl_sender.hh"


class XrlPolicyV0p1Client {
public:
    XrlPolicyV0p1Client(XrlSender* s) : _sender(s) {}
    virtual ~XrlPolicyV0p1Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr CreateTermCB;
    /**
     *  Send Xrl intended to:
     *
     *  Create a term in a policy. The term will be the last term in the policy
     *  statement.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param policy the name of the policy.
     *
     *  @param order position of term.
     *
     *  @param term the name of the term.
     */
    bool send_create_term(
	const char*	dst_xrl_target_name,
	const string&	policy,
	const string&	order,
	const string&	term,
	const CreateTermCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteTermCB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete a term in a policy.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param policy the name of the policy.
     *
     *  @param term the name of the term.
     */
    bool send_delete_term(
	const char*	dst_xrl_target_name,
	const string&	policy,
	const string&	term,
	const DeleteTermCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr UpdateTermBlockCB;
    /**
     *  Send Xrl intended to:
     *
     *  Update the source/dest/action block of a term in a policy. Note: if
     *  statement is empty, the previous one in that position will be deleted.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param policy the name of the policy.
     *
     *  @param term the name of the term.
     *
     *  @param block the block to update (0:source, 1:dest, 2:action).
     *
     *  @param order numerical position (local) of statement.
     *
     *  @param statement the statement to insert or delete.
     */
    bool send_update_term_block(
	const char*	dst_xrl_target_name,
	const string&	policy,
	const string&	term,
	const uint32_t&	block,
	const string&	order,
	const string&	statement,
	const UpdateTermBlockCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CreatePolicyCB;
    /**
     *  Send Xrl intended to:
     *
     *  Create a policy.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param policy name of the policy.
     */
    bool send_create_policy(
	const char*	dst_xrl_target_name,
	const string&	policy,
	const CreatePolicyCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeletePolicyCB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete a policy.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param policy name of the policy.
     */
    bool send_delete_policy(
	const char*	dst_xrl_target_name,
	const string&	policy,
	const DeletePolicyCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CreateSetCB;
    /**
     *  Send Xrl intended to:
     *
     *  Create a set.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param set name of the set.
     */
    bool send_create_set(
	const char*	dst_xrl_target_name,
	const string&	set,
	const CreateSetCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr UpdateSetCB;
    /**
     *  Send Xrl intended to:
     *
     *  Replace elements in a set.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param type the type of the set.
     *
     *  @param set name of the set.
     *
     *  @param elements comma delimited list of set elements.
     */
    bool send_update_set(
	const char*	dst_xrl_target_name,
	const string&	type,
	const string&	set,
	const string&	elements,
	const UpdateSetCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteSetCB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete a set.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param set name of the set.
     */
    bool send_delete_set(
	const char*	dst_xrl_target_name,
	const string&	set,
	const DeleteSetCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddToSetCB;
    /**
     *  Send Xrl intended to:
     *
     *  Add an element to a set.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param type the type of the set.
     *
     *  @param set name of the set.
     *
     *  @param element the element to add.
     */
    bool send_add_to_set(
	const char*	dst_xrl_target_name,
	const string&	type,
	const string&	set,
	const string&	element,
	const AddToSetCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DeleteFromSetCB;
    /**
     *  Send Xrl intended to:
     *
     *  Delete an element from a set.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param type the type of the set.
     *
     *  @param set name of the set.
     *
     *  @param element the element to delete.
     */
    bool send_delete_from_set(
	const char*	dst_xrl_target_name,
	const string&	type,
	const string&	set,
	const string&	element,
	const DeleteFromSetCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr DoneGlobalPolicyConfCB;
    /**
     *  Send Xrl intended to:
     *
     *  Commit the configuration.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     */
    bool send_done_global_policy_conf(
	const char*	dst_xrl_target_name,
	const DoneGlobalPolicyConfCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr ImportCB;
    /**
     *  Send Xrl intended to:
     *
     *  Replace import/export policies for a protocol. Will normally cause a
     *  delayed commit.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param protocol protocol for which policies must be replaced.
     *
     *  @param policies comma separated list of policies.
     */
    bool send_import(
	const char*	dst_xrl_target_name,
	const string&	protocol,
	const string&	policies,
	const ImportCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr ExportCB;

    bool send_export(
	const char*	dst_xrl_target_name,
	const string&	protocol,
	const string&	policies,
	const ExportCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr AddVarmapCB;
    /**
     *  Send Xrl intended to:
     *
     *  Add a variable to the varmap configuration.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param protocol the protocol this variable is available to.
     *
     *  @param variable name of the variable.
     *
     *  @param type the type of the variable.
     *
     *  @param access the permissions on the variable (r/rw).
     *
     *  @param id unique id for this var. Scoped by protocol.
     */
    bool send_add_varmap(
	const char*	dst_xrl_target_name,
	const string&	protocol,
	const string&	variable,
	const string&	type,
	const string&	access,
	const uint32_t&	id,
	const AddVarmapCB&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const string*>::RefPtr DumpStateCB;
    /**
     *  Send Xrl intended to:
     *
     *  Dump state of policy manager. To be used ONLY for debugging.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param id which aspect of the internal state to dump.
     */
    bool send_dump_state(
	const char*	dst_xrl_target_name,
	const uint32_t&	id,
	const DumpStateCB&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr SetProtoTargetCB;
    /**
     *  Send Xrl intended to:
     *
     *  Update the mapping from protocols to their XRL target name.
     *
     *  @param dst_xrl_target_name the Xrl target name of the destination.
     *
     *  @param protocol protocol to update.
     *
     *  @param target XRL target for the protocol.
     */
    bool send_set_proto_target(
	const char*	dst_xrl_target_name,
	const string&	protocol,
	const string&	target,
	const SetProtoTargetCB&	cb
    );

protected:
    XrlSender* _sender;

private:
    void unmarshall_create_term(
	const XrlError&	e,
	XrlArgs*	a,
	CreateTermCB		cb
    );

    void unmarshall_delete_term(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteTermCB		cb
    );

    void unmarshall_update_term_block(
	const XrlError&	e,
	XrlArgs*	a,
	UpdateTermBlockCB		cb
    );

    void unmarshall_create_policy(
	const XrlError&	e,
	XrlArgs*	a,
	CreatePolicyCB		cb
    );

    void unmarshall_delete_policy(
	const XrlError&	e,
	XrlArgs*	a,
	DeletePolicyCB		cb
    );

    void unmarshall_create_set(
	const XrlError&	e,
	XrlArgs*	a,
	CreateSetCB		cb
    );

    void unmarshall_update_set(
	const XrlError&	e,
	XrlArgs*	a,
	UpdateSetCB		cb
    );

    void unmarshall_delete_set(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteSetCB		cb
    );

    void unmarshall_add_to_set(
	const XrlError&	e,
	XrlArgs*	a,
	AddToSetCB		cb
    );

    void unmarshall_delete_from_set(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteFromSetCB		cb
    );

    void unmarshall_done_global_policy_conf(
	const XrlError&	e,
	XrlArgs*	a,
	DoneGlobalPolicyConfCB		cb
    );

    void unmarshall_import(
	const XrlError&	e,
	XrlArgs*	a,
	ImportCB		cb
    );

    void unmarshall_export(
	const XrlError&	e,
	XrlArgs*	a,
	ExportCB		cb
    );

    void unmarshall_add_varmap(
	const XrlError&	e,
	XrlArgs*	a,
	AddVarmapCB		cb
    );

    void unmarshall_dump_state(
	const XrlError&	e,
	XrlArgs*	a,
	DumpStateCB		cb
    );

    void unmarshall_set_proto_target(
	const XrlError&	e,
	XrlArgs*	a,
	SetProtoTargetCB		cb
    );

};

#endif /* __XRL_INTERFACES_POLICY_XIF_HH__ */
