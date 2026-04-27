# CS-300-8-1-Journal

What was the problem you were solving in the projects for this course?:

The problem was building an advising program to manage a course catalog. It required quickly finding specific courses and efficiently printing the entire catalog in alphanumeric order.

How did you approach the problem? Consider why data structures are important to understand.

I evaluated different data structures to avoid performance bottlenecks. I chose a Binary Search Tree (BST) because it provides fast O(logN) searches while inherently keeping data sorted. This allows the program to print the alphanumeric list via a simple in-order traversal without any extra sorting overhead.

How did you overcome any roadblocks you encountered while going through the activities or project?

I overcame inconsistent file formatting and unpredictable user inputs by adding robust validation. I wrote helper functions to trim whitespace from CSV strings, standardize text casing, remove accidental trailing commas, and clear invalid menu inputs to prevent crashes.

How has your work on this project expanded your approach to designing software and developing programs?

It emphasized the need for theoretical Big-O analysis before writing code. I now approach data structures as active components that dictate the efficiency of specific features, rather than just treating them as basic storage containers.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

It taught me to heavily prioritize modularity. I encapsulated the operations within a dedicated BinarySearchTree class and used adaptable structures, like a vector<string> for prerequisites, to easily handle future curriculum changes without needing to rewrite the code.
