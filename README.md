# Eigenfaces

###################################################################################################################
#                                                                                                                 #
#       ######  ######  ########  ######      ##       ######       ##      ######  ##  ########  ###    ##	  #
#       ##  ##  ##  ##  ###       ##  ##     ####      ##  ##      ####       ##    ##  ##    ##  ####   ##	  #
#       ######  ######  ##        ######    ## ###     ######     ## ###      ##    ##  ##    ##  ## ##  ##	  #
#       ##      ####    ######    ##       ########    ####      ########     ##    ##  ##    ##  ##  ## ##	  #
#       ##      ## ##   ##        ##      ##    ####   ## ##    ##    ####    ##    ##  ##    ##  ##   ####	  #
#       ##      ##  ##  ########  ##     ##      ####  ##  ##  ##      ####   ##    ##  ########  ##    ###	  #
#                                                                                                                 #
###################################################################################################################
Create folders bin/ and data/

Download the AT&T face-recognition dataset from 
http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html
extract it, and add it to data/ under the original name and folder structure.

This enables bin/main executable to successfully run after running cmake.

Create folder data/output/ for varyEnergy executable.

In order to succesfully the two celebrity executable, you need to follow the instructions 
in preprocessing/celeb.py:
1. create folder data/celeb
2. create folder data/raw
3. download the celebrity pictures at the provided links and store them with the specified 
names in the above-mentioned folder.
4. go to preprocessing/ and run the script (or in a similar hierarchy directory)
If you already have the cropped pictures, you can directly place it in the folder data, 
skipping the steps.


############################################
#                                          #
#       ######  ##    ##   ###    ##	   #
#       ##  ##  ##    ##   ####   ##	   #
#       ######  ##    ##   ## ##  ##	   #
#       ####    ##    ##   ##  ## ##	   #
#       ## ##   ##    ##   ##   ####	   #
#       ##  ##  ########   ##    ###	   #
#                                          #
############################################

In order to run the program, you need to create a bin folder and run the makefile.
After running make, 4 executables will be created:

-> ./main which contains the fist part of the assignment, computing the accuracy over a 
60% training/ 40% testing partition of the data with at most 85% accuracy and removing the
first eigenvector.

-> ./best_five which takes 10 celebrity pictures and returns the five best matches for each,
storing the data in the file data/celeb_accuracy_scores, and displaying 5 of the celebrities
together with the closest matches on the screen

-> ./celeb is a simplified version of ./best_five, only displaying the best match and without 
storing the accuracies.

-> ./varyEnergy runs 20 tests with varying energy, both including and excluding the first eigeface.


Additionally, the script in postprocessing creates the data using the output data generated with ./varyEnergy executable
