# WeatherSystemP2

## Running the program
After downloading the repository to the desirec directory call 'make' in the parent directory. This will compile both the client and server simultaneously.

## State of Operation
This program allows a number of clients to connect to a server, create and manage accounts, subscribe/unsubscribe to locations, talk to other users, and save those accounts and messages on server exit.
All data is saved with relationship to a user. So a loaded user can login after server shutdown to see the content of their account.