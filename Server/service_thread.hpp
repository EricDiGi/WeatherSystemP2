#ifndef SERVICE_THREAD_HPP
#define SERVICE_THREAD_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <mutex>

#include <fstream>
#include <sstream>

#include "action_handler.hpp"
#include "glob.hpp"

#define NUM_THREADS 4
#define PORT 60049
#define BUFFER_LEN 1280

std::vector<Location> locats;
std::mutex lock;

struct new_user{
	int id;
	int socket;
};

int active_threads = 0;

void serve(struct new_user* user);
void build();

void serve(struct new_user* user){
	lock.lock();
	active_threads++;
	lock.unlock();

	struct new_user* nu = user;
	int id_ = nu->id;
	int sock = nu->socket;
    
	char buffer[BUFFER_LEN] = {0};

	while(1){
		if(read(sock, buffer, BUFFER_LEN) > 0){
			std::string packet = Handler(buffer).act();
			printf("THREAD: %d\n", id_);
			write(sock, (char*)packet.c_str(), (int)packet.size());
			printf("---------- MESSAGE SENT -----------\n");
		}
	}

	close(sock);
	
	lock.lock();
	active_threads--;
	lock.unlock();

	std::terminate();
}


void build(){
	std::stringstream dbuf;

	std::ifstream fs("BASE/locations.dat");
	if(fs){
		dbuf << fs.rdbuf();
		fs.close();
	}
	else{
        perror("Unable to load locations");
        exit(EXIT_FAILURE);
    }

	std::string tmp;
	while(getline(dbuf,tmp,'\n')){
		locats.push_back(Location(tmp));
	}
}

#endif