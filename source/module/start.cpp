#include <iostream>

extern "C" {

void start() {
	std::cout << "module started\n";
}

const char *get_page(const char *page_name) {
	return "testing";

	// writing file test
	//std::string file_path = content_path + r.location;
	//std::string file_content = io::read_file(file_path);
	//stream.writes(http::create_response(file_content));
}

}
