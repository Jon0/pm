#include <iostream>

#include <http/request.h>
#include <http/response.h>
#include <module/module.h>
#include <socket.h>
#include <strings.h>

int main(int argc, char *argv[]) {
	std::string content_path = "";
	if (argc > 1) {
		content_path += argv[1];
	}
	else {
		content_path += ".";
	}
	std::cout << content_path << "\n";


	// load the modules file
	std::string module_file = content_path + "/modules.conf";
	module::module_config mconf(module_file);
	std::cout << mconf.module_list() << "\n";

	mconf.get_module("module1", [](module::module &m) {
		m.call("start");
	});


	os::tcp_acceptor webport(8080);

	while (true) {
		os::tcp_stream stream(webport);

		http::request r = http::parse_request("tcp", stream.reads());
		std::string file_path = content_path + r.location;
		stream.writes(http::create_response(io::read_file(file_path)));

	}

	return 0;
}
