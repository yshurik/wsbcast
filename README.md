# wsbcast

Web Sockets simple server: it broadcasts message from one client to all other connected.
The server can be used as standard component in the infrastructure to make web applications
to know about each other by making default web socket connection to wsbcast server and then listen
messages from all other web applications.

## Contributing

wsbcast is an open source project and always ready for more contributions.

## Getting the Code

To get a local copy of the current code, clone it using git:

    $ git clone git@github.com:yshurik/wsbcast.git
    $ cd wsbcast
    
Next, open wsbcast.pro file in Qt Creator and complete the build or use qmake utility
to generate Makefiles and build the wsbcast with make command:

    $ qmake wsbcast.pro
    $ make release
    
## Usage 

wsbcast is simple server application. There are command line arguments to specify port and switch on debug mode.
embedded help command line arg:

    $ wsbcast --help
    Usage: /Users/alex/w/wsbcast/wsbcastd [options]
    wsbcast: Web Socket broadcast server, from one client to all other.

    Options:
      -h, --help         Displays this help.
      -d, --debug        Debug output [default: off].
      -p, --port <port>  Port for wsbcast [default: 8086].

    $ wsbcast -d --port 8080
    
