// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2003 International Computer Science Institute
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

#ident "$XORP: xorp/rtrmgr/cli.cc,v 1.20 2004/01/13 00:24:35 pavlin Exp $"

#include "rtrmgr_module.h"
#include <pwd.h>
#include "cli.hh"
#include "command_tree.hh"
#include "slave_conf_tree.hh"
#include "slave_conf_tree_node.hh"
#include "template_tree.hh"
#include "template_tree_node.hh"
#include "op_commands.hh"
#include "util.hh"


RouterCLI::RouterCLI(XorpShell& xorpsh, CliNode& cli_node)
    : _xorpsh(xorpsh),
      _cli_node(cli_node),
      _cli_client(*(_cli_node.add_stdio_client())),
      _mode(CLI_MODE_NONE),
      _changes_made(false)
{
    _current_config_node = &(config_tree()->root_node());
    operational_mode();
}

RouterCLI::~RouterCLI()
{
    // TODO: for now we leave the deletion to be implicit when xorpsh exits
    // _cli_node.delete_stdio_client(&_cli_client);
}

void
RouterCLI::commit_done_by_user(int uid)
{
    // someone just did a commit, so we may need to regenerate options
    if (_mode == CLI_MODE_OPERATIONAL) {
	string message = c_format("\nUser %d changed the configuration.\n",
				  uid);
	_cli_client.cli_print(message);
	clear_command_set();
	add_op_mode_commands(NULL);
    }
}

void
RouterCLI::operational_mode()
{
    if (_mode == CLI_MODE_OPERATIONAL)
	return;

    _mode = CLI_MODE_OPERATIONAL;
    clear_command_set();
    reset_path();
    set_prompt("", "Xorp> ");
    add_op_mode_commands(NULL);
}

void
RouterCLI::add_op_mode_commands(CliCommand* com0)
{
    CliCommand *com1, *com2;
    // com0->add_command("clear", "Clear information in the system *");

    // If no root node is specified, default to the true root
    if (com0 == NULL)
	com0 = _cli_node.cli_command_root();

    if (com0 == _cli_node.cli_command_root()) {
	com1 = com0->add_command("configure",
				 "Switch to configuration mode",
				 callback(this, &RouterCLI::configure_func));
	com1->set_global_name("configure");
	com2 = com1->add_command("exclusive",
				 "Switch to configuration mode, locking out other users",
				 callback(this, &RouterCLI::configure_func));
	com2->set_global_name("configure exclusive");

	com0->add_command("help", "Provide help with commands");
	com0->add_command("quit", "Quit this command session");
    }

    set<string> cmds = op_cmd_list()->top_level_commands();
    set<string>::const_iterator iter;
    for (iter = cmds.begin(); iter != cmds.end(); ++iter) {
	com1 = com0->add_command(*iter, "help");
	com1->set_global_name(*iter);
	// Set the callback to generate the node's children
	com1->set_dynamic_children(callback(op_cmd_list(),
					    &OpCommandList::childlist));
	// Set the callback to pass to the node's children when they
	// are executed
	com1->set_dynamic_process_callback(callback(this,
						    &RouterCLI::op_mode_func));
    }

    //    com0->add_command("file", "Perform file operations");
    //    com0->add_command("ping", "Ping a network host");
    //    _set_node = com0->add_command("set", "Set CLI properties");
    //    _show_node = com0->add_command("show", "Show router operational imformation");
    //    com0->add_command("traceroute", "Trace the unicast path to a network host");
}

void
RouterCLI::configure_mode()
{
    _nesting_depth = 0;
    if (_mode == CLI_MODE_CONFIGURE)
	return;

    if (_mode != CLI_MODE_TEXTENTRY) {
	display_config_mode_users();
    }
    display_alerts();
    _mode = CLI_MODE_CONFIGURE;
    clear_command_set();

    set_prompt("", "XORP> ");

    // Add all the menus
    apply_path_change();
}

void
RouterCLI::display_config_mode_users() const
{
    _cli_client.cli_print("Entering configuration mode.\n");
    if (_config_mode_users.empty()) {
	_cli_client.cli_print("There are no other users in configuration mode.\n");
    } else {
	if (_config_mode_users.size() == 1)
	    _cli_client.cli_print("User ");
	else
	    _cli_client.cli_print("Users ");
	list<uint32_t>::const_iterator iter, iter2;
	struct passwd* pwent;
	for (iter = _config_mode_users.begin();
	    iter != _config_mode_users.end();
	    ++iter) {
	    if (iter != _config_mode_users.begin()) {
		iter2 = iter;
		++iter2;
		if (iter2 == _config_mode_users.end())
		    _cli_client.cli_print(" and ");
		else
		    _cli_client.cli_print(", ");
	    }
	    pwent = getpwuid(*iter);
	    if (pwent == NULL)
		_cli_client.cli_print(c_format("UID:%d", *iter));
	    else
		_cli_client.cli_print(pwent->pw_name);
	}
	endpwent();
	if (_config_mode_users.size() == 1)
	    _cli_client.cli_print(" is also in configuration mode.\n");
	else
	    _cli_client.cli_print(" are also in configuration mode.\n");
    }
}

void
RouterCLI::display_alerts()
{
    // Display any alert messages that accumulated while we were busy
    while (!_alerts.empty()) {
	_cli_client.cli_print(_alerts.front());
	_alerts.pop_front();
    }
}

bool
RouterCLI::is_config_mode() const
{
    // This is a switch statement to get compile time checking
    switch (_mode) {
    case CLI_MODE_NONE:
    case CLI_MODE_OPERATIONAL:
	return false;
    case CLI_MODE_CONFIGURE:
    case CLI_MODE_TEXTENTRY:
	return true;
    }
    XLOG_UNREACHABLE();
}

void
RouterCLI::text_entry_mode()
{
    string prompt;

    _mode = CLI_MODE_TEXTENTRY;
    clear_command_set();

    prompt = "    > ";
    for (size_t i = 0; i < _nesting_depth; i++)
	prompt += "  ";
    set_prompt("", prompt);
}

void
RouterCLI::add_static_configure_mode_commands()
{
    CliCommand *com0, *com1, *com2;
    com0 = _cli_node.cli_command_root();
    if (_changes_made) {
	com0->add_command("commit", "Commit the current set of changes",
			  callback(this, &RouterCLI::commit_func));
    }

    _delete_node = com0->add_command("delete",
				     "Delete a configuration element");

    // Edit command
    _edit_node = com0->add_command("edit", "Edit a sub-element");
    _edit_node->set_global_name("edit");

    // Exit command
    com1 = com0->add_command("exit", "Exit from this configuration level",
			     callback(this, &RouterCLI::exit_func));
    com1->set_global_name("exit");
    com2 = com1->add_command("configuration-mode",
			     "Exit from configuration mode",
			     callback(this, &RouterCLI::exit_func));
    com2->set_global_name("exit configuration-mode");
    com2 = com1->add_command("discard",
			     "Exit from configuration mode, discarding changes",
			     callback(this, &RouterCLI::exit_func));
    com2->set_global_name("exit discard");

    com0->add_command("help", "Provide help with commands");
    //    com0->add_command("insert", "Insert a new configuration element");

    // Load Command
    com1 = com0->add_command("load", "Load configuration from a file",
			     callback(this, &RouterCLI::load_func));
    com1->set_global_name("load");

    // Quit Command
    com1 = com0->add_command("quit", "Quit from this level",
			     callback(this, &RouterCLI::exit_func));
    com1->set_global_name("quit");

    _run_node = com0->add_command("run", "Run an operational-mode command");
    add_op_mode_commands(_run_node);

    com1 = com0->add_command("save", "Save configuration to a file",
			     callback(this, &RouterCLI::save_func));
    com1->set_global_name("save");

    // Set Command
    _set_node = com0->add_command("set", "Set the value of a parameter");

    // Show Command
    _show_node = com0->add_command("show", "Show the value of a parameter",
				   callback(this, &RouterCLI::show_func));

    // Top Command
    com1 = com0->add_command("top", "Exit to top level of configuration",
			     callback(this, &RouterCLI::exit_func));
    com1->set_global_name("top");

    // Up Command
    com1 = com0->add_command("up", "Exit one level of configuration",
			     callback(this, &RouterCLI::exit_func));
    com1->set_global_name("up");
}

void
RouterCLI::reset_path()
{
    while (_path.size() > 0)
	_path.pop_front();
}

void
RouterCLI::set_path(string path)
{
    reset_path();
    debug_msg("set path: >%s<\n", path.c_str());
    string::size_type ix;
    while (path.size() > 0) {
	ix = path.find(' ');
	if (ix == string::npos && path.size() > 0) {
	    _path.push_back(path);
	    break;
	} else {
	    _path.push_back(path.substr(0, ix));
	    path = path.substr(ix + 1, path.size() - ix + 1);
	}
    }
}

void
RouterCLI::config_mode_prompt()
{
    string prompt;

    if (pathstr() == "") {
	prompt = "[edit]";
    } else {
	prompt = "[edit " + pathstr() + "]";
    }
    set_prompt(prompt, "XORP> ");
}

void
RouterCLI::apply_path_change()
{
    _cli_node.cli_command_root()->delete_all_commands();
    add_static_configure_mode_commands();

    // Rebuild the command subtree for the edit command
    _edit_node->delete_all_commands();

    //
    // Note: the edit subtree must be done before the other subtrees,
    // because it can force a path change in the root node if the edit
    // subtree is not a node that can be editted.
    //
    add_edit_subtree();

    _delete_node->delete_all_commands();
    add_delete_subtree();

    // Rebuild the command subtree for the set command
    _set_node->delete_all_commands();
    add_set_subtree();

    // Rebuild the command subtree for the show command
    _show_node->delete_all_commands();
    add_show_subtree();
    string cmdpath;
    if (_path.empty())
	cmdpath = "show";
    else
	cmdpath = "show " + pathstr();
    _show_node->set_global_name(cmdpath);

    // Set the prompt appropriately
    config_mode_prompt();
}

void
RouterCLI::set_prompt(const string& line1, const string& line2)
{
    if (line1 != "") {
	_cli_client.cli_print(line1 + "\n");
    }
    _cli_node.cli_command_root()->set_allow_cd(true, line2);
    _cli_client.set_current_cli_prompt(line2);
}

void
RouterCLI::add_command_subtree(CliCommand& current_cli_node,
			       const CommandTreeNode& current_ctn,
			       const CLI_PROCESS_CALLBACK& cb,
			       string path,
			       size_t depth)
{
    const list<CommandTreeNode*>& children = current_ctn.children();
    if (depth > 0) {
	if (path.empty())
	    path = current_ctn.name();
	else
	    path += " " + current_ctn.name();
    }

    list<CommandTreeNode*>::const_iterator cmd_iter;
    for (cmd_iter = children.begin(); cmd_iter != children.end(); ++cmd_iter) {
	string cmd_name = (*cmd_iter)->name();
	CliCommand* com;
	string subpath = path + " " + cmd_name;
	if ((*cmd_iter)->has_command()) {
	    com = current_cli_node.add_command(cmd_name,
					       "help", cb);
	} else {
	    com = current_cli_node.add_command(cmd_name,
					       "help");
	}
	if (com == NULL) {
	    XLOG_FATAL("add_command %s failed", cmd_name.c_str());
	} else {
	    com->set_global_name(subpath);
	}
	add_command_subtree(*com, *(*cmd_iter), cb, path, depth + 1);
    }
}

void
RouterCLI::add_immediate_commands(CliCommand& current_cli_node,
				  const CommandTree& command_tree,
				  const list<string>& cmd_names,
				  bool include_intermediates,
				  const CLI_PROCESS_CALLBACK& cb,
				  const string& path)
{
    string subpath;
    set<string> existing_children;

    const list<CommandTreeNode*>& children = command_tree.root_node().children();
    list<CommandTreeNode*>::const_iterator cmd_iter;
    for (cmd_iter = children.begin(); cmd_iter != children.end(); ++cmd_iter) {
	if (include_intermediates || (*cmd_iter)->has_command()) {
	    if (path.empty())
		subpath = (*cmd_iter)->name();
	    else
		subpath = path + " " + (*cmd_iter)->name();

	    CliCommand* com;
	    com = current_cli_node.add_command((*cmd_iter)->name(),
					       "help", cb);
	    if (com == NULL) {
		XLOG_FATAL("AI: add_command %s failed",
			   (*cmd_iter)->name().c_str());
	    } else {
		com->set_global_name(subpath);
	    }
	    existing_children.insert((*cmd_iter)->name());
	}
    }

    const TemplateTreeNode* ttn;
    if (_current_config_node->is_root_node()) {
	ttn = template_tree()->root_node();
    } else {
	ttn = _current_config_node->template_tree_node();
    }
    XLOG_ASSERT(ttn != NULL);

    list<TemplateTreeNode*>::const_iterator tti;
    for (tti = ttn->children().begin(); tti != ttn->children().end(); ++tti) {
	// we don't need to consider this child if it's already added
	if (existing_children.find((*tti)->segname())
	    != existing_children.end()) {
	    continue;
	}
	if ((*tti)->check_command_tree(cmd_names, include_intermediates,
				       /* depth */ 0)) {
	    if (path.empty())
		subpath = (*tti)->segname();
	    else
		subpath = path + " " + (*tti)->segname();

	    CliCommand* com;
	    com = current_cli_node.add_command((*tti)->segname(),
					       "help", cb);
	    if (com == NULL) {
		XLOG_FATAL("AI: add_command %s for template failed",
			   (*tti)->segname().c_str());
	    } else {
		com->set_global_name(subpath);
	    }
	}
    }
}

void
RouterCLI::clear_command_set()
{
    CliCommand* com0;

    com0 = _cli_node.cli_command_root();
    com0->delete_all_commands();
}

string
RouterCLI::pathstr() const
{
    string s;
    list<string>::const_iterator iter;

    for (iter = _path.begin(); iter != _path.end(); ++iter) {
	if (s.empty())
	    s = *iter;
	else
	    s += " " + *iter;
    }
    return s;
}

string
RouterCLI::pathstr2() const
{
    string s;
    list<string>::const_iterator iter;

    for (iter = _path.begin(); iter != _path.end(); ++iter) {
	if (s.empty())
	    s = ">" + *iter + "<";
	else
	    s += " >" + *iter + "<";
    }
    return s;
}

void
RouterCLI::add_edit_subtree()
{
    CommandTree cmd_tree;
    list<string> cmds;

    cmds.push_back("%create");
    cmds.push_back("%activate");
    if (_nesting_depth == 0) {
	_current_config_node = config_tree()->find_node(_path);
    }
    XLOG_ASSERT(_current_config_node != NULL);

    //
    // If we ended up at a node that can't be the root for an edit
    // tree, go back up one level now.
    //
    const TemplateTreeNode* ttn = _current_config_node->template_tree_node();
    if (ttn != NULL) {
	if (ttn->is_tag() && !_path.empty()) {
	    _path.pop_back();
	    _current_config_node = _current_config_node->parent();
	}
    }

    _current_config_node->create_command_tree(cmd_tree,
					      cmds,
					      /* include_intermediates */ true,
					      /* include templates */ true);
#ifdef DEBUG_CMD_TREES
    printf("==============================================================\n");
    printf("edit subtree is:\n\n");
    cmd_tree->print();
    printf("==============================================================\n");
#endif

    if (_nesting_depth == 0) {
	string cmdpath;
	if (_path.empty())
	    cmdpath = "edit";
	else
	    cmdpath = "edit " + pathstr();

	add_command_subtree(*_edit_node, cmd_tree.root_node(),
			    callback(this, &RouterCLI::edit_func),
			    cmdpath, 0);
    }
    add_immediate_commands(*(_cli_node.cli_command_root()),
			   cmd_tree,
			   cmds,
			   /* include_intermediates */ true,
			   callback(this, &RouterCLI::text_entry_func),
			   pathstr());
}

void
RouterCLI::add_delete_subtree()
{
    CommandTree cmd_tree;
    list<string> cmds;

    cmds.push_back("%create");
    cmds.push_back("%activate");
    cmds.push_back("%set");
    cmds.push_back("%delete");
    _current_config_node->create_command_tree(cmd_tree,
					      cmds,
					      /* include_intermediates */ true,
					      /* include templates */ false);
#ifdef DEBUG_CMD_TREES
    printf("==============================================================\n");
    printf("delete subtree is:\n\n");
    cmd_tree->print();
    printf("==============================================================\n");
#endif

    string cmdpath;
    if (_path.empty())
	cmdpath = "delete";
    else
	cmdpath = "delete " + pathstr();

    add_command_subtree(*_delete_node, cmd_tree.root_node(),
			callback(this, &RouterCLI::delete_func),
			cmdpath, 0);
}

void
RouterCLI::add_set_subtree()
{
    CommandTree cmd_tree;
    list<string> cmds;

    cmds.push_back("%set");
    _current_config_node->create_command_tree(cmd_tree,
					      cmds,
					      /* include_intermediates */false,
					      /* include templates */ true);

#ifdef DEBUG_CMD_TREES
    printf("==============================================================\n");
    printf("set subtree is:\n\n");
    cmd_tree->print();
    printf("==============================================================\n");
#endif

    if (_nesting_depth == 0) {
	string cmdpath;
	if (_path.empty())
	    cmdpath = "set";
	else
	    cmdpath = "set " + pathstr();

	add_command_subtree(*_set_node, cmd_tree.root_node(),
			    callback(this, &RouterCLI::set_func),
			    cmdpath, 0);
    }
    add_immediate_commands(*(_cli_node.cli_command_root()),
			   cmd_tree,
			   cmds,
			   /* include_intermediates */ false,
			   callback(this, &RouterCLI::immediate_set_func),
			   pathstr());
}

void
RouterCLI::add_show_subtree()
{
    CommandTree cmd_tree;
    list<string> cmds;

    cmds.push_back("%get");
    _current_config_node->create_command_tree(cmd_tree,
					      cmds,
					      /* include_intermediates */ true,
					      /* include templates */ false);

#ifdef DEBUG_CMD_TREES
    printf("==============================================================\n");
    printf("show subtree is:\n\n");
    cmd_tree->print();
    printf("==============================================================\n");
#endif

    string cmdpath;
    if (_path.empty())
	cmdpath = "show";
    else
	cmdpath = "show " + pathstr();

    add_command_subtree(*_show_node, cmd_tree.root_node(),
			callback(this, &RouterCLI::show_func),
			cmdpath, 0);
}

int
RouterCLI::configure_func(const string& ,
			  const string& ,
			  uint32_t ,
			  const string& command_global_name,
			  const vector<string>& /* argv */)
{
    bool exclusive = false;

    if (command_global_name == "configure exclusive")
	exclusive = true;

    idle_ui();
    _xorpsh.enter_config_mode(exclusive,
			       callback(this, &RouterCLI::enter_config_done));
     return (XORP_OK);
}

void
RouterCLI::enter_config_done(const XrlError& e)
{
    if (e != XrlError::OKAY()) {
	if ((e == XrlError::COMMAND_FAILED()) && (e.note() == "AUTH_FAIL")) {
	    check_for_rtrmgr_restart();
	    return;
	}
	_cli_client.cli_print(c_format("ERROR: %s\n", e.note().c_str()));
	//
	// Either something really bad happened, or a user that didn't
	// have permission attempted to enter config mode.
	//
	reenable_ui();
	return;
    }

   _xorpsh.get_config_users(callback(this, &RouterCLI::got_config_users));
}

void
RouterCLI::got_config_users(const XrlError& e, const XrlAtomList* users)
{
    // clear the old list
    if (e != XrlError::OKAY()) {
	if (e == XrlError::COMMAND_FAILED() && e.note() == "AUTH_FAIL") {
	    check_for_rtrmgr_restart();
	    return;
	}
	_cli_client.cli_print("ERROR: failed to get config users from rtrmgr\n");
    } else {
	while (!_config_mode_users.empty()) {
	    _config_mode_users.pop_front();
	}

	size_t nusers = users->size();
	bool doneme = false;
	for (size_t i = 0; i < nusers; i++) {
	    XrlAtom a;
	    a = users->get(i);
	    try {
		uint32_t uid = a.uint32();
		// Only include me if I'm in the list more than once.
		if (uid == getuid() && doneme == false)
		    doneme = true;
		else
		    _config_mode_users.push_back(uid);
	    }
	    catch (const XrlAtom::WrongType& wt) {
		// this had better not happen
		XLOG_FATAL("Internal Error");
	    }
	}
    }
    reset_path();
    configure_mode();
    reenable_ui();
}

void
RouterCLI::new_config_user(uid_t user_id)
{
    if (_mode == CLI_MODE_CONFIGURE || _mode == CLI_MODE_TEXTENTRY) {
	_config_mode_users.push_back(user_id);
	struct passwd* pwent = getpwuid(user_id);
	string username;
	if (pwent == NULL)
	    username = c_format("UID:%d", user_id);
	else
	    username = pwent->pw_name;
	string alert = c_format("User %s entered configuration mode\n",
				username.c_str());
	notify_user(alert, /* not urgent */ false);
    }
}

void
RouterCLI::leave_config_done(const XrlError& e)
{
    if (e != XrlError::OKAY()) {
	_cli_client.cli_print("ERROR: failed to inform rtrmgr of entry into config mode\n");
	// something really bad happened - should we just exit here?
	if (e == XrlError::COMMAND_FAILED() && e.note() == "AUTH_FAIL") {
	    check_for_rtrmgr_restart();
	    operational_mode();
	    return;
	}
    }
    operational_mode();
    reenable_ui();
}

void
RouterCLI::notify_user(const string& alert, bool urgent)
{
    if (_mode == CLI_MODE_TEXTENTRY && !urgent) {
	_alerts.push_back(alert);
    } else {
	_cli_client.cli_print(alert);
    }
}

int
RouterCLI::exit_func(const string& ,
		     const string& ,
		     uint32_t ,
		     const string& command_global_name,
		     const vector<string>& argv)
{
    if (command_global_name == "exit configuration-mode") {
	if (argv.size() > 0) {
	    _cli_client.cli_print("Error: \"exit configuration-mode\"  does not take any additional parameters\n");
	    return (XORP_ERROR);
	}
	if (_changes_made) {
	    _cli_client.cli_print("Error: There are uncommitted changes\n");
	    _cli_client.cli_print("Use \"commit\" to commit the changes, or \"exit discard\" to discard them\n");
	    return (XORP_ERROR);
	}
	idle_ui();
	_xorpsh.leave_config_mode(callback(this,
					   &RouterCLI::leave_config_done));
	return (XORP_OK);
    }
    if (command_global_name == "exit discard") {
	if (argv.size() > 0) {
	    _cli_client.cli_print("Error: \"exit discard\"  does not take any additional parameters\n");
	    return (XORP_ERROR);
	}
	config_tree()->discard_changes();
	idle_ui();
	_xorpsh.leave_config_mode(callback(this,
					   &RouterCLI::leave_config_done));
	return (XORP_OK);
    }
    if (command_global_name == "top") {
	if (argv.size() > 0) {
	    _cli_client.cli_print("Error: top does not take any parameters\n");
	    return (XORP_ERROR);
	}
	reset_path();
	apply_path_change();
	return (XORP_OK);
    }

    //
    // Commands up and exit are similar, except up doesn't exit
    // configuration-mode if it's executed at the top level
    //
    if (command_global_name == "up") {
	if (argv.size() > 0) {
	    _cli_client.cli_print("Error: up does not take any parameters\n");
	    return (XORP_ERROR);
	}
	if (_path.size() > 0)
	    _path.pop_back();
    }
    if ((command_global_name == "exit") || (command_global_name == "quit")) {
	if (_path.size() == 0) {
	    if (_changes_made) {
		_cli_client.cli_print("Error: There are uncommitted changes\n");
		_cli_client.cli_print("Use \"commit\" to commit the changes, or \"exit discard\" to discard them\n");
		return (XORP_ERROR);
	    }
	    idle_ui();
	    _xorpsh.leave_config_mode(callback(this,
					       &RouterCLI::leave_config_done));
	    return (XORP_OK);
	} else {
	    _path.pop_back();
	}
    }
    apply_path_change();
    return (XORP_OK);
}

int
RouterCLI::edit_func(const string& ,
		     const string& ,
		     uint32_t ,		// cli_session_id
		     const string& command_global_name,
		     const vector<string>& argv)
{
    if (argv.size() == 0) {
	string cmd_name = command_global_name;
	XLOG_ASSERT(cmd_name.substr(0, 5) == "edit ");
	string path = cmd_name.substr(5, cmd_name.size() - 5);
	set_path(path);
	apply_path_change();
	return (XORP_OK);
    } else {
	return (XORP_ERROR);
    }
}

int
RouterCLI::text_entry_func(const string& ,
			   const string& ,
			   uint32_t /* cli_session_id */,
			   const string& command_global_name,
			   const vector<string>& argv)
{
    string path = command_global_name;
    list<string> path_segments;

    while (path.size() > 0) {
	string::size_type ix = path.find(' ');
	if ((ix == string::npos) && (path.size() > 0)) {
	    path_segments.push_back(path);
	    break;
	} else {
	    path_segments.push_back(path.substr(0, ix));
	    path = path.substr(ix + 1, path.size() - ix + 1);
	}
    }

    SlaveConfigTreeNode* ctn = config_tree()->find_node(path_segments);
    const TemplateTreeNode *tag_ttn, *data_ttn;
    bool create_needed = false;
    string nodename;

    if (argv.size() != 0 || (path_segments.back() != "}")) {
	if (ctn == NULL) {
	    create_needed = true;
	    tag_ttn = config_tree()->find_template(path_segments);
	    XLOG_ASSERT(tag_ttn != NULL);
	    nodename = path_segments.back();
	    path_segments.pop_back();
	    ctn = config_tree()->find_node(path_segments);
	} else {
	    tag_ttn = ctn->template_tree_node();
	}

	// If there are no arguments, it must be a void structuring node
	if ((argv.size() == 0) && (tag_ttn->type() != NODE_VOID)) {
	    _cli_client.cli_print("ERROR: Insufficient arguments\n");
	    return (XORP_ERROR);
	}

	XLOG_ASSERT(tag_ttn->is_tag() || (tag_ttn->type() == NODE_VOID));

	if (tag_ttn->is_tag()) {
	    // We're dealing with a tag node, plus value.

	    // Check type of argv[0] is OK
	    list<TemplateTreeNode*>::const_iterator iter;
	    data_ttn = NULL;
	    //
	    // The tag can have multiple children of different types -
	    // take the first that has valid syntax.
	    //
	    // XXX we really ought to check the allow commands here
	    for (iter = tag_ttn->children().begin();
		 iter != tag_ttn->children().end();
		 ++iter) {
		if ((*iter)->type_match(argv[0])) {
		    data_ttn = (*iter);
		    break;
		}
	    }
	    if (data_ttn == NULL) {
		string result = "ERROR: argument \"" + argv[0] +
		    "\" is not a valid " + tag_ttn->segname() + "\n";
		_cli_client.cli_print(result);
		return (XORP_ERROR);
	    }

	    //
	    // Check we're not being asked to create a node that
	    // already exists.
	    //
	    if (create_needed == false) {
		list<ConfigTreeNode*>::const_iterator cti;
		for (cti = ctn->children().begin();
		     cti != ctn->children().end();
		     cti++) {
		    if ((*cti)->segname() == argv[0]) {
			string result = "ERROR: can't create \"" + argv[0] +
			    "\", as it already exists.\n";
			_cli_client.cli_print(result);
			return (XORP_ERROR);
		    }
		}
	    }

	    // Check remaining args are OK
	    if (argv.size() == 2 && argv[1] != "{") {
		string result = "ERROR: \"{\" expected instead of  \""
		    + argv[1] + "\n";
		_cli_client.cli_print(result);
		return (XORP_ERROR);
	    } else if (argv.size() > 2) {
		string result = "ERROR: too many arguments\n";
		_cli_client.cli_print(result);
		return (XORP_ERROR);
	    }
	} else {

	    // We're dealing with a NODE_VOID structuring node.

	    XLOG_ASSERT(tag_ttn->type() == NODE_VOID);
	    if (argv.size() == 1 && argv[0] != "{") {
		string result = "ERROR: \"{\" expected instead of  \""
		    + argv[0] + "\n";
		_cli_client.cli_print(result);
		return (XORP_ERROR);
	    } else if (argv.size() > 1) {
		string result = "ERROR: too many arguments\n";
		_cli_client.cli_print(result);
		return (XORP_ERROR);
	    }
	}

	// Create the parent node, if needed
	string newpath = pathstr();
	SlaveConfigTreeNode* newnode;
	if (create_needed) {
	    path_segments.push_back(nodename);
	    list<string>::const_iterator iter;
	    for (iter = path_segments.begin(); iter != path_segments.end();
		 ++iter) {
		if (newpath.empty())
		    newpath = *iter;
		else
		    newpath += " " + *iter;
	    }
	    ctn = new SlaveConfigTreeNode(path_segments.back(), newpath,
					  tag_ttn, _current_config_node,
					  getuid());
	}

	if (tag_ttn->is_tag()) {
	    // We're dealing with a tag node, plus value.

	    newpath += " " + argv[0];
	    newnode = new SlaveConfigTreeNode(argv[0], newpath, data_ttn,
					      ctn, getuid());

	    // Check that the value was OK
	    string errmsg;
	    if (newnode->check_allowed_value(errmsg) == false) {
		_cli_client.cli_print(errmsg);
		// If the value was bad, remove the nodes we just added
		ctn->remove_child(newnode);
		delete newnode;
		if (create_needed) {
		    _current_config_node->remove_child(ctn);
		    delete ctn;
		}
		return (XORP_ERROR);
	    }

	    if (argv.size() == 1 && _nesting_depth == 0) {
		// Nothing more to enter
		_cli_client.cli_print("OK\n");
		_changes_made = true;
		// Apply path change to add the commit command
		apply_path_change();
		// Add any default children for the new node
		newnode->add_default_children();
		return (XORP_OK);
	    }

	    if (argv.size() > 1) {
		_current_config_node = newnode;
		_path.push_back(path_segments.back());
		_path.push_back(argv[0]);
		_nesting_lengths.push_back(2);
		_nesting_depth++;
	    }
	} else {
	    // We're dealing with a NODE_VOID structuring node.
	    if (argv.size() == 0 && _nesting_depth == 0) {
		// Nothing more to enter
		_cli_client.cli_print("OK\n");
		_changes_made = true;
		// Apply path change to add the commit command
		apply_path_change();
		// Add any default children for the new node
		ctn->add_default_children();
		return (XORP_OK);
	    }

	    XLOG_ASSERT(tag_ttn->type() == NODE_VOID);
	    _current_config_node = ctn;
	    _path.push_back(path_segments.back());
	    _nesting_lengths.push_back(1);
	    _nesting_depth++;
	}
	text_entry_mode();
	add_edit_subtree();
	add_set_subtree();
	CliCommand* com;
	com = _cli_node.cli_command_root()->
	    add_command("}",
			"complete this configuration level",
			callback(this, &RouterCLI::text_entry_func));
	com->set_global_name("}");
	_changes_made = true;
	return (XORP_OK);
    } else {
	XLOG_ASSERT(path_segments.back() == "}");
	XLOG_ASSERT(_nesting_depth > 0);
	for (size_t i = 0; i < _nesting_lengths.back(); i++) {
	    _current_config_node = _current_config_node->parent();
	    XLOG_ASSERT(_current_config_node != NULL);
	    _path.pop_back();
	}
	_nesting_lengths.pop_back();
	_nesting_depth--;
	if (_nesting_depth > 0) {
	    XLOG_ASSERT(!_path.empty());
	    text_entry_mode();
	    add_edit_subtree();
	    add_set_subtree();
	    CliCommand* com;
	    com = _cli_node.cli_command_root()->
		add_command("}",
			    "complete this configuration level",
			    callback(this, &RouterCLI::text_entry_func));
	    com->set_global_name("}");
	    _changes_made = true;
	    return (XORP_OK);
	} else {
	    _cli_client.cli_print("OK.  Use \"commit\" to apply these changes.\n");
	    _changes_made = true;
	    config_tree()->add_default_children();
	    configure_mode();
	    return (XORP_OK);
	}
    }
}

int
RouterCLI::delete_func(const string& ,
		       const string& ,
		       uint32_t ,
		       const string& command_global_name,
		       const vector<string>& argv)
{
    if (argv.size() == 0) {
	string cmd_name = command_global_name;
	XLOG_ASSERT(cmd_name.substr(0, 7) == "delete ");
	string path = cmd_name.substr(7, cmd_name.size() - 7);
	list<string> path_segments;

	while (path.size() > 0) {
	    string::size_type ix = path.find(' ');
	    if ((ix == string::npos) && (path.size() > 0)) {
		path_segments.push_back(path);
		break;
	    } else {
		path_segments.push_back(path.substr(0, ix));
		path = path.substr(ix + 1, path.size() - ix + 1);
	    }
	}

	string result = config_tree()->show_subtree(path_segments);
	_cli_client.cli_print("Deleting: \n");
	_cli_client.cli_print(result + "\n");

	result = config_tree()->mark_subtree_for_deletion(path_segments,
							  getuid());
	_cli_client.cli_print(result + "\n");

	// Regenerate the available command tree without the deleted stuff
	_changes_made = true;
	apply_path_change();
	return (XORP_OK);
    } else {
	return (XORP_ERROR);
    }
}

int
RouterCLI::set_func(const string& ,
		    const string& ,
		    uint32_t ,
		    const string& command_global_name,
		    const vector<string>& argv)
{
    string cmd_name = command_global_name;
    XLOG_ASSERT(cmd_name.substr(0, 4) == "set ");
    string path = cmd_name.substr(4, cmd_name.size() - 4);
    string response = run_set_command(path, argv);
    _cli_client.cli_print(response + "\n");
    apply_path_change();
    return (XORP_OK);
}

int
RouterCLI::immediate_set_func(const string& ,
			      const string& ,
			      uint32_t ,
			      const string& command_global_name,
			      const vector<string>& argv)
{
    string path = command_global_name;
    string response = run_set_command(path, argv);
    if (_nesting_depth == 0) {
	_cli_client.cli_print(response + "\n");
	config_mode_prompt();
    } else {
	if (response != "OK")
	    _cli_client.cli_print(response + "\n");
	text_entry_mode();
	add_edit_subtree();
	add_set_subtree();
	CliCommand* com;
	com = _cli_node.cli_command_root()->
	    add_command("}", "complete this configuration level",
			callback(this, &RouterCLI::text_entry_func));
	com->set_global_name("}");
    }
    return (XORP_OK);
}

string
RouterCLI::run_set_command(const string& path, const vector<string>& argv)
{
    list<string> path_parts;
    path_parts = split(path, ' ');

    ConfigTreeNode* ctn = config_tree()->find_node(path_parts);
    const TemplateTreeNode* ttn;
    bool create_needed = false;
    string nodename;
    if (ctn == NULL) {
	create_needed = true;
	ttn = config_tree()->find_template(path_parts);
	nodename = path_parts.back();
	path_parts.pop_back();
	ctn = config_tree()->find_node(path_parts);
    } else {
	XLOG_ASSERT(ctn->is_leaf());
	ttn = ctn->template_tree_node();
    }

    XLOG_ASSERT(ctn != NULL && ttn != NULL);

    if (argv.size() != 1) {
	string result = "ERROR: \"set " + path + "\" should take one argument of type " + ttn->typestr();
	return result;
    }

    if (ttn->type_match(argv[0]) == false) {
	string result = "ERROR: argument \"" + argv[0] + "\" is not a valid " + ttn->typestr();
	return result;
    }

    if (create_needed) {
	string newpath;
	path_parts.push_back(nodename);
	list<string>::const_iterator iter;
	for (iter = path_parts.begin(); iter != path_parts.end(); ++iter) {
	    if (newpath.empty())
		newpath = *iter;
	    else
		newpath += " " + *iter;
	}
	ConfigTreeNode* newnode = new ConfigTreeNode(path_parts.back(),
						     newpath, ttn,
						     ctn,
						     getuid());
	ctn = newnode;
	ctn->set_value(argv[0], getuid());
    } else {
	ctn->set_value(argv[0], getuid());
    }
    // we don't execute commands until a commit is received
    // string result = config_tree()->execute_node_command(ctn, "%set");
    _changes_made = true;
    string result = "OK";
    return result;
}

int
RouterCLI::commit_func(const string& ,
		       const string& ,
		       uint32_t ,
		       const string& , /* command_global_name */
		       const vector<string>& argv)
{
    if (!argv.empty()) {
	_cli_client.cli_print("ERROR: commit does not take any arguments\n");
	return (XORP_ERROR);
    }

    // Clear the UI
    idle_ui();

    string response;
    XLOG_ASSERT(_changes_made);
    bool success =
	config_tree()->commit_changes(response, _xorpsh,
				      callback(this, &RouterCLI::commit_done));
    if (!success) {
	// _changes_made = false;
	_cli_client.cli_print(response);
	set_prompt("", "XORP> ");
	apply_path_change();
	return (XORP_ERROR);
    }
    // _cli_client.cli_print(response + "\n");
    // apply_path_change();
    return (XORP_OK);
}

void
RouterCLI::idle_ui()
{
    _cli_client.set_is_waiting_for_data(true);
}

void
RouterCLI::reenable_ui()
{
    _cli_client.set_is_waiting_for_data(false);
    _cli_client.post_process_command();
}

void
RouterCLI::commit_done(bool success, string errmsg)
{
    //
    // If we get a failure back here, report it.  Otherwise expect an
    // XRL from the rtrmgr to inform us what really happened as the
    // change was applied.
    //
    if (!success) {
	_cli_client.cli_print("Commit Failed\n");
	_cli_client.cli_print(errmsg);
    } else {
	_changes_made = false;
	_cli_client.cli_print("OK\n");
	_cli_client.cli_print(errmsg);
    }
    _xorpsh.set_mode(XorpShell::MODE_IDLE);
    apply_path_change();
    reenable_ui();
}

int
RouterCLI::show_func(const string& ,
		     const string& ,
		     uint32_t ,		// cli_session_id
		     const string& command_global_name,
		     const vector<string>& argv)
{
    if (argv.size() == 0) {
	string cmd_name = command_global_name;
	XLOG_ASSERT(cmd_name.substr(0, 4) == "show");
	string path;

	if (cmd_name == "show") {
	    // Command "show" with no parameters at the top level
	    path = "";
	} else {
	    path = cmd_name.substr(5, cmd_name.size() - 5);
	}
	list<string> path_segments;
	while (path.size() > 0) {
	    string::size_type ix = path.find(' ');
	    if (ix == string::npos && path.size() > 0) {
		path_segments.push_back(path);
		break;
	    } else {
		path_segments.push_back(path.substr(0, ix));
		path = path.substr(ix + 1, path.size() - ix + 1);
	    }
	}
	string result = config_tree()->show_subtree(path_segments);
	_cli_client.cli_print(result + "\n");
	config_mode_prompt();
	return (XORP_OK);
    } else {
	return (XORP_ERROR);
    }
}

int
RouterCLI::op_mode_func(const string& ,
			const string& ,	// cli_term_name
			uint32_t ,	// cli_session_id
			const string& command_global_name,
			const vector<string>& argv)
{
    string full_command = command_global_name;
    list<string> path_segments;

    path_segments = split(command_global_name, ' ');
    for (size_t i = 0; i < argv.size(); i++) {
	path_segments.push_back(argv[i]);
	full_command += " " + argv[i];
    }

    if (op_cmd_list()->prefix_matches(path_segments)) {
	// Clear the UI
	idle_ui();

	op_cmd_list()->execute(&(_xorpsh.eventloop()), path_segments,
			       callback(this, &RouterCLI::op_mode_cmd_done));
    } else {
	//
	// Try to figure out where the error is, so we can give useful
	// feedback to the user.
	//
	list<string>::const_iterator iter;
	list<string> test_parts;
	string cmd_error;

	_cli_client.cli_print("Error: no matching command:\n");
	for (iter = path_segments.begin(); iter != path_segments.end();
	     ++iter) {
	    if (iter != path_segments.begin())
		cmd_error += " ";
	    test_parts.push_back(*iter);
	    if (op_cmd_list()->prefix_matches(test_parts)) {
		for (size_t i = 0; i < iter->size(); i++) {
		    cmd_error += " ";
		}
	    } else {
		cmd_error += "^";
		break;
	    }
	}
	_cli_client.cli_print(
	    c_format("%s\n%s\n", full_command.c_str(), cmd_error.c_str())
	    );
	return XORP_ERROR;
    }
    return XORP_OK;
}

void
RouterCLI::op_mode_cmd_done(bool success, const string& result)
{
    if (success) {
	// XXX: don't print anything after a command in operational mode
	// _cli_client.cli_print("OK\n");
    } else {
	_cli_client.cli_print("Error:\n");
    }
    if (!result.empty())
	_cli_client.cli_print(result + "\n");

    // Re-enable the CLI
    //  clear_command_set();
    //  add_op_mode_commands(NULL);
    reenable_ui();
}

int
RouterCLI::save_func(const string& ,
		     const string& ,
		     uint32_t ,		// cli_session_id
		     const string& command_global_name,
		     const vector<string>& argv)
{
    if (argv.size() != 1) {
	_cli_client.cli_print("Usage: save <filename>\n");
	return (XORP_ERROR);
    } else {
	XLOG_ASSERT(command_global_name == "save");
	_cli_client.cli_print(c_format("save, filename = %s\n",
				       argv[0].c_str()));
	_xorpsh.save_to_file(argv[0], callback(this, &RouterCLI::save_done));
	idle_ui();
	return (XORP_OK);
    }
}

void
RouterCLI::save_done(const XrlError& e)
{
    debug_msg("in save done\n");
    if (e != XrlError::OKAY()) {
	_cli_client.cli_print("ERROR: Save failed\n");
	if (e == XrlError::COMMAND_FAILED()) {
	    if (e.note() == "AUTH_FAIL") {
		check_for_rtrmgr_restart();
		return;
	    }  else {
		_cli_client.cli_print(e.note());
	    }
	} else {
	    _cli_client.cli_print("Failed to communicate save command to rtrmgr\n");
	    _cli_client.cli_print(c_format("%s\n", e.error_msg()));
	}
	reenable_ui();
	return;
    }
    _cli_client.cli_print("Save done\n");
    reenable_ui();
};

int
RouterCLI::load_func(const string& ,
		     const string& ,
		     uint32_t ,
		     const string& command_global_name,
		     const vector<string>& argv)
{
    if (argv.size() != 1) {
	_cli_client.cli_print("Usage: load <filename>\n");
	return (XORP_ERROR);
    } else {
	XLOG_ASSERT(command_global_name == "load");
#ifdef DEBUG_LOADING
	printf("load, filename = %s\n", argv[0].c_str());
#endif
	_xorpsh.load_from_file(argv[0],
				callback(this, &RouterCLI::load_communicated),
				callback(this, &RouterCLI::load_done));
	idle_ui();
	return (XORP_OK);
    }
}

//
// Method load_communicated() is called when the request for the load has been
// communicated to the rtrmgr, or when this communication has failed.
//
void
RouterCLI::load_communicated(const XrlError& e)
{
    if (e != XrlError::OKAY()) {
	_cli_client.cli_print("ERROR: Load failed.\n");
	if (e == XrlError::COMMAND_FAILED()) {
	    if (e.note() == "AUTH_FAIL") {
		check_for_rtrmgr_restart();
		return;
	    }  else {
		_cli_client.cli_print(e.note());
	    }
	} else {
	    _cli_client.cli_print("Failed to communicate load command to rtrmgr.\n");
	    _cli_client.cli_print(c_format("%s\n", e.error_msg()));
	}
	_xorpsh.set_mode(XorpShell::MODE_IDLE);
	reenable_ui();
	return;
    }
    _xorpsh.set_mode(XorpShell::MODE_LOADING);
    //
    // Don't enable the UI - we'll get called back when the commit has
    // completed.
    //
};

//
// Method load_done() is called when the load has successfully been applied to
// all the router modules, or when something goes wrong during this process.
//
void
RouterCLI::load_done(bool success, string errmsg)
{
    if (!success) {
	_cli_client.cli_print("ERROR: Load failed.\n");
	_cli_client.cli_print(errmsg);
    } else {
	_cli_client.cli_print("Load done.\n");
    }
    _xorpsh.set_mode(XorpShell::MODE_IDLE);
    reenable_ui();
    return;
};

//just to make the code more readable:
SlaveConfigTree*
RouterCLI::config_tree()
{
    return _xorpsh.config_tree();
}

//
// Just to make the code more readable:
//
TemplateTree*
RouterCLI::template_tree()
{
    return _xorpsh.template_tree();
}

//
// Just to make the code more readable:
//
OpCommandList*
RouterCLI::op_cmd_list()
{
    return _xorpsh.op_cmd_list();
}

void
RouterCLI::check_for_rtrmgr_restart()
{
    _xorpsh.get_rtrmgr_pid(callback(this, &RouterCLI::verify_rtrmgr_restart));
}

void
RouterCLI::verify_rtrmgr_restart(const XrlError& e, const uint32_t* pid)
{
    if (e == XrlError::OKAY()) {
	if (_xorpsh.rtrmgr_pid() != *pid) {
	    _cli_client.cli_print("FATAL ERROR.\n");
	    _cli_client.cli_print("The router manager process has restarted.\n");
	    _cli_client.cli_print("Advise logout and login again.\n");
	    reenable_ui();
	    return;
	}

	//
	// It's not clear what happened, but attempt to carry on.
	//
	_cli_client.cli_print("ERROR: authentication failure.\n");
	reenable_ui();
	return;
    } else {
	_cli_client.cli_print("FATAL ERROR.\n");
	_cli_client.cli_print("The router manager process is no longer functioning correctly.\n");
	_cli_client.cli_print("Advise logout and login again, but if login fails the router may need rebooting.\n");
	reenable_ui();
	return;
    }
}
