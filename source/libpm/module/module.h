#pragma once

#include <functional>
#include <string>
#include <unordered_map>

namespace module {


class module {
public:
	module(const std::string &libpath);
	~module();

	bool open() const;

	void call(const std::string &fname) const;

	/**
	 * io testing
	 */
	const char *get_page(const char *page_name) const;

private:
	void *lib_handle;

};


class module_config {
public:
	module_config(const std::string &confpath);

	bool has_module(const std::string &name) const;

	std::string module_list() const;

	void get_module(const std::string &name, std::function<void(module &)> callback) const;

private:
	std::unordered_map<std::string, std::string> mod_paths;

};


}
