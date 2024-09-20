SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

CFLAGS = -Wall -Wextra -Werror
SRC_S = utils.c server.c
SRC_C = utils.c client.c
SRC_SB = utils.c server_bonus.c
SRC_CB = utils.c client_bonus.c
OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)
OBJ_SB = $(SRC_SB:.c=.o)
OBJ_CB = $(SRC_CB:.c=.o)

all : $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_S)
	$(CC) $(CFLAGS) $(OBJ_S) -o $(SERVER)

$(CLIENT): $(OBJ_C)
	$(CC) $(CFLAGS) $(OBJ_C) -o $(CLIENT)

bonus : $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(OBJ_SB)
	$(CC) $(CFLAGS) $(OBJ_SB) -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(OBJ_CB)
	$(CC) $(CFLAGS) $(OBJ_CB) -o $(CLIENT_BONUS)

clean:
	rm -f $(OBJ_S) $(OBJ_C) $(OBJ_SB) $(OBJ_CB) 

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all