main: main.c
	cc main.c gameLogic.c setup_inicio.c grafo_la.c fila_enc.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
