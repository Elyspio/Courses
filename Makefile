CC ?= gcc

SERVER = server
CLIENT = client
COMMON_FOLDER = common

TASK ?= 1

SRC_FOLDER = src
DIST_FOLDER = dist
BUILD_FOLDER = build


SERVER_SRC = server.c
CLIENT_SRC = client.c

SERVER_EXEC = server
CLIENT_EXEC = client


help:
	@echo Error: no command provided.
	@echo See ./INSTALL to get started.

pkg: 
	@ echo "Packaging the project to groupe_PAUTRAT_GUICHARD.zip" 
	@ /bin/time --format="Done in %es" zip -9 -ll groupe_PAUTRAT_GUICHARD.zip  -r ./$(SRC_FOLDER) ./README.md ./CONTRIBUTORS.md ./Makefile ./INSTALL.md  > /dev/null


env:
	@mkdir -p $(SRC_FOLDER)/$(SERVER) $(SRC_FOLDER)/$(CLIENT) $(SRC_FOLDER)/$(COMMON_FOLDER)
	@mkdir -p $(BUILD_FOLDER)/$(SERVER) $(BUILD_FOLDER)/$(CLIENT)
	@mkdir -p $(DIST_FOLDER)/$(TASK)
	@echo "Done"

build:
	@echo "Compile task $(TASK)"

	@ $(CC) -c `find src -type f -name "*.c" ! -name "$(SERVER_SRC)"`
	@ mv *.o $(BUILD_FOLDER)/$(CLIENT)
	@ $(CC) -o $(DIST_FOLDER)/$(CLIENT_EXEC)  $(BUILD_FOLDER)/$(CLIENT)/*.o

	@echo "Client is at $(DIST_FOLDER)/$(CLIENT_EXEC)"

	@$(CC) -c  `find src -type f -name "*.c" ! -name "$(CLIENT_SRC)"`
	@mv *.o $(BUILD_FOLDER)/$(SERVER)
	@$(CC) -o $(DIST_FOLDER)/$(SERVER_EXEC)  $(BUILD_FOLDER)/$(SERVER)/*.o

	@echo "Server is at $(DIST_FOLDER)/$(SERVER_EXEC)"
