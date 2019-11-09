CC = gcc

CC_FLAGS = -Wall -pedantic

SERVER = server
CLIENT = client
COMMON_FOLDER = common

SRC_FOLDER = src
TEST_FOLDER = test
DIST_FOLDER = dist
BUILD_FOLDER = build


SERVER_SRC = server.c
CLIENT_SRC = client.c

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
	@mkdir -p $(SRC_FOLDER)/$(SERVER) $(SRC_FOLDER)/$(CLIENT) $(SRC_FOLDER)/$(COMMON_FOLDER)
	@mkdir -p $(BUILD_FOLDER)/$(SERVER) $(BUILD_FOLDER)/$(CLIENT) $(BUILD_FOLDER)/$(TEST_FOLDER)/
	@mkdir -p $(DIST_FOLDER) $(DIST_FOLDER)/$(TEST_FOLDER) 
	@echo "Done"

task:
	@echo "Compiling task"

	@ $(CC) $(CC_FLAGS) -c `find src -type f -name "*.c" ! -name "$(SERVER_SRC)"`
	@ mv *.o $(BUILD_FOLDER)/$(CLIENT)
	@ $(CC) -o $(DIST_FOLDER)/$(CLIENT_EXEC)  $(BUILD_FOLDER)/$(CLIENT)/*.o

	@echo "Client is at $(DIST_FOLDER)/$(CLIENT_EXEC)"

	@$(CC) $(CC_FLAGS) -c  `find src -type f -name "*.c" ! -name "$(CLIENT_SRC)"`
	@mv *.o $(BUILD_FOLDER)/$(SERVER)
	@$(CC) -o $(DIST_FOLDER)/$(SERVER_EXEC)  $(BUILD_FOLDER)/$(SERVER)/*.o

	@echo "Server is at $(DIST_FOLDER)/$(SERVER_EXEC)"


env_test:
	@ mkdir -p $(SRC_FOLDER)/$(TEST_FOLDER)
	@ mkdir -p $(BUILD_FOLDER)/$(TEST_FOLDER)
	@ mkdir -p $(DIST_FOLDER)/$(TEST_FOLDER)

test:
	@ echo "Compile test"
	 $(CC) $(CC_FLAGS) -c $(SRC_FOLDER)/$(TEST_FOLDER)/*.c
	 mv *.o $(BUILD_FOLDER)/$(TEST_FOLDER)
	 $(CC) -o $(DIST_FOLDER)/$(TEST_FOLDER)/$(TEST_EXEC) $(BUILD_FOLDER)/$(TEST_FOLDER)/*.o
	@ echo test at $(DIST_FOLDER)/$(TEST_FOLDER)/$(TEST_EXEC)
clean: 
	@ rm -rdf $(DIST_FOLDER)
	@ rm -rdf $(BUILD_FOLDER)

watch:
	@ ./tmux/test.bash
