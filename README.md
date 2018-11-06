# IPPortTranslation


The IPPortTranslation class is written in the main.cpp file. Test cases can be found in the Tests folder. Output is written in the same path of the main.cpp file.


My solution was that, first we read and store all the translation information within NAT file into hashmaps. Then we go through each elements in FLOW file and check that if the current (ip, port) pair matches any translation case. If it is the case, we translate the pair to a new pair and write the output. Otherwise, the current pair does not have any matches.


The data structure I used is hashmap. Because in the NAT file, an (ip, port) pair may have three formats:
1. ip:port
2. \*:port
3. ip:\*

Therefore I used three different hashmaps for each of these cases:
1. ip\_port\_map<string, string>, while key is ip:port and value is the new ip:port
2. port\_map<string, string>, while key is port and value is the new ip:port
3. ip\_map<string, string>, while key is ip and value is the new ip:port
Depends on whether the string contains the char \* and whether this \* is on ip or port, the string will be distributed to a different hashmap. Similar idea to check a given (ip, port) pair in the FLOW file. My program will check format 1 first. If format 1 is satisfied, result will be written to the output file and continue. Otherwise it will check format 2, and then format 3.


The reason I use hashmap is that it takes O(1) time to check the existence of an (ip, port) pair. This will be very efficient if the given FLOW file is large. However, this means that all the NAT translation info is stored in the hashmap, which requires lots of space if the NAT file is large. If we care more about the time efficiency, this solution is acceptable. However, if we care more about space efficiency instead of time, we can scan the NAT file every time for each FLOW element to see if there is a match. It will be much slower under this case but we don't need to store any data. The choice of these two solutions depends on real-life requirements.


Some edge cases:
1.1.1.1:1000,2.2.2.2:2000
\*:1000,3.3.3.3:3000
1.1.1.1:\*,4.4.4.4:4000
If given an (ip, port) pair, eg. 1.1.1.1:1000, which satisfies all three cases. My program will output 2.2.2.2:2000 beacuse it checks format 1 first and the given string matches.
