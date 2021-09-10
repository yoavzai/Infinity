#include <iostream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

static void Run(vector< pair<string, int> >& histo);
static void Print(vector< pair<string, int> >& histo);

int main()
{
    vector< pair<string, int> > histo;

    Run(histo);
    Print(histo);

    return 0;
}

static void Run(vector< pair<string, int> >& histo)
{
    vector< pair<string, int> >::iterator iter;
    string cur_input;

    getline(cin, cur_input);

    while(cur_input != ".")
    {
        iter = histo.begin();

        while(iter != histo.end() && cur_input != (*iter).first)
        {
            ++iter;
        }
        
        if (iter == histo.end())
        {
            histo.push_back(make_pair(cur_input, 1));
        }

        else
        {
            (*iter).second++;
        }

        getline(cin, cur_input);
    }
}

static void Print(vector< pair<string, int> >& histo)
{
    vector< pair<string, int> >::iterator iter;

    for (iter = histo.begin(); iter != histo.end(); ++iter)
    {
        if ((*iter).second == 1)
        {
            cout << (*iter).first << endl;
        }

        else
        {
            cout << (*iter).second << " x " << (*iter).first << endl;  
        }
    }
}
