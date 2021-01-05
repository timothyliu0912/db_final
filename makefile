db:
	gcc db.c graph.c load.c predict.c query.c save.c update.c -lcrypto -lm
load:
	gcc graph.c load.c predict.c query.c save.c test_load.c update.c -lcrypto -lm
