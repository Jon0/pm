#include <iostream>

#include "interface.h"

std::string conf_path;

void set_conf_path(const char *confpath) {
	conf_path = confpath;
}

const char *get_page(const char *page_name) {
	return conf_path.c_str();

	// writing file test
	//std::string file_path = content_path + r.location;
	//std::string file_content = io::read_file(file_path);
	//stream.writes(http::create_response(file_content));
}
