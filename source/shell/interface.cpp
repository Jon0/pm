#include <iostream>

#include <os/pipe.h>
#include <strings.h>

#include "interface.h"

std::string conf_path;
std::string page_out;

void set_conf_path(const char *confpath) {
	conf_path = confpath;
}

const char *get_page(const char *page_name) {
	std::string result = os::exec(conf_path + "/source/shell/update.sh");
	std::string page_path = conf_path + "/source/shell/shell.html";
	page_out = io::read_file(page_path) + "<br>" + result;
	return page_out.c_str();
}
