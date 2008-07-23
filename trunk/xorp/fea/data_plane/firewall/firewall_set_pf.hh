// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2008 XORP, Inc.
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

// $XORP: xorp/fea/data_plane/firewall/firewall_set_pf.hh,v 1.3 2008/04/28 05:21:07 pavlin Exp $

#ifndef __FEA_DATA_PLANE_FIREWALL_FIREWALL_SET_PF_HH__
#define __FEA_DATA_PLANE_FIREWALL_FIREWALL_SET_PF_HH__

#include <map>

#include "fea/firewall_set.hh"


class FirewallSetPf : public FirewallSet {
public:
    // Firewall entries trie indexed by rule number
    typedef map<uint32_t, FirewallEntry> FirewallTrie;

    /**
     * Constructor.
     *
     * @param fea_data_plane_manager the corresponding data plane manager
     * (@ref FeaDataPlaneManager).
     */
    FirewallSetPf(FeaDataPlaneManager& fea_data_plane_manager);

    /**
     * Virtual destructor.
     */
    virtual ~FirewallSetPf();

    /**
     * Start operation.
     * 
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int start(string& error_msg);
    
    /**
     * Stop operation.
     *
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int stop(string& error_msg);

    /**
     * Update the firewall entries by pushing them into the underlying system.
     *
     * @param added_entries the entries to add.
     * @param replaced_entries the entries to replace.
     * @param deleted_entries the deleted entries.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int update_entries(const list<FirewallEntry>& added_entries,
			       const list<FirewallEntry>& replaced_entries,
			       const list<FirewallEntry>& deleted_entries,
			       string& error_msg);

    /**
     * Set the IPv4 firewall table.
     *
     * @param firewall_entry_list the list with all entries to install into
     * the IPv4 firewall table.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int set_table4(const list<FirewallEntry>& firewall_entry_list,
			   string& error_msg);

    /**
     * Delete all entries in the IPv4 firewall table.
     *
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int delete_all_entries4(string& error_msg);

    /**
     * Set the IPv6 firewall table.
     *
     * @param firewall_entry_list the list with all entries to install into
     * the IPv6 firewall table.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int set_table6(const list<FirewallEntry>& firewall_entry_list,
			   string& error_msg);

    /**
     * Delete all entries in the IPv6 firewall table.
     *
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int delete_all_entries6(string& error_msg);

private:

    /**
     * Add a single firewall entry.
     *
     * @param firewall_entry the entry to add.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int add_entry(const FirewallEntry& firewall_entry,
			  string& error_msg);

    /**
     * Replace a single firewall entry.
     *
     * @param firewall_entry the replacement entry.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int replace_entry(const FirewallEntry& firewall_entry,
			      string& error_msg);

    /**
     * Delete a single firewall entry.
     *
     * @param firewall_entry the entry to delete.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    virtual int delete_entry(const FirewallEntry& firewall_entry,
			     string& error_msg);

    /**
     * Start a transaction for manipulating the firewall table.
     *
     * @param ticket return-by-reference ticket for the transaction.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    int start_transaction(uint32_t& ticket, string& error_msg);

    /**
     * Commit a transaction for manipulating the firewall table.
     *
     * @param ticket the ticket for the transaction.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    int commit_transaction(uint32_t ticket, string& error_msg);

    /**
     * Abort a transaction for manipulating the firewall table.
     *
     * @param ticket the ticket for the transaction.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    int abort_transaction(uint32_t ticket, string& error_msg);

    /**
     * Push all locally stored firewall entries.
     *
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    int push_entries(string& error_msg);

    /**
     * Add or delete a single firewall entry as part of a transaction.
     *
     * @param is_add if true, then add the entry, otherwise delete it.
     * @param ticket the ticket for the transaction.
     * @param firewall_entry the entry to add.
     * @param error_msg the error message (if error).
     * @return XORP_OK on success, otherwise XORP_ERROR.
     */
    int add_delete_transaction_entry(bool is_add, uint32_t ticket,
				     const FirewallEntry& firewall_entry,
				     string& error_msg);

    int		_fd;		// The file descriptor for firewall access

    // The locally saved firewall entries
    FirewallTrie	_firewall_entries4;
    FirewallTrie	_firewall_entries6;

    static const string _pf_device_name;	// The PF device name
};

#endif // __FEA_DATA_PLANE_FIREWALL_FIREWALL_SET_PF_HH__
