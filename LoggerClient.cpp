#include <iostream>
#include "gen-cpp/Logger.h" 
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

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

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace LoggerCpp;

int main(int argc, char **argv)
{
    char logfile[]="logfile.log";
    std::string line;

    std::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    LoggerClient client(protocol);
    try {
        transport->open();

        client.timestamp(logfile);
        std::cout << "Logged timestamp to log file" << std::endl;

        client.write_log(logfile, "This is a message that I am writing to the log");
        client.timestamp(logfile);

        client.get_last_log_entry(line, logfile);
        std::cout << "Last line of the log file is: " << line << std::endl;
        std::cout << "Size of log file is: " << client.get_log_size(logfile) << " bytes" << std::endl;

        transport->close();
    }
    catch (TTransportException e) {
        std::cout << "Error starting client" << std::endl;
    }
    catch (LoggerException e) {
        std::cout << e.error_description << std::endl;
    }
    return 0;
}
