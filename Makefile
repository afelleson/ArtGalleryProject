CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14  -Wno-deprecated-declarations

# RM= /bin/rm -f

# CD = cd subfolder/ # doesn't work

all: APIcalls PutHTML
# all:  testcomment PutHTML # for testing

commentEntry.o: ./Backend/commentEntry.cpp ./Backend/commentEntry.h
	$(CC) -c $(CFLAGS) ./Backend/commentEntry.cpp

artworkEntry.o: ./Backend/artworkEntry.cpp ./Backend/artworkEntry.h
	$(CC) -c $(CFLAGS) ./Backend/artworkEntry.cpp

galleryDB.o: ./Backend/galleryDB.cpp #galleryDB.h
	$(CC) -c $(CFLAGS) -I/usr/include/cppconn ./Backend/galleryDB.cpp

# testcomment.o: ./Backend/testcomment.cpp ./Backend/commentEntry.h ./Backend/artworkEntry.h #galleryDB.h # for testing
# 	$(CC) -c $(CFLAGS) ./Backend/testcomment.cpp

# testcomment: testcomment.o galleryDB.o commentEntry.o artworkEntry.o # for testing
# 	$(CC) testcomment.o galleryDB.o commentEntry.o artworkEntry.o -L/usr/lib -o testcomment -L/usr/local/lib -lmariadbcpp $(CXXFLAGS)

APIcalls.o: ./Backend/APIcalls.cpp httplib.h
	$(CC) -c $(CFLAGS) ./Backend/APIcalls.cpp

APIcalls: APIcalls.o galleryDB.o commentEntry.o artworkEntry.o CTokenGenerator.o
	$(CC) APIcalls.o galleryDB.o commentEntry.o artworkEntry.o ./Backend/CTokenGenerator.cpp ./Backend/CTokenGenerator.h -o APIcalls -L/usr/local/lib -lmariadbcpp

restChat.o: restChat.cpp httplib.h
	$(CC) -c $(CFLAGS) restChat.cpp

CTokenGenerator.o: ./Backend/CTokenGenerator.cpp ./Backend/CTokenGenerator.h
	$(CC) -c $(CFLAGS) ./Backend/CTokenGenerator.cpp

PutHTML:
	cp ./Pages/listView/listView.html /var/www/html/ArtworkComments/listView
	cp ./Pages/listView/listView.js /var/www/html/ArtworkComments/listView
	cp ./Pages/listView/listView.css /var/www/html/ArtworkComments/listView
	cp ./Pages/listView/solid-tack.svg /var/www/html/ArtworkComments/listView
	cp ./GGfavicon.ico /var/www/html/ArtworkComments


clean:
	rm -f *.o  APIcalls testcomment
