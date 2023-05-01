#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

int main()
{
    int page_frames, page_faults = 0, page_references;
    cout << "Enter the number of page frames: ";
    cin >> page_frames;
    cout << "Enter the number of page references: ";
    cin >> page_references;

    int pages[page_references];
    cout << "Enter the page reference string: ";
    for (int i = 0; i < page_references; i++) {
        cin >> pages[i];
    }

    list<int> page_list; // list to keep track of page frames in LRU order
    unordered_map<int, list<int>::iterator> page_table; // hash table to map page numbers to list iterators

    for (int i = 0; i < page_references; i++) {
        int page = pages[i];
        bool page_found = false;

        // Check if page is already in memory
        if (page_table.find(page) != page_table.end()) {
            page_list.erase(page_table[page]);
            page_found = true;
        }

        // If page is not in memory, add it and increment page_faults
        if (!page_found) {
            if (page_list.size() == page_frames) {
                int oldest_page = page_list.back();
                page_list.pop_back();
                page_table.erase(oldest_page);
            }
            page_faults++;
        }

        page_list.push_front(page);
        page_table[page] = page_list.begin();
    }

    cout << "Number of page faults: " << page_faults << endl;

    return 0;
}
