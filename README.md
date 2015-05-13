# Eigenfaces

## Setup

````
cd Eigenfaces
mkdir data/celeb
mkdir data/raw
mdkir data/output
python preprocessing/download.py
python preprocessing/celeb.py
rm -rf data/raw
```

## Run


```
./main 
```
Contains the fist part of the assignment, computing the accuracy over a 
60% training/ 40% testing partition of the data with at most 85% accuracy and removing the
first eigenvector.

'''
./best_five 
'''

Takes 10 celebrity pictures and returns the five best matches for each,
storing the data in the file data/celeb_accuracy_scores, and displaying 5 of the celebrities
together with the closest matches on the screen

'''
./celeb 
'''
A simplified version of ./best_five, only displaying the best match and without 
storing the accuracies.

'''
./varyEnergy
'''
Runs 20 tests with varying energy, both including and excluding the first eigeface.


Additionally, the script in postprocessing creates the data using the output data generated with ./varyEnergy executable
