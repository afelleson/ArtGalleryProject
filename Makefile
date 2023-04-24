CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14  -Wno-deprecated-declarations

# RM= /bin/rm -f

# CD = cd subfolder/ # doesn't work

all: testcomment PutHTML  #APIcalls 

commentEntry.o: ./Backend/commentEntry.cpp ./Backend/commentEntry.h
	$(CC) -c $(CFLAGS) ./Backend/commentEntry.cpp

commentDB.o: ./Backend/commentDB.cpp #commentDB.h
	$(CC) -c $(CFLAGS) -I/usr/include/cppconn ./Backend/commentDB.cpp

testcomment.o: ./Backend/testcomment.cpp ./Backend/commentEntry.h #commentDB.h
	$(CC) -c $(CFLAGS) ./Backend/testcomment.cpp

testcomment: testcomment.o commentDB.o commentEntry.o
	$(CC) testcomment.o commentDB.o commentEntry.o -L/usr/lib -o testcomment -L/usr/local/lib -lmariadbcpp $(CXXFLAGS)

# # testcomment: testcomment.o commentDB.o commentEntry.o
# # 	$(CC) testcomment.o commentDB.o commentEntry.o -L/usr/lib -o testcomment -L/usr/local/lib -lmariadbcpp

# APIcalls.o: APIcalls.cpp httplib.h
# 	$(CC) -c $(CFLAGS) APIcalls.cpp

# APIcalls: APIcalls.o commentDB.o commentEntry.o 
# 	$(CC) APIcalls.o commentDB.o commentEntry.o -o APIcalls -L/usr/local/lib -lmariadbcpp

PutHTML:
	cp listView.html /var/www/html/ArtworkComments/listView
	cp listView.js /var/www/html/ArtworkComments/listView
	cp listView.css /var/www/html/ArtworkComments/listView


	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/commentCpp

clean:
	rm -f *.o  APIcalls testcomment
