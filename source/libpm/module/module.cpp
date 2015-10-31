#include <iostream>

#include <dlfcn.h>

#include "../strings.h"
#include "module.h"

namespace module {

module::module(const std::string &libpath)
	:
	lib_handle(dlopen(libpath.c_str(), RTLD_LAZY)) {

	if (!lib_handle) {
		std::cerr << "unable to load " << libpath << "\n";
	}
	else {
		std::cout << "loaded " << libpath << "\n";
	}
}


module::~module() {
	dlclose(lib_handle);
}


void module::call(const std::string &fname) const {
	void (*fn)();
	char *error;

	fn = reinterpret_cast<void (*)()>(dlsym(lib_handle, fname.c_str()));
	if ((error = dlerror()) != NULL) {
		std::cerr << "error " << fname << "\n";
	}
	else {
		fn();
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
		callback(used_module);
	}
}


}
