### Explanation of sub_1000CEA0

This function takes a source string and a target character as arguments , and iterates over the source string starting from its last character and returns the target characters position (addres) if its in source string , null if target is not in source string.

The reason it iterates over the string starting from its last character might be checking the current directory , because in Windows directory is in form of A:\smth\smth\... so if it is searching for the character "\" it can find the spesific folder name the program is in.