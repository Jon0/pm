#include <iostream>

// example of functions to export
extern "C" {

void set_conf_path(const char *confpath);

const char *get_page(const char *page_name);

}
