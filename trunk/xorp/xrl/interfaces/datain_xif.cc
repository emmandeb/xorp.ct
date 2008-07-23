/*
 * Copyright (c) 2001-2008 XORP, Inc.
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/datain_xif.cc,v 1.19 2008/01/04 03:17:52 pavlin Exp $"

#include "datain_xif.hh"

bool
XrlDatainV0p1Client::send_receive(
	const char*	dst_xrl_target_name,
	const string&	peer,
	const uint32_t&	genid,
	const bool&	status,
	const uint32_t&	secs,
	const uint32_t&	micro,
	const vector<uint8_t>&	data,
	const ReceiveCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "datain/0.1/receive");
    x.args().add("peer", peer);
    x.args().add("genid", genid);
    x.args().add("status", status);
    x.args().add("secs", secs);
    x.args().add("micro", micro);
    x.args().add("data", data);
    return _sender->send(x, callback(this, &XrlDatainV0p1Client::unmarshall_receive, cb));
}


/* Unmarshall receive */
void
XrlDatainV0p1Client::unmarshall_receive(
	const XrlError&	e,
	XrlArgs*	a,
	ReceiveCB		cb
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
XrlDatainV0p1Client::send_error(
	const char*	dst_xrl_target_name,
	const string&	peer,
	const uint32_t&	genid,
	const string&	reason,
	const ErrorCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "datain/0.1/error");
    x.args().add("peer", peer);
    x.args().add("genid", genid);
    x.args().add("reason", reason);
    return _sender->send(x, callback(this, &XrlDatainV0p1Client::unmarshall_error, cb));
}


/* Unmarshall error */
void
XrlDatainV0p1Client::unmarshall_error(
	const XrlError&	e,
	XrlArgs*	a,
	ErrorCB		cb
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
XrlDatainV0p1Client::send_closed(
	const char*	dst_xrl_target_name,
	const string&	peer,
	const uint32_t&	genid,
	const ClosedCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "datain/0.1/closed");
    x.args().add("peer", peer);
    x.args().add("genid", genid);
    return _sender->send(x, callback(this, &XrlDatainV0p1Client::unmarshall_closed, cb));
}


/* Unmarshall closed */
void
XrlDatainV0p1Client::unmarshall_closed(
	const XrlError&	e,
	XrlArgs*	a,
	ClosedCB		cb
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
