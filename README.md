# IPPortTranslation


The IPPortTranslation class is written in the main.cpp file. Test cases can be found in the Tests folder. Output is written in the same path of the main.cpp file.


My solution was that, first we read and store all the translation infomation within NAT file into hashmaps. Then we go through each elements in FLOW file and check that if the current (ip, port) pair matches any translation case. If it is the case, we translate the pair to a new pair and write the output. Otherwise, the current pair does not have any matches.


The data structure I used is hashmap. Because in the NAT file, an (ip, port) pair may have three formats\:
1. ip:port
2. \*:port
3. ip:\*

