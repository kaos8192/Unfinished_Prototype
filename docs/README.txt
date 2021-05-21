Team Cython
  -Kyle Jenkins
  -Geir Anderson
  -Joshua Obernesser
  -Eric Schmidt
  -Michael Sellers
CMSC 461
Logic Gate Simulator

This program is currently split into two seperate porgrams. Firstly, there is
a system of logic gates built to handle inputs of gates, and will return the
output. Secondly, a GUI is being built to handle graphical interaction. Follow
the instructions below to test both sides of the program.

Terminal:
Here are instructions to compile and run the gates family of files. These files
hold gate logic. You can find all of the code to this part of the program in
the main branch of the folder (In Cython/src/logic-be).
	Compile commands:
		To compile both the test and create versions of the program:
			make all

		To compile the test version of the program:
			make test

		To compile and immediately run the test version of the program:
			make run_tests

		To compile the create version of the program:
			make create

		To compile and immediately run the create version of the program:
			make run_create

		To clean the program executables:
			make clean


	./create commands:
		When you run the create program, you will have options for input.
		To read up on syntax, terms, and valid arguments while the program
		is running, type:
			HELP -- (This will give all of the help information.)
			INPUTS -- (Lists valid input and gate arguments.)
			GLOSSARY -- (Lists Gate terms, what they mean, and offers
						 examples of input and output.)
			SYNTAX -- (Provides correct syntax for operations.)

		To end the program, type:
			END

		To run a NOT gate, type:
			NOT [true/false]

		To run a SPLIT gate, type:
			SPLIT [true/false] [number of outputs you want]

		To run a different gate, type:
			[true/false] [GATE] [true/false]

	The GATE command line argument must be in capitalized letters.


GUI:
Here are instructions to compile and run the GUI. These files are used to build
the GUI. The GUI only runs a window with placeholders and, if enabled, the
Dear ImGui library testing demo.

	Firstly, the GUI needs to be on a graphically-capable Linux or MacOS environment
	and SDL2 needs to be installed (the Windows version). SSH is not compatible with the GUI
	without VNC and X11 enabled and working. For more information on how to
	download SDL2, please check the Makefile in the following filepath below.

    !!!!NEW METHOD!!!!
    Second, goto Cython/maker.
    To compile:
        ./compa_it
        This will do the following:
        make clean
        make
        ../gui_test_proto

    !!!!OUTDATED METHOD!!!!
    Secondly, you need to travel down this path:
	Cython/gui_bundled/gui/gui_master/
	This will take you to the location of the program.

	To compile:
		./compa_it
			This script will run a make clean, make, and run the
			./gui_test_proto script all at once.


