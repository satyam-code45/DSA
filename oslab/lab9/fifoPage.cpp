// Q1: FIFO Page Replacement in C++

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    int fs = 3;
    int rs = 15;
    // cout << "Enter the Frame Size: ";
    // cin >> fs;
    // cout << "Enter the reference string size: ";
    // cin >> rs;
    vector<int> frame(fs);
    vector<int> ref(rs);
    ref = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0};
    queue<int> q;
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
        q.push(i);

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
                hit++;
                // Print Hit
                cout << "Step " << k + 1 << " - Page: " << ref[k] << " | Frame: ";
                for (int j = 0; j < fs; j++)
                    cout << frame[j] << " ";
                cout << "(Hit)" << endl;

                k++;
                flag = false;
                break;
            }
        }
        if (flag)
        {
            miss++;
            int idx = q.front();
            q.pop();
            q.push(idx);
            frame[idx] = ref[k];

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
