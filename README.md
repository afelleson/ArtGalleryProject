# ArtGalleryProject
 A interface for leaving and viewing comments on select artworks at the Gund Gallery. Includes an admin login for moderating comments and editing the list of available artworks.

## Database setup
Set up phpMyAdmin on your VM.  
See: https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-phpmyadmin-on-ubuntu-22-04 and https://cs.kenyon.edu/index.php/install-mariadb-and-phpmyadmin/

1. Download ArtGalleryProject.sql from this repo to your local device.  
2. Open phpMyAdmin in a browser (http://YourIP//phpMyAdmin).  
3. On the left, at the top, click New.  
4. Enter the name ArtGalleryProject for the new database name and click Create.  
5. Choose Import in the menu at the top, and choose the file ArtGalleryProject.sql.  
6. Click the Import button at the bottom of the page.

## VM Setup (for Ubuntu 22.04.01)  
Run these commands anywhere on in your VM system:  
```
sudo mkdir /var/www/html/ArtworkComments/  
sudo chown ubuntu /var/www/html/ArtworkComments
```

Clone this repository

Set up a mariaDB connector until this line of code in the .h files doesn't give an error: #include <mariadb/conncpp.hpp>   
See: https://www.digitalocean.com/community/tutorials/how-to-install-mariadb-on-ubuntu-22-04 and https://cs.kenyon.edu/index.php/scmp-318-0x-software-development-s23/c-mariadb-connector/



## Running the program
cd to the repo directory and run these commands:  
```
make  
./APIcalls
```
This will terminate after a certain amount of time.

To run the program indefinitely:
```
nohup ./APIcalls &
```

If you have multiple versions of the program running indefinitely at the same time, you may experience weird results.  
To check for existing, indefinitely running versions of the program:
```
ps -aux | grep APIcalls
```
There will always be one process listed, but its Process ID will change every time you rerun that command. If there is more than one process listed, you can kill any process with a consistent ID via
```
kill ######
```
where ##### is the process ID.
