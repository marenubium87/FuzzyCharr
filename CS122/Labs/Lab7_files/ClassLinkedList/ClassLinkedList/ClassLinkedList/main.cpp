#include "ListApp.h"

int main(void)
{
	// Start with debugging this project! "Step Into" each statement to answer the questions!
	// Question 1: what function is called in the statement below?
	// A:  The ListNode constructor
	ListNode n1;
	// Question 2: what function is called in the statement below?
	// A:  Also the ListNode constructor, shallow copy, simply
	//		"copy-pastes" the values over to the new object
	ListNode n2(42); // shallow or deep copy?
	// Question 3: what function is called in the statement below?
	// A:  The ListNode copy constructor, shallow copy because we simply 
	//		copied over the data and pointer values
	ListNode n3(n2); // shallow or deep copy?
	// Question 4: what function is called in the statement below?
	// A:  The ListNode copy constructor, shallow copy because we simply 
	//		copied over the data and pointer values
	ListNode n4 = n3; // shallow or deep copy?
	
	ListNode n5;
	// Question 5: what function/operator is called in the statement below?
	// A:  Technically the = (overloaded assignment operator); we didn't 
	// define one so the compiler defines one by default
	// (with probably predictable but still unknown behavior
	// SO USE CAUTION!)
	n5 = n4; // did we explicitly implement this function/operator?   Nope.

	// Question 6: what function is called in the statement below?
	// A:  The default constructor for the list class
	List l1;
	// make sure that you finish implementing the copy constructor for the List object before you try to 
	// execute the next statement!
	// Question 7: what function is called in the statement below? What would happen if we did not 
	//             explicitly implement the function? Would the compiler generated one be good enough?

	//				Calls copy constructor, if we didn't explicitly implement
	//				one the compiler would generate one by default for us.  
	//				And it'd make a shallow copy (just copy the pointers over
	//				without actually copying any of the nodes,
	//				which will get us into a lot of trouble with respect to 
	//				pointers (also see question 8 for a specific example of why)

	 List l2 = l1; // shallow or deep copy?		A:  deep, after implementation
	// Question 8: what would happen if a shallow copy constructor is used, instead of a deep copy constructor, 
	//             when the destructor for each list object is implicily invoked? 

	//			   (The below was already written so... not sure what I'm supposed to do here.)
	//			   l2 and l1 would have the same
	//             address stored in the head pointer, and thus, one of the lists would be freed and when the other went
	//             out of scope, the destructor would try to access already freed memory (a dangling pointer situation)!


	List l3;
	// make sure that you finish implementing the overloaded assignment for the List object before you try to 
	// execute the next statement!
	// Question 9: what function is called in the statement below? What would happen if we did not 
	//             explicitly implement the function? Would the compiler generated one be good enough?
	
	//				Calls overloaded assignment operator, if we didn't explicitly 
	//				one the compiler would generate one by default for us.  
	//				And it'd make a shallow copy (just copy the pointers over
	//				without actually copying any of the nodes,
	//				which will get us into a lot of trouble with respect to 
	//				pointers (also see question 10 for a specific example of why)


	l3 = l2; // shallow or deep copy?   A:  Deep, after implementation.
	// Question 10: what would happen if a shallow copy assignment is used, instead of a deep copy assignment, 
	//              when the destructor for each list object is implicily invoked? 

	//				(Again, the below was already written so... not sure what I'm supposed to do here.)
	//				l3 and l2 would have the same
	//              address stored in the head pointer, and thus, one of the lists would be freed and when the other went
	//              out of scope, the destructor would try to access already freed memory (a dangling pointer situation)!

	// Question 11: how does the List destructor free up the nodes? You will need to visit "List.cpp" to answer this question!
	//	A:  It calls "destroyList" which itself calls a helper function that recursively deletes the nodes.
	//		Specifically, it first calls itself on the next element of the list until it hits nullptr,
	//		and then it deletes the current (non-null) node, so as the stack frames execute it deletes each node in turn, 
	//		and this has the effect of deleting the list in the direction from the tail to the head.



	ListApp app;

	app.runApp();

	return 0;
}