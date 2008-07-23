/*
 * Copyright (c) 2001-2008 XORP, Inc.
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/mld6igmp_client_xif.cc,v 1.19 2008/01/04 03:17:56 pavlin Exp $"

#include "mld6igmp_client_xif.hh"

bool
XrlMld6igmpClientV0p1Client::send_add_membership4(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv4&	source,
	const IPv4&	group,
	const AddMembership4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp_client/0.1/add_membership4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source", source);
    x.args().add("group", group);
    return _sender->send(x, callback(this, &XrlMld6igmpClientV0p1Client::unmarshall_add_membership4, cb));
}


/* Unmarshall add_membership4 */
void
XrlMld6igmpClientV0p1Client::unmarshall_add_membership4(
	const XrlError&	e,
	XrlArgs*	a,
	AddMembership4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMld6igmpClientV0p1Client::send_add_membership6(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv6&	source,
	const IPv6&	group,
	const AddMembership6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp_client/0.1/add_membership6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source", source);
    x.args().add("group", group);
    return _sender->send(x, callback(this, &XrlMld6igmpClientV0p1Client::unmarshall_add_membership6, cb));
}


/* Unmarshall add_membership6 */
void
XrlMld6igmpClientV0p1Client::unmarshall_add_membership6(
	const XrlError&	e,
	XrlArgs*	a,
	AddMembership6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMld6igmpClientV0p1Client::send_delete_membership4(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv4&	source,
	const IPv4&	group,
	const DeleteMembership4CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp_client/0.1/delete_membership4");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source", source);
    x.args().add("group", group);
    return _sender->send(x, callback(this, &XrlMld6igmpClientV0p1Client::unmarshall_delete_membership4, cb));
}


/* Unmarshall delete_membership4 */
void
XrlMld6igmpClientV0p1Client::unmarshall_delete_membership4(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteMembership4CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlMld6igmpClientV0p1Client::send_delete_membership6(
	const char*	dst_xrl_target_name,
	const string&	xrl_sender_name,
	const string&	vif_name,
	const uint32_t&	vif_index,
	const IPv6&	source,
	const IPv6&	group,
	const DeleteMembership6CB&	cb
)
{
    Xrl x(dst_xrl_target_name, "mld6igmp_client/0.1/delete_membership6");
    x.args().add("xrl_sender_name", xrl_sender_name);
    x.args().add("vif_name", vif_name);
    x.args().add("vif_index", vif_index);
    x.args().add("source", source);
    x.args().add("group", group);
    return _sender->send(x, callback(this, &XrlMld6igmpClientV0p1Client::unmarshall_delete_membership6, cb));
}


/* Unmarshall delete_membership6 */
void
XrlMld6igmpClientV0p1Client::unmarshall_delete_membership6(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteMembership6CB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u)", XORP_UINT_CAST(a->size()), XORP_UINT_CAST(0));
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}
