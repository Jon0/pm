#include <iostream>

#include <strings.h>

#include "interface.h"

std::string conf_path;
std::string page_out;

void set_conf_path(const char *confpath) {
	conf_path = confpath;

	// load install configuration
	std::cout << io::read_file(conf_path + "/install.conf");
}

const char *get_page(const char *page_name) {
	std::string page_path = conf_path + "/source/install/install.html";
	std::cout << "opening " << page_path << "\n";
	page_out = io::read_file(page_path);
	return page_out.c_str();
}
