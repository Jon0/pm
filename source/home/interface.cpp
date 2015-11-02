#include <iostream>

#include <module/module.h>
#include <pipe.h>
#include <strings.h>

#include "interface.h"

std::string conf_path;
std::string hostname;
std::string module_info;
std::string page_out;

//TODO use init function
void init(const module::module_config &mconf) {

}

void set_conf_path(const char *confpath) {
	conf_path = confpath;
	hostname = os::exec("hostname");

	// workaround until init works
	module::module_config mconf(confpath);
	module_info = "";
	for (auto &m : mconf.module_map()) {
		module_info += "<a href=\"" + m.first + "/\">" + m.first + "</a><br>";
	}
}

const char *get_page(const char *page_name) {
	std::string page_path = conf_path + "/source/home/index.html";
	std::cout << "opening " << page_path << "\n";
	page_out = io::read_file(page_path) + hostname + "<br>modules:<br>" + module_info;
	return page_out.c_str();
}
