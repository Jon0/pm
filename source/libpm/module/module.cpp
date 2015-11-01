#include <iostream>

#include <dlfcn.h>

#include "../strings.h"
#include "module.h"

namespace module {

module::module(const std::string &libpath)
	:
	lib_handle(dlopen(libpath.c_str(), RTLD_LAZY)) {

	if (open()) {
		std::cout << "loaded " << libpath << "\n";
	}
	else {
		std::cerr << "unable to load " << libpath << "\n";
	}
}


module::~module() {
	if (open()) {
		dlclose(lib_handle);
	}
}


bool module::open() const {
	return lib_handle;
}


void module::call(const std::string &fname) const {
	void (*fn)();
	char *error;

	fn = reinterpret_cast<void (*)()>(dlsym(lib_handle, fname.c_str()));
	if ((error = dlerror()) != NULL) {
		std::cerr << "error " << fname << ": " << error << "\n";
	}
	else {
		fn();
	}
}


const char *module::get_page(const char *page_name) const {
	const char *(*fn)(const char *);
	char *error;

	fn = reinterpret_cast<const char *(*)(const char *)>(dlsym(lib_handle, "get_page"));
	if ((error = dlerror()) != NULL) {
		std::cerr << "error calling get_page: " << error << "\n";
		return "not found";
	}
	else {
		return fn(page_name);
	}
}


module_config::module_config(const std::string &confpath) {
	std::string file_map = io::read_file(confpath);
	std::vector<std::string> mappings = io::split(file_map, '\n');

	for (auto &m : mappings) {
		std::vector<std::string> line = io::split(m, ' ');
		if (line.size() == 2) {
			mod_paths.insert(std::make_pair(line[0], line[1]));
		}
	}
}


bool module_config::has_module(const std::string &name) const {
	return (mod_paths.count(name) > 0);
}


std::string module_config::module_list() const {
	std::string result = "";
	for (auto &m : mod_paths) {
		result += m.first + " -> " + m.second + "\n";
	}
	return result;
}


void module_config::get_module(const std::string &name, std::function<void(module &)> callback) const {
	if (mod_paths.count(name) > 0) {
		module used_module(mod_paths.at(name));
		if (used_module.open()) {
			callback(used_module);
		}
	}
}


}
