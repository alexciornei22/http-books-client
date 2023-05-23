# Books API HTTP Client, C++

## Program flow
The program loop reads input from the console, using a command factory to initialize
the right command object to be executed. Based on the command, the program uses the
overloaded `promptInput()` method to ask the user for more input, passing an `InputValidator`
object to the method if necessary. An `HTTPRequest` object is instantiated based on the
action's corresponding method, path, and JSON content if necessary, which is then sent to
the server.

The [nlohmann/json](https://github.com/nlohmann/json) library was chosen to help
with JSON data handling for its trivial integration (a single *.hpp* included header file)
and intuitive syntax (looping through JSON arrays like a normal C++ array using an 
enhanced for, accessing JSON object properties like an associative array: `object["member"]`).

The Client's `sendToServer()` method responds with a `HTTPResponse` object which
is then interpreted for errors based on the status code, displaying a success or error message
accordingly. A new socket is opened before sending a new request and then closed after receiving
the response from the server. The cookies and JWT for the library access are stored in
the `SessionData` object which is modeled by the Singleton pattern, making them available globally.

## Project Structure
- [/src](/src): contains the class implementations
- [/include](/include): contains the header files with the class declarations and the JSON library
- [main.cpp](/src/main.cpp): the main program loop, exits the loop if it catches an `exited()`
exception, thrown in the exit command
- [ConsoleCommands.cpp](/src/ConsoleCommands.cpp): the command objects which handle the various
actions, constructing and sending HTTP requests and displaying responses from the server
- [HTTPRequest.cpp](/src/HTTPRequest.cpp): request object which exposes a method to easily construct
the request string buffer to be sent to the server
- [HTTPResponse.cpp](/src/HTTPResponse.cpp): response object which is automatically constructed from
a response string buffer, encapsulating the response status code/text and data
- [HTTPClient.cpp](/src/HTTPClient.cpp): contains the methods for sending an HTTP request and receiving
an HTTP response with TCP sockets
- [InputValidator.cpp](/src/InputValidator.cpp): validator classes for user input validation, such as
`NoSpacesValidator` or `NumberValidator`
- [SessionData.cpp](/src/SessionData.cpp): the session data singleton, fetched whenever needed
