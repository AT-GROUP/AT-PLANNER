
#include <iostream>
#include <direct.h>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Building project..." << std::endl;

	std::string path(argv[1]), prj_path(argv[2]);
	
	std::string bin_path = path + "/bin";

	cout << "Creating dir " << bin_path << std::endl;
	_mkdir(bin_path.c_str());

	std::ofstream res_file(bin_path + "/es.exe");
	res_file << "XXXXXX";

	return 0;
}
