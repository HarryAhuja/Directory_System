# Directory_System

The computer OS uses an organizational unit called "directory" to organize the folder and files into a hierarchical structure.
A directory contains multiple files and other directories and it provides user with a logical file group.

A directory uses "/" as a separator character and shows its route within the file system.
"/" may represent a root directory or a hierarchical relationship between parent directories and subdirectories.
For instance, "/aa/bb" indicates that under the root directory, there is the "aa" directory, beneath which lies the "bb" directory.

There are various features related to a directory but following 5 features are implemented in this project
- Create a directory
- Remove a directory
- Copy   a directory
- Move   a directory
- Check the number of subdirectories


<img src="images/initial.PNG" height="100" width="350">
<img src="images/mkdir.PNG" height="100"   width="350">
<img src="images/remove.PNG" height="100"  width="350">
<img src="images/copy.PNG" height="120"    width="350">
<img src="images/move.PNG" height="120"    width="350">
<img src="images/find.PNG" height="120"    width="350">



<br/>
<br/>
  
  
#### Look at the table below in which functions are called in following order ####
<img src="images/table.PNG" height="300">
<br/>
<br/>

#### When functions #1 to #4 are called, the directory structure will be like this [Fig. 1] ####
<img src="images/fig1.PNG" height="300">
<br/>
<br/>


#### When function #5 is called, the directory structure will be like this [Fig. 2] ####
<img src="images/fig2.PNG" height="300">
<br/>
<br/>


#### When function #6 is called, the directory structure will be like this [Fig. 3] ####
<img src="images/fig3.PNG" height="300">
<br/>
<br/>


#### When function #7 is called, the directory structure will be like this [Fig. 4] ####
<img src="images/fig4.PNG" height="300">
<br/>
<br/>


#### When function #9 is called, the directory structure will be like this [Fig. 5] ####
<img src="images/fig5.PNG" height="300">
<br/>
<br/>


## Constraints ##
* Maximum directories that can be made is 50,000
* The directory name is made of small letters and its length is >=2 and <=6
* The route of every directory is not longer than 1999
* No directories under same parent have same name
* Only upto 30 directories can have same parent directory

## How to Compile and Run Project ##
* git clone https://github.com/HarryAhuja/Directory_System.git
* cd Directory_System/
* make clean
* make -j
* ./directory.exe  -->(directory is the name of executable)
* Output of the program should be "#Test Case:1 Passed"
* All Object files will be stored in Directory_System/output/ folder
