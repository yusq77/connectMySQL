CC=gcc

SRCS=update.c\
	log.c

OBJS=$(SRCS:.c=.o)

EXEC=DBUpdate

start:$(OBJS)
	$(CC) -o $(EXEC) $(OBJS) -L../../lib64  -lhac_sqldual  -lsqlite3 -lmysqlclient  -lxml2 -lxmlconfig -lunionencrypt -lunionlog
#	$(CC) -o $(EXEC) $(OBJS)  -L../../lib64 -lmysqlclient

.cpp.o:
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJS) $(EXEC) *.log
