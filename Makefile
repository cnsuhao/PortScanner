BOOST_INC_PATH := /usr/local/boost_1_56_0
BOOST_LIB_PATH := /usr/local/boost_1_56_0/stage/lib

FILES := main \
		 ConnectScanner \
		 ConsoleOutputer \
		 DataStructures \
		 IOutputer \
		 IScanner
CPPS := $(foreach n,$(FILES),$(n).cpp)
HEADERS := $(foreach n,$(FILES),$(n).h)
OBJS := $(foreach n,$(FILES),$(n).o)
libs := 	-lboost_system \
			-lboost_date_time \
			-lboost_program_options \
			-lboost_thread \
			-lpthread \
			

TARGET := PortScanner
C11 := c++11

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) -std=$(C11) \
		-L $(BOOST_LIB_PATH) \
		$(libs) \
		-static

$(OBJS): %.o:%.cpp
	g++ -c $< -std=$(C11) \
	-I $(BOOST_INC_PATH)

.PHONY: clean
clean:
	rm $(OBJS) $(TARGET)

