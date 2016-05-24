#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

using namespace std;

int main ( int argc, char* argv[] )
{
  try
    {

      ClientSocket client_socket ( "localhost", 1314 );

      string reply;

      try
	{
	  client_socket << "Test message.";
	  client_socket >> reply;
	}
      catch ( SocketException& ) {}

      cout << "We received this response from the server:\n\"" << reply << "\"\n";;

    }
  catch ( SocketException& e )
    {
      cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
