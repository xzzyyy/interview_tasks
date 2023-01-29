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
    
    
## diary

- memorizing QA app
- 2gis 4th task
- prog_notes
 
| ts                | what did                                                                                 |
|-------------------|------------------------------------------------------------------------------------------|
| 230129 (su) 16:20 | prognotes                                                                                |
| 230129 (su) 14:23 | prognotes                                                                                |
| 230128 (sa) 00:09 | prognotes                                                                                |
| 230128 (sa) 22:51 | process memory consumption (Linux), debugging                                            |
| 230128 (sa) 21:09 | process memory consumption (Linux), debugging                                            |
| 230128 (sa) 19:24 | installing `b2` on AlmaLinux                                                             |
| 230127 (fr) 21:16 | sudo/root problems                                                                       |
| 230127 (fr) 19:13 | process memory consumption (Linux), debugging                                            |
| 230127 (fr) 16:50 | process memory consumption (Linux), UT for memory consumption and process id             |
| 230127 (fr) 15:38 | process memory consumption (Linux)                                                       |
| 230127 (fr) 13:21 | prognotes, process memory consumption (Linux)                                            |
| 230127 (fr) 11:56 | prognotes                                                                                |
| 230126 (th) 01:43 | prognotes                                                                                |
| 230126 (th) 22:20 | prognotes                                                                                |
| 230126 (th) 		| prognotes                                                                                |
| 230126 (th) 		| prognotes                                                                                |
| 230125 (we) 		| prognotes                                                                                |
| 230125 (we) 		| settings build-dir system-specific                                                       |
| 230125 (we) 		| 2gis > optimization > memory consumption UTs                                             |
| 230125 (we) 		| 2gis > optimization > (speed UTs, memory consumption)                                    |
| 230125 (we) 		| 2gis optimization task > setting up GDB debugger in Visual Studio Code                   |
| 230125 (we) 		| 2gis optimization task > space optimization debugging                                    |
| 230124 (tu) 		| 2gis optimization task > (space optimization, optimization UTs)                          |
| 230124 (tu) 		| 2gis optimization task > speed optimizations with execution policies                     |
| 230123 (mo) 		| 2gis optimization task > speed optimization with parallel execution policy, pure `func`  |
| 230123 (mo) 		| 2gis optimization task > understanding execution policies                                |
