#include <iostream>

#include <http/request.h>
#include <http/response.h>
#include <module/module.h>
#include <os/pipe.h>
#include <os/socket.h>
#include <strings.h>

void update(const std::string &content_path) {

	// TODO check for result errors
	os::exec(content_path + "/source/shell/update.sh");
}

int main(int argc, char *argv[]) {
	std::string content_path = "";
	if (argc > 1) {
		content_path += argv[1];
	}
	else {
		content_path += ".";
	}
	std::cout << "using directory: " << content_path << "\n";
	module::module_config init_mconf(content_path);
	std::cout << init_mconf.module_list() << "\n";

	// update core modules
	update(content_path);
	std::cout << "update complete, starting server\n";

	// accept http requests
	os::tcp_acceptor webport(8080);
	while (true) {
		os::tcp_stream stream(webport);
		http::request r = http::parse_request("tcp", stream.reads());
		std::vector<std::string> url = io::split(r.location, '/');

		// reload the modules file
		module::module_config mconf(content_path);
		if (url.size() > 0 && mconf.has_module(url[0])) {

			// find and return the resource
			mconf.get_module(url[0], [&stream, &r](module::module &m) {
				std::string result = m.get_page(r.location.c_str());
				stream.writes(http::create_response(result));
			});
		}
		else if (mconf.has_module("home")) {

			// find and return the home page
			mconf.get_module("home", [&stream, &r](module::module &m) {
				std::string result = m.get_page(r.location.c_str());
				stream.writes(http::create_response(result));
			});
		}
		else {

			// show available modules
			std::string result = mconf.module_list();
			stream.writes(http::create_response(result));
		}
	}

	return 0;
}
