
/******************************************************************************
 * Target sum problem: Given a list of numbers, find any two that add up to a
 *                     target sum.
 *****************************************************************************/
#include "beginnerProblems.h"
#include "euler.h"
#include <array>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <functional>
#include <chrono>
#include <list>

static void targetSumSorted(const std::vector<int>& numbers, const int target);
static void targetSumUnsorted(const std::vector<int>& numbers, const int target);


static void printVector(const std::vector<int>& vec) {
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


/* ****************************************************************************
* Problem 1:   Two Sum Problem
*
* Description: Given an array of numbers and a target value, find out if any
*              two numbers in the array add up to the target.
*
* Solution:    The optimal solution for this problem is an O(n) algorithm where
*              you iterate over the data, storing the difference between each
*              number and the target value inside a hash set. Every time you
*              read a new number, check if it's complement is already in the
*              set. If so, then there is a match for the two sum problem.
*              If not, move to the next number. The look ups are O(1) so they
*              do not add to the time complexity.
* ****************************************************************************/
static void targetSumUnsorted(const std::vector<int>& numbers, const int target) {
	std::unordered_set<int> complements;
	for (std::vector<int>::const_iterator it = numbers.begin(); it != numbers.end(); it++) {
		// Get the required complement for the current value
		int c = target - *it;
		// Check if the complement for the current value is in the set, if a match is found
		// then we have our pair.
		if (complements.count(target - c) > 0) {
			std::cout << "Found: " << target - c << ", " << c << std::endl;
			return;
		}
		complements.insert(c);
	}
	std::cout << "No values found" << std::endl;
}

/* Sub optimal solution. Still O(n) but only works on sorted data. */
static void targetSumSorted(const std::vector<int>& numbers, const int target) {
	int high_index = numbers.size() - 1;
	int high = numbers.at(high_index);
	int low_index = 0;
	int low = numbers.at(low_index);

	for (std::vector<int>::const_iterator it = numbers.begin(); it != numbers.end(); it++) {
		if (high_index == low_index) {
			std::cout << "No values found" << std::endl;
			return;
		}
		else if (high + low > target) {
			high_index--;
			high = numbers.at(high_index);
		}
		else if (high + low < target) {
			low_index++;
			low = numbers.at(low_index);
		}
		else if (high + low == target) {
			std::cout << "Found: " << high << ", " << low << std::endl;
			return;
		}
	}
}

void test_targetSum(bool sorted, const int target) {
	std::cout << "Checking a random array for a two-sum of " << target << ": ";
	std::vector<int> numbers;
	const size_t VECTOR_SIZE = 10;

	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		numbers.push_back(static_cast<int>(getRandomNumber(-10, 10)));
	}
	printVector(numbers);
	if (sorted) {
		std::sort(numbers.begin(), numbers.end());
		targetSumSorted(numbers, target);
	}
	else {
		targetSumUnsorted(numbers, target);
	}
	numbers.clear();

}



/* ****************************************************************************
* Problem 2:   Add Two Numbers
*
* Description: You are given two non-empty linked lists representing two
*              non-negative integers. The digits are stored in reverse order
*              and each of their nodes contain a single digit. Add the two
*              numbers and return it as a linked list. You may assume the two
*              numbers do not contain any leading zero, except the number 0.
*
* Solution:
*
******************************************************************************/
struct Node {
	unsigned int val = 0;
	Node* next = nullptr;
};

Node* addTwoNumbers(Node* l1, Node* l2) {
	unsigned int sum = 0;
	unsigned int carry = 0;
	Node* tmp1 = l1;
	Node* tmp2 = l2;
	Node* tmp_root = new Node;
	Node* tmp_ret = tmp_root;
	while (tmp1 || tmp2) {
		unsigned int x = (tmp1 != nullptr ? tmp1->val : 0);
		unsigned int y = (tmp2 != nullptr ? tmp2->val : 0);
		unsigned int sum = carry + x + y;
		carry = sum / 10;
		tmp_root->next = new Node;
		tmp_root->next->val = (sum % 10);
		tmp_root = tmp_root->next;
		if (tmp1) tmp1 = tmp1->next;
		if (tmp2) tmp2 = tmp2->next;
	}
	if (carry) {
		tmp_root->next = new Node;
		tmp_root->next->val = carry;
	}
	Node* ret = tmp_ret->next;
	free(tmp_ret);
	return ret;
}

Node* createNodeList(const unsigned int data[], const unsigned int n) {
	if (!n) {
		return 0;
	}
	Node* root = new Node;
	Node* tmp = root;
	for (unsigned int i = 0; i < n; i++) {
		tmp->val = data[i];
		if (i != n - 1) {
			tmp->next = new Node;
			tmp = tmp->next;
		}
	}
	return root;
}

void printList(Node* root) {
	while (root) {
		std::cout << root->val << " ";
		root = root->next;
	}
	std::cout << std::endl;
}

void test_addTwoNumbers() {
	const int LIST_SIZE = 3;
	unsigned int l1[LIST_SIZE] = { 2, 4, 3 };
	unsigned int l2[LIST_SIZE] = { 6, 4, 4 };

	Node* nodeL1 = createNodeList(l1, LIST_SIZE);
	Node* nodeL2 = createNodeList(l2, LIST_SIZE);
	
	printList(nodeL1);
	printList(nodeL2);

	std::cout << "Optimal solution: " << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	Node* sum_optimal = addTwoNumbers(nodeL1, nodeL2);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	printList(sum_optimal);
	std::cout << "Elapsed time: " << duration.count() << " ms. " << std::endl;
}


/* ****************************************************************************
* Problem 3:   Longest Substring Without Repeating Characters
*
* Description: Given a string, find the length of the longest substring without
*              repeating characters.
*
* Solution:
*
******************************************************************************/

int longestSubstringLength_map(const std::string& s) {
	int cur = 0;
	int max = 0;
	std::unordered_map<char, int> seenLetters;
	for (size_t i = 0; i < s.size(); i++) {
		// Check if current letter has not been found
		if (seenLetters.find(s[i]) == seenLetters.end()) {
			// If not found, set the value as the index it appeared at
			seenLetters[s[i]] = i;
			cur++;
		}
		else {
			// The letter had been found, our subsequence needs to restart
			max = std::max(cur, max);
			cur = 0;
			i = seenLetters[s[i]];
			seenLetters.clear();
		}
	}
	return std::max(cur, max);
}

int longestSubstringLength_array(const std::string &s) {
	int cur = 0;
	int max = 0;
	std::array<int, 128> chars{ 0 };
	for (size_t i = 0; i < s.size(); i++) {
		// Check if current letter has not been found
		if (!chars[(s[i])]) {
			// If not found, set the value as the index it appeared at
			chars[(s[i])] = i + 1;
			cur++;
		}
		else {
			// The letter had been found, our subsequence needs to restart
			max = std::max(cur, max);
			cur = 0;
			i = chars[(s[i])] - 1;
			std::fill(chars.begin(), chars.end(), 0);
		}
	}
	return std::max(cur, max);
}

void time_lengthOfLongestSubstring(std::string test, bool useMap) {
	auto start = std::chrono::high_resolution_clock::now();
	std::cout << "Test case: " << test << "\nSubstring Length: ";
	int answer = useMap ? longestSubstringLength_map(test) : longestSubstringLength_array(test);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << answer << "\nTime Elapsed: " << duration.count() << " ms.\n" << std::endl;
}

void test_lengthOfLongestSubstring() {
	std::string test1 = "abcdaefghij";
	std::string test2 = "abbcafddabcabbpwwkew";
	std::string test3 = "dvdf";

	/* Test using the map method */
	std::cout << "Testing longest substring using the map method: " << std::endl;
	time_lengthOfLongestSubstring(test1, true);
	time_lengthOfLongestSubstring(test2, true);
	time_lengthOfLongestSubstring(test3, true);
	std::cout << std::endl << "Testing longest substring using array method: " << std::endl;
	/* Test using the array method */
	time_lengthOfLongestSubstring(test1, false);
	time_lengthOfLongestSubstring(test2, false);
	time_lengthOfLongestSubstring(test3, false);

}


