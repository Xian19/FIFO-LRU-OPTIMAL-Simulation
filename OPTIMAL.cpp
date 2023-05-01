#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int page_frames, page_faults = 0, page_references;
    vector<int> pages;

    cout << "Enter the number of page frames: ";
    cin >> page_frames;

    cout << "Enter the number of page references: ";
    cin >> page_references;

    cout << "Enter the page reference string: ";
    for (int i = 0; i < page_references; i++) {
        int page;
        cin >> page;
        pages.push_back(page);
    }

    vector<int> page_table(page_frames, -1); // vector to keep track of page frames in memory

    for (int i = 0; i < page_references; i++) {
        int page = pages[i];
        bool page_fault = true;

        for (int j = 0; j < page_frames; j++) {
            if (page_table[j] == page) {
                page_fault = false;
                break;
            }
        }

        if (page_fault) {
            int replace_index = -1;
            for (int j = 0; j < page_frames; j++) {
                bool found = false;
                for (int k = i + 1; k < page_references; k++) {
                    if (page_table[j] == pages[k]) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    replace_index = j;
                    break;
                }
            }
            if (replace_index == -1) {
                replace_index = 0;
            }
            page_table[replace_index] = page;
            page_faults++;
        }
    }

    cout << "Number of page faults: " << page_faults << endl;

    return 0;
}
