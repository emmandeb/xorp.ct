// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001,2002 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the Xorp LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the Xorp LICENSE file; the license in that file is
// legally binding.

// $XORP: xorp/bgp/route_table_cache.hh,v 1.1.1.1 2002/12/11 23:55:50 hodson Exp $

#ifndef __BGP_ROUTE_TABLE_CACHE_HH__
#define __BGP_ROUTE_TABLE_CACHE_HH__

#include "route_table_base.hh"
#include "libxorp/trie.hh"

template<class A>
class CacheTable : public BGPRouteTable<A>  {
public:
    CacheTable(string tablename, BGPRouteTable<A> *parent);
    int add_route(const InternalMessage<A> &rtmsg,
		  BGPRouteTable<A> *caller);
    int replace_route(const InternalMessage<A> &old_rtmsg,
		      const InternalMessage<A> &new_rtmsg,
		      BGPRouteTable<A> *caller);
    int delete_route(const InternalMessage<A> &rtmsg, 
		     BGPRouteTable<A> *caller);
    int push(BGPRouteTable<A> *caller);
    int route_dump(const InternalMessage<A> &rtmsg,
		   BGPRouteTable<A> *caller,
		   const PeerHandler *dump_peer);

    void flush_cache();
    const SubnetRoute<A> *lookup_route(const IPNet<A> &net) const;
    void route_used(const SubnetRoute<A>* route, bool in_use);

    RouteTableType type() const {return CACHE_TABLE;}
    string str() const;

    /* mechanisms to implement flow control in the output plumbing */
    void output_state(bool busy, BGPRouteTable<A> *next_table);
    bool get_next_message(BGPRouteTable<A> *next_table);

    int route_count() const {
	return _route_table.route_count();
    }
private:
    Trie<A, const SubnetRoute<A> > _route_table;
};

#endif // __BGP_ROUTE_TABLE_CACHE_HH__
