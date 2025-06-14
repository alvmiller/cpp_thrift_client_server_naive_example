#include "gen-cpp/Logger.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

/*
apache  thrift:
https://thrift.apache.org/download
https://thrift.apache.org/docs/BuildingFromSource
https://thrift.apache.org/docs/install/
https://thrift.apache.org/tutorial/cpp.html
https://thrift.apache.org/lib/cpp.html
https://github.com/apache/thrift
https://github.com/apache/thrift/tree/master/contrib/transport-sample
https://thrift-tutorial.readthedocs.io/en/latest/intro.html
https://medium.com/@tahir.rauf/building-your-first-service-with-apache-thrift-a-practical-tutorial-1e591c4af8d9
https://vorbrodt.blog/2019/03/10/thrift-or-how-to-rpc/
https://github.com/cdmeister/Basic-Thrift-Tutorial/tree/master
https://www.avabodh.com/thrift/client_server.html
https://d3s.mff.cuni.cz/files/teaching/nswi080/lectures/notes/ch02s20.html
https://diwakergupta.github.io/thrift-missing-guide/
https://thrift-tutorial.readthedocs.io/en/latest/installation.html
https://www.tutorialspoint.com/apache-thrift/apache-thrift-installation.htm
https://thrift.apache.org/docs/install/debian.html
https://medium.com/@etehvinayak/steps-to-install-apache-thrift-on-ubuntu-14-04-42378b339f0f


sudo apt update
sudo apt install -y build-essential autoconf automake libtool pkg-config
sudo apt install default-jre
sudo apt install default-jdk
sudo apt-get install libboost-dev libboost-test-dev libboost-program-options-dev libboost-filesystem-dev libboost-thread-dev libevent-dev automake libtool flex bison pkg-config g++ libssl-dev
http://thrift.apache.org/download
git clone https://github.com/apache/thrift.git
./bootstrap.sh
./configure
make
make install
thrift -version

sudo apt install thrift-compiler

thrift --gen cpp LoggerService.thrift
cd gen-cpp/
cmake ..
make
./LoggerServer
./LoggerClient

gen-cpp/Logger_server.skeleton.cpp -> LoggerServer
gen-cpp/Logger_client.skeleton.cpp -> LoggerClient
*/

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::LoggerCpp;

class LoggerHandler : virtual public LoggerIf {
public:
	LoggerHandler() {
	}
	void timestamp(const std::string& filename) {
		printf("timestamp\n");
	}
	void get_last_log_entry(std::string& _return, const std::string& filename) {
		printf("get_last_log_entry\n");
		printf("filename = %s\n", filename.c_str());
	}
	void write_log(const std::string& filename, const std::string& message) {
		printf("write_log\n");
		printf("filename = %s, message = %s\n", filename.c_str(), message.c_str());
	}
	int32_t get_log_size(const std::string& filename) {
		printf("get_log_size\n");
		return 0;
	}
};

int main(int argc, char **argv) {
	int port = 9090;
	::std::shared_ptr<LoggerHandler> handler(new LoggerHandler());
	::std::shared_ptr<TProcessor> processor(new LoggerProcessor(handler));
	::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	server.serve();
	return 0;
}
