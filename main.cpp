#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
    try {
        boost::asio::io_context io_context;

        // Resolver to get endpoints for the server
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("www.example.com", "80");

        // Create and connect the socket
        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        // Create and send an HTTP GET request
        std::string request =
            "GET / HTTP/1.1\r\n"
            "Host: www.example.com\r\n"
            "Connection: close\r\n\r\n";

        boost::asio::write(socket, boost::asio::buffer(request));

        // Read and print the response
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Print the response headers
        std::istream response_stream(&response);
        std::string header;
        while (std::getline(response_stream, header) && header != "\r") {
            std::cout << header << std::endl;
        }
        std::cout << std::endl;

        // Print the response body
        std::stringstream response_body;
        response_body << response_stream.rdbuf();
        std::cout << response_body.str() << std::endl;

        // Read remaining response body
        boost::system::error_code error;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {
            std::cout << &response;
        }

        if (error != boost::asio::error::eof) {
            throw boost::system::system_error(error);
        }

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
