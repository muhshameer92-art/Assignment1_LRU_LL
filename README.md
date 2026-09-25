# Assignment 1 Implementing LRU for Memory Management 

## 1. Introduction: What Is a Memory Management (MM) Module? 

In an operating system, many programs run at the same time, and each program uses memory in fixed-size chunks called pages. Because physical memory is limited, the operating system must keep track of which pages each running program is currently using, and it must decide which pages to keep in memory and which pages could be replaced if space runs out. 

The Memory Management (MM) module is the part of the operating system responsible for this bookkeeping. It does not decide what a program computes — it only tracks, for every running program, which memory pages that program has touched, and in what order they were last used. This information is exactly what a page replacement algorithm (such as LRU, described below) needs in order to decide which page to evict when memory is full. 

This assignment focuses only on the bookkeeping part: maintaining the data structures the MM module uses to record page usage. You will not need to implement actual memory allocation or physical page eviction — you only need to maintain the two linked lists described below so that they always correctly reflect recency of use. 

### 1.1 What is LRU? 

LRU stands for “Least Recently Used.” It is a simple and widely used policy: among all the pages currently tracked for a program, the one that was accessed longest ago is considered the best candidate to remove first when memory is needed elsewhere. To support this policy efficiently, the MM module keeps each program's pages ordered from most recently used to least recently used, so the least-recently-used page is always easy to find (it sits at the end of the list). 

## 2. Data Structures 

The MM module maintains two levels of linked lists: 

- Program List — a single linked list containing one node per currently running program. 

- Page List (per program) — each program node contains its own linked list of the pages that program has used so far, ordered from most recently used (front) to least recently used (end). 

The diagram below shows this two-level structure for three programs, each with its own page list: 



<!-- Start of picture text -->
Program List (linked list)<br>Each program :Rs its own Page 4st (most-recently-usgefirst):<br>Program A's<br>Program B's 3<br>Program C's<br>Page list:<br>Front of page list = Most Recently Used (MRU)<br>End of page list (before NULL) = Least Recently Used (LRU)<br><!-- End of picture text -->

_Figure 1: Overall structure — a Program List, where each program node owns its own Page List._ 

## 3. Rules the MM Module Must Follow 

### 3.1 Handling a memory access request 

Whenever a program accesses a memory page, the MM module receives a request of the form (program, page). It must: 

1. Locate the requesting program's node in the Program List. 

2. Search that program's Page List for the requested page. 

3. If the page IS found (a “hit”): remove it from its current position and re-insert it at the FRONT of the page list, marking it as most recently used. 

4. If the page is NOT found (a “miss”): insert a new node for that page at the FRONT of the page list, since it is now the most recently used page. 



<!-- Start of picture text -->
Case 1: Requested page IS found in the program's page list (HIT)<br>Before:<br>wreavest ge”) | ne |<br>Page 3 removed from<br>current position and<br>moved to the FRONT<br>as [ome |<br><!-- End of picture text -->

_Figure 2: Page HIT — an existing page is moved to the front of the page list._ 



<!-- Start of picture text -->
Case 2: Requested page is NOT found in the program's page list (MISS)<br>Before:<br>(reauest Page ¢ nek vf me || me |<br>Pageinserted4 isata theNEWFRONT page—<br>of the page list<br>as [me |<br><!-- End of picture text -->

_Figure 3: Page MISS — a new page is inserted at the front of the page list._ 

### 3.2 Handling program start and end 

- When a new program starts, a new node is created for it and inserted at the END of the Program List, with an empty page list. 

- When a program ends, its node (together with its entire page list) is removed from the Program List. 



<!-- Start of picture text -->
New Program Starts ~ inserted at the END of the Program List<br>Before: new Program D starts<br>ee le ie, Mee,<br>After: Program D added at the end (before NULL)<br><!-- End of picture text -->

_Figure 4: A new program is always appended at the end of the Program List._ 

## 4. Your Task 

You are required to implement the part of the MM module that maintains these two linked lists correctly. Specifically, implement the following operations 

|**Function**|**Required Behaviour**|
|---|---|
|startProgram(programID)|Creates a new program node with an empty page list and inserts it at the end of the<br>Program List.|
|endProgram(programID)|Removes the given program's node (and its page list) from the Program List.|
|accessPage(programID,<br>pageID)|Finds the program, then searches its page list for pageID. If found, moves it to the<br>front. If not found, inserts it at the front as a new page.|
|printState()|Prints the current Program List and, for each program, its Page List from most to least<br>recently used (for testing/debugging).|



### 4.1 Classes 

You would need the following classes for this assignment: 

Linked list (including node and iterator class) 

Program (each object stores the memory usage and program ID) 

Memory_Manager (maintains the list of running programs) 

### 4.2 Constraints and notes 

- Implement the Program List and each Page List using linked lists  — do not use a built-in dynamic array/list as a substitute for the linked-list logic. 

- accessPage() must run by traversing the list and adding a move function so that the exercise reflects how the underlying linked-list pointers are actually updated. 

- Assume programIDs and pageIDs are simple integers and are unique within their scope (a pageID is only unique within a single program's page list, not globally). 

- You do not need to implement actual page eviction or a maximum page-list size for this assignment — only the ordering logic described above. 

- Overload appropriate operators for comparison (equality operator that compares a program and integer ID) 

## 5. Worked Example (Trace) 

The table below shows a sequence of operations and the resulting state of the Program List and each program's Page List. Use this to check your implementation. 

|**Operation**|**Program List(after)**|**Page List Affected(front → end)**|
|---|---|---|
|startProgram(A)|A|A: (empty)|
|startProgram(B)|A, B|B: (empty)|
|accessPage(A, 1)|A, B|A: 1|
|accessPage(A, 2)|A, B|A: 2, 1|
|accessPage(A, 1)|A, B|A: 1, 2   (hit — page 1 moves to front)|
|accessPage(B, 5)|A, B|B: 5|
|startProgram(C)|A, B, C|C: (empty)|
|accessPage(A, 3)|A, B, C|A: 3, 1, 2   (miss — page 3 inserted at<br>front)|
|endProgram(B)|A, C|(B and its page list removed)|

