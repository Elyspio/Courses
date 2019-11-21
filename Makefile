CC = gcc

CC_FLAGS = -Wall -pedantic

SERVER = server
CLIENT = client

SRC_FOLDER = src
DIST_FOLDER = dist
BUILD_FOLDER = build

COMMON = common
TEST = test


SERVER_SRC = server.c
CLIENT_SRC = client.c
TEST_SRC = test.c

SERVER_EXEC = server.app
CLIENT_EXEC = client.app
TEST_EXEC = test.app

help:
	@echo Error: no command provided.
	@echo See ./INSTALL to get started.

pkg: 
	@ echo "Packaging the project to groupe_PAUTRAT_GUICHARD.zip" 
	@ /bin/time --format="Done in %es" zip -9 -ll groupe_PAUTRAT_GUICHARD.zip  -r ./$(SRC_FOLDER) ./README.md ./CONTRIBUTORS.md ./Makefile ./INSTALL.md  > /dev/null


env:
	@mkdir -p $(SRC_FOLDER)/$(SERVER) $(SRC_FOLDER)/$(CLIENT) $(SRC_FOLDER)/$(COMMON)
	@mkdir -p $(BUILD_FOLDER)/$(SERVER) $(BUILD_FOLDER)/$(CLIENT) $(BUILD_FOLDER)/$(TEST)/=
	@mkdir -p $(DIST_FOLDER)

compile_common: env
	@ mkdir -p $(BUILD_FOLDER)/$(COMMON)
	@echo "Compiling common files"
	@ $(CC) $(CC_FLAGS) -c  `find $(SRC_FOLDER)/$(COMMON) -type f -name "*.c"`
	@ mv *.o $(BUILD_FOLDER)/$(COMMON)

server: compile_common
	@ $(CC) $(CC_FLAGS) -c  `find $(SRC_FOLDER)/$(SERVER) -type f -name "*.c"`
	@ mv *.o $(BUILD_FOLDER)/$(SERVER)
	@ $(CC) -o $(DIST_FOLDER)/$(SERVER_EXEC)  $(BUILD_FOLDER)/$(SERVER)/*.o $(BUILD_FOLDER)/$(COMMON)/*.o
	@ echo "Server is available at $(DIST_FOLDER)/$(SERVER_EXEC)"

client: compile_common
	@ $(CC) $(CC_FLAGS) -c  `find $(SRC_FOLDER)/$(CLIENT) -type f -name "*.c"`
	@ mv *.o $(BUILD_FOLDER)/$(CLIENT)
	@ $(CC) -o $(DIST_FOLDER)/$(CLIENT_EXEC)  $(BUILD_FOLDER)/$(CLIENT)/*.o $(BUILD_FOLDER)/$(COMMON)/*.o
	@ echo "Client is available at $(DIST_FOLDER)/$(CLIENT_EXEC)"

test: compile_common env_test
	@ $(CC) $(CC_FLAGS) -c  `find $(SRC_FOLDER)/$(TEST) -type f -name "*.c"`
	@ mv *.o $(BUILD_FOLDER)/$(TEST)
	@ $(CC) -o $(DIST_FOLDER)/$(TEST_EXEC)  $(BUILD_FOLDER)/$(TEST)/*.o $(BUILD_FOLDER)/$(COMMON)/*.o
	@ echo "Test is available at $(DIST_FOLDER)/$(TEST_EXEC)"

task: client server test


env_test:
	@ mkdir -p $(SRC_FOLDER)/$(TEST)
	@ mkdir -p $(BUILD_FOLDER)/$(TEST)
	@ mkdir -p $(DIST_FOLDER)/

watch_test:
	@ ./tmux/test.bash
