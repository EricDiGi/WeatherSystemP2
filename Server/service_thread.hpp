#ifndef SERVICE_THREAD_HPP
#define SERVICE_THREAD_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <vector>
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
std::vector<User> accs;
std::vector<Message> msgs;

std::mutex lock;

struct new_user{
	int id;
	int socket;
};

int active_threads = 0;
bool do_save_on_exit = true;

void serve(struct new_user* user);
void build();
void exit_handle();
void save_point();
void false_exit(std::string err);

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
		memset(buffer,0,BUFFER_LEN);
	}

	close(sock);
	
	lock.lock();
	active_threads--;
	lock.unlock();

	std::terminate();
}


void false_exit(std::string err){
	do_save_on_exit = false;
	perror((char*)err.c_str());
	exit(EXIT_FAILURE);
}


void build(){
	std::stringstream dbuf;
	std::stringstream dbufa;
	std::stringstream dbufb;
	std::string tmp;
	std::ifstream fs;

	std::cout << "\n >> BUILDING <<\n";
	std::cout << "LOCATIONS - ";
	fs.open("BASE/locations.dat");
	if(fs.is_open() && fs.good()){
		dbuf << fs.rdbuf();
		fs.close();
	}
	else false_exit("Unable to load locations");
	while(getline(dbuf,tmp,'\n')){
		std::cout << tmp << "\t";
		locats.push_back(Location(tmp));
	}
	std::cout << "OK\nMESSAGES - ";

	tmp = "";
	std::ifstream fsa;
	fsa.open("BASE/messages.dat");
	if(fsa.is_open() && fsa.good()){
		dbufa << fsa.rdbuf();
		fsa.close();
	} else false_exit("Unable to load messages");
	while(getline(dbufa,tmp,'\n')){
		std::cout << "new msg\t";
		int delim_l = tmp.find((char)30);
		Message m = Message();
		std::stringstream sstmp;
		sstmp << tmp.substr(0,delim_l);
		sstmp >> m.id;
		m.content = tmp.substr(delim_l+1,tmp.length());
		msgs.push_back(m);
	}

	std::cout << "OK\nUSERS - ";
	
	std::ifstream fsb;
	tmp = "";
	fsb.open("BASE/users.dat");
	if(fsb.is_open() && fsb.good()){
		dbufb << fsb.rdbuf();
		fsb.close();
	} else false_exit("Unable to load users");
	while(getline(dbufb,tmp,'\n')){
		std::cout << tmp << std::endl;
		User u = User(tmp);
		std::cout << "N: " << u << std::endl;
		accs.push_back(u);
	}

	std::cout << "OK\n\n";
}

void exit_handle(){
	if(do_save_on_exit){
		save_point();
		std::cout << ">>> EXIT - SAVING" << std::endl;
	}
	else std::cout << ">>> EXIT - NO SAVE" << std::endl;
}

void save_point(){
	std::fstream of;
	of.open("BASE/users.dat", std::ios::out|std::ios::trunc);
	if(of){
		for(auto &it:accs)
			of << it << std::endl;
		of.close();
	}
	of.open("BASE/messages.dat", std::ios::out|std::ios::trunc);
	if(of){
		for(auto &it:msgs)
			of << it << std::endl;
		of.close();
	}
}

#endif