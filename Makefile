CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14  -Wno-deprecated-declarations

# RM= /bin/rm -f

CD = cd ./Backend/

all: testcomment PutHTML  #APIcalls 

commentEntry.o: commentEntry.cpp commentEntry.h
	$(CD) && $(CC) -c $(CFLAGS) commentEntry.cpp

commentDB.o: commentDB.cpp #commentDB.h
	$(CD) && $(CC) -c $(CFLAGS) -I/usr/include/cppconn commentDB.cpp

testcomment.o: testcomment.cpp commentEntry.h #commentDB.h
	$(CD) && $(CC) -c $(CFLAGS) testcomment.cpp

testcomment: testcomment.o commentDB.o commentEntry.o
	$(CD) && $(CC) testcomment.o commentDB.o commentEntry.o -L/usr/lib -o testcomment -L/usr/local/lib -lmariadbcpp $(CXXFLAGS)

# # testcomment: testcomment.o commentDB.o commentEntry.o
# # 	$(CD) && $(CC) testcomment.o commentDB.o commentEntry.o -L/usr/lib -o testcomment -L/usr/local/lib -lmariadbcpp

# APIcalls.o: APIcalls.cpp httplib.h
# 	$(CD) && $(CC) -c $(CFLAGS) APIcalls.cpp

# APIcalls: APIcalls.o commentDB.o commentEntry.o 
# 	$(CD) && $(CC) APIcalls.o commentDB.o commentEntry.o -o APIcalls -L/usr/local/lib -lmariadbcpp

PutHTML:
	cp APIcalls.html /var/www/html/commentCpp/
	cp APIcalls.js /var/www/html/commentCpp/
	cp APIcalls.css /var/www/html/commentCpp/


	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/commentCpp

clean:
	rm -f *.o  APIcalls testcomment
