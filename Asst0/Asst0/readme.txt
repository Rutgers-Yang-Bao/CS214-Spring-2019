Description of the code :
	My code uses main(int argc, char** argv) to scan the input string and automatically devide the input into several strings by spaces.
	The main function first check if there is a input( argc == 1), if so ,there is no input, so report and print nothing.
	Then the main struct I used to store the tokens is sorted linked list. I traverse all the strings in *argv and seperate them by non-alpha chars and copy the token into a new pointer and send it to my insertNode function.
	The insertNode function will receive the linked list front and the data I want to insert. During insert, I traverse front and decide which node my new node should be inserted before it. I used the check function to compare each character of both strings and return a value shows whether the new node should be insert before the current pointer.
	By this insert function I can make the linked list sorted.
	Before output the result, I check if the front is empty(there is no token from input). If so, report and print nothing.
	At last I write a traverse function to traverse the linked list and print all the datas to screen.
	Also, I remembered to free all the memory I malloc at the end of every function and the main.

The error need to report to screen I considered :
	The input may be empty.
	the input may not include any token.
	Malloc function may fail.
	
The other errors I can think about have been all fixed in the program and no need to report.

For this assignment, I thought about to solve it by only using arrays and traverse the array multiple times to output. But then I think the big-O will be really bad. Then I also think about to use a array which contains all 52 letters(upper and lower cases) as a dictionary so my insert function will be more efficient and the output is also efficient. But I don't have enough time to finish that code So I choose a middle way, just the sorted linked list, which is good while outputing and no bad while inserting.

By the way, I find this assignment is really funny and its code is also happy to writting. Thank you for making this assignment. XD
