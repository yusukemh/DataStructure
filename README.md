# DataStructure
ICS621 Project

## List of Contents
- testset: top directory for different types of test sets
- makefile
- .cpp files: st.cpp, rbt.cpp treap.cpp
- run_analysis.py: runs analysis
- TestSetGenerator.ipynb: iPython Notebook for generating test sets

## Specific Instructions
- To compile .cpp files, run `make` and it compiles all three of the .cpp files.
- To run an expetiment on a single instance of a test set, run</br>
`./<tree> testsets/<test_set_instance>.txt`</br>
For example, to run the second instance of test set A-I-50000 on RBT tree, run</br>
`./rbt testsets/A-I/50000/iter_2.txt`
- run_analysis.py</br>
To run, `python3 run_analysis.py`</br>
This file runs analysis on every instance of test set for five times each. Inside the file, set the `if` block to `True` or `False` to determine which analysis to run.</br>
Calculates average execution time for each type of test set and prints it out.</br>
If running analysis on H test sets, make sure to alter all .cpp files as follows:</br>
`bool height_analysis = false;` => `bool height_analysis = true;`
