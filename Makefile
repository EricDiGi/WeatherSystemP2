
all: client server

clean:
	$(MAKE) -C Server clean
	$(MAKE) -C Client clean

client:
	$(MAKE) -C Client clean
	$(MAKE) -C Client

server:
	$(MAKE) -C Server clean
	$(MAKE) -C Server