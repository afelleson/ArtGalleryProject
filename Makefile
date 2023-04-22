# # Contacts App
# # James Skon, Kenyon College 2022

# CC= g++

# #For Optimization
# #CFLAGS= -O2
# #For debugging
# CFLAGS= -std=c++14  -Wno-deprecated-declarations

# RM= /bin/rm -f

# all: testcontact contactApp PutHTML 

# contactEntry.o: contactEntry.cpp contactEntry.h
# 	$(CC) -c $(CFLAGS) contactEntry.cpp

# contactDB.o: contactDB.cpp contactDB.h
# 	$(CC) -c $(CFLAGS) -I/usr/include/cppconn contactDB.cpp

# testcontact.o: testcontact.cpp contactEntry.h	contactDB.h
# 	$(CC) -c $(CFLAGS) testcontact.cpp

# testcontact: testcontact.o contactDB.o contactEntry.o
# 	$(CC) testcontact.o contactDB.o contactEntry.o -L/usr/lib -o testcontact -L/usr/local/lib -lmariadbcpp

# contactApp.o: contactApp.cpp httplib.h
# 	$(CC) -c $(CFLAGS) contactApp.cpp

# contactApp: contactApp.o contactDB.o contactEntry.o 
# 	$(CC) contactApp.o contactDB.o contactEntry.o -o contactApp -L/usr/local/lib -lmariadbcpp

# PutHTML:
# 	cp contactApp.html /var/www/html/contactCpp/
# 	cp contactApp.js /var/www/html/contactCpp/
# 	cp contactApp.css /var/www/html/contactCpp/


# 	echo "Current contents of your HTML directory: "
# 	ls -l /var/www/html/contactCpp

# clean:
# 	rm -f *.o  contactApp testcontact
