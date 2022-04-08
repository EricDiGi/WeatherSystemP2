#include "service_thread.hpp"
#include <cstdlib>
#include <csignal>

int main(int argc, char** argv){

	// Allow me to save data before exiting
	auto ex_s = [] (int i) {if(do_save_on_exit) exit(i);};
	std::atexit(exit_handle);
	signal(SIGINT, ex_s);
    signal(SIGABRT, ex_s);
    signal(SIGTERM, ex_s);
    signal(SIGTSTP, ex_s);

	build();

	int server_fd, new_socket;
	struct sockaddr_in address;
	int address_length = sizeof(address);

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("Socket Error");
		do_save_on_exit = false;
		exit(EXIT_FAILURE);
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
	memset(address.sin_zero,'\0',sizeof(address.sin_zero));
	
	if(bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0){
		perror("Could not bind");
		do_save_on_exit = false;
		exit(EXIT_FAILURE);
	}
	
	if(listen(server_fd,10) < 0){
		perror("Could not listen");
		do_save_on_exit = false;
		exit(EXIT_FAILURE);
	}

	std::thread threads[NUM_THREADS];

	while(1){
		if(active_threads < NUM_THREADS){
			printf(">>> Waiting for new connection\n");
			if((new_socket = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&address_length))<0){
				perror("Could not Accept Packet");
				exit(EXIT_FAILURE);
			}

			struct new_user* nu = (struct new_user*)malloc(sizeof(struct new_user));
			nu->id = active_threads;
			nu->socket = new_socket;
			threads[active_threads] = std::thread(serve, nu);
		}
	}
	return EXIT_SUCCESS;
}