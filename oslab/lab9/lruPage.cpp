// 3. wap to implemt lru page replacement algo.

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int fs = 4;
    int rs = 20;
    // cout << "Enter the Frame Size: ";
    // cin >> fs;
    // cout << "Enter the reference string size: ";
    // cin >> rs;
    vector<int> frame(fs, -1); // initialize with -1 for clarity
    vector<int> ref(rs);
    ref = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    // for (int i = 0; i < rs; i++)
    // {
    //     cout << "Enter the " << i + 1 << " reference page no: ";
    //     cin >> ref[i];
    // }
    int hit = 0, miss = 0;
    for (int i = 0; i < fs; i++)
    {
        frame[i] = ref[i];
        miss++;
        // Print initial steps
        cout << "Step " << i + 1 << " - Page: " << ref[i] << " | Frame: ";
        for (int j = 0; j <= i; j++)
            cout << frame[j] << " ";
        cout << "(Miss)" << endl;
    }

    int k = fs;

    while (k < rs)
    {
        bool flag = true;
        for (int i = 0; i < fs; i++)
        {
            if (frame[i] == ref[k])
            {
                flag = false;

                // Print hit
                cout << "Step " << k + 1 << " - Page: " << ref[k] << " |Frame: ";
                for (int j = 0; j < fs; j++)
                {
                    cout << frame[j] << " ";
                }
                cout << "(Hit)" << endl;

                k++;
                hit++;
                break;
            }
        }
        if (flag)
        {
            // LRU replacement logic
            int lruIndex = -1;
            int leastRecent = k; // furthest back we’ll look

            for (int i = 0; i < fs; i++)
            {
                int j;
                for (j = k - 1; j >= 0; j--)
                {
                    if (ref[j] == frame[i])
                        break;
                }

                if (j < leastRecent)
                {
                    leastRecent = j;
                    lruIndex = i;
                }
            }

            frame[lruIndex] = ref[k];
            miss++;

            // Print Miss
            cout << "Step " << k + 1 << " - Page: " << ref[k] << " | Frame: ";
            for (int j = 0; j < fs; j++)
                cout << frame[j] << " ";
            cout << "(Miss)" << endl;

            k++;
        }
    }
    cout << "\nMiss: " << miss << endl;
    cout << "Hit: " << hit << endl;
    cout << "k: " << k << endl;
}
