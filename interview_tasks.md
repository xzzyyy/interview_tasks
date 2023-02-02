## design

- Should I use execution policies as one of the methods to optimize code by speed?
    - so far it improves only if `func` is not pure
    - try pure `func` and two `for_each` funcs with execution policy
        - seems only close memory regions are fit for this kind of optimizations
- elvis test task
    - adding separators and text continually or atomically
        - I should choose **continually** to abide with spec condition "demonstrate OOP knowledge"
    - nobody asks me to find separator position as soon as it is given to class
        - everything is much simpler and logical if we process everything at `parse` function
    - we need to output some text inside parallelized function to "demostrate work with threads and synchronization objects"
- what build tool to use
    - Boost.Build
    - CMake
    - nothing
