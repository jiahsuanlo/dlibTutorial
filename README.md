# dlibTutorial
C++ dlib simple tutorial. The tutorials in this repo are based on the examples from dlib official website.
(http://dlib.net/). It is focused on setting up dlib projects using Qt creator and MSVC compiler. 

## Development Environment 

- Qt 5.12.4
- Qt Creator 4.9.2
- MSVC 2017

## Download dlib source file

Download the source zip file from dlib website (http://dlib.net/). Unzip it and place to a local directory of your 
choice. 


## dlib setup

To use the dlib, please refer to the dlib official compile page (http://dlib.net/compile.html) for details.

Depending on whether to use CUDA or not, the setup procedure for dlib is different. Here are some simple steps
to set up dlib for both options:

### Setup a Qt project using dlib with **CPU ONLY*:

1. Open Qt and click New Project to create a new project
![NewProject](./Images/NewProject.png)   

2. After creating the project, in the project file:
	- Add the main folder to the include path. 
	- Add the /dlib/all/source.cpp to the project
	
	Here is an example, the dlib main folder is **dlib-19.17** and its relative location with the project folder
	is like following:
	
	/dlib-19.17
	/Workspace/ThisProject
	
	![CPU Project](./Images/CpuProject.png)
	
	
	
	



 
