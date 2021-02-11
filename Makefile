CC				       = gcc
LINK				       = gcc
CC_OPTS				       = -c -g -Wall -DANSI_COLORS_SUPPORTED
CC_INCS				       = 
LINK_OPTS			       = -g -LGeneralUtilities
LINK_LIBS			       = -lmongoose -llinenoise -lutils -lm -lpthread

TARGET				       = netmon
OBJS				       = $(sort					\
					   main.o				\
					   HTTPServer.o				\
					   WebSocketServer.o			\
					   WebSocketHTTPConfig.o		\
					   WebConnection.o			\
					   NetworkMonitorServer.o		\
					   UserInterfaceServer.o		\
					   Log.o				\
					  )
LIBS				       = 
%.o				      : %.c
					 @echo [CC] $<
					 @$(CC) $(CC_OPTS) $(CC_INCS) $<

$(TARGET)			       : $(OBJS)
					 @echo [LD] $(TARGET)
					 @$(LINK) $(LINK_OPTS) -o $(TARGET) $(OBJS) $(LINK_LIBS) $(LIBS)

include					 depends.mk

.PHONY				       : junkclean
junkclean			       : 
					 rm -rf $(wildcard *~ *-bak)

.PHONY				       : clean
clean				       : junkclean
					 rm -rf $(wildcard $(OBJS) $(TARGET)
