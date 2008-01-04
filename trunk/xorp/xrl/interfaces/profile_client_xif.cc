/*
 * Copyright (c) 2001-2008 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/profile_client_xif.cc,v 1.8 2007/07/16 22:29:26 pavlin Exp $"

#include "profile_client_xif.hh"

bool
XrlProfileClientV0p1Client::send_log(
	const char*	dst_xrl_target_name,
	const string&	pname,
	const uint32_t&	sec,
	const uint32_t&	usec,
	const string&	comment,
	const LogCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "profile_client/0.1/log");
    x.args().add("pname", pname);
    x.args().add("sec", sec);
    x.args().add("usec", usec);
    x.args().add("comment", comment);
    return _sender->send(x, callback(this, &XrlProfileClientV0p1Client::unmarshall_log, cb));
}


/* Unmarshall log */
void
XrlProfileClientV0p1Client::unmarshall_log(
	const XrlError&	e,
	XrlArgs*	a,
	LogCB		cb
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
XrlProfileClientV0p1Client::send_finished(
	const char*	dst_xrl_target_name,
	const string&	pname,
	const FinishedCB&	cb
)
{
    Xrl x(dst_xrl_target_name, "profile_client/0.1/finished");
    x.args().add("pname", pname);
    return _sender->send(x, callback(this, &XrlProfileClientV0p1Client::unmarshall_finished, cb));
}


/* Unmarshall finished */
void
XrlProfileClientV0p1Client::unmarshall_finished(
	const XrlError&	e,
	XrlArgs*	a,
	FinishedCB		cb
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
