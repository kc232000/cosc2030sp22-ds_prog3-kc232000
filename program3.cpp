// Kellen Mentock
// Program 3

#include "hashMap.h"
#include "timer.h"

using namespace::std;

string cleanWord(string dirty)
{
	string clean = "";
	for (int i = 0; i < dirty.length(); i++) {
		if (isalnum(dirty[i])) {
			if (isupper(dirty[i])) {
				clean.push_back(tolower(dirty[i]));
			}
			else {
				clean.push_back(dirty[i]);
			}
		}
		else if (dirty[i] == '\'') {
			clean.push_back(dirty[i]);
		}
		else {}
	}
	if (clean.length() != 0) {
		return clean;
	}
	else {
		return "-";
	}
}

int main()
{
    hashMap<string>* dict = new hashMap<string>;
    ifstream fdict;
    ifstream fbook;
    ofstream badbook;
    string word;
    int dcount=0, count=0, right=0, wrong=0, notChecked=0, fComp=0, nfComp=0;
    vector<string> incorrect;
    Timer timer;
    
    // Load Dictionary

    fdict.open("dict.txt");
    if (fdict.is_open()) {
        while (getline(fdict, word)) {
            dict->insert(cleanWord(word));
            dcount++;
        }
        fdict.close();
        cout << "Dictionary Loaded" << endl;
    }
    else {
        cout << "File Open Error" << endl;
    }

    // Display Dictionary Size

    cout << "Dictionary Size: " << dcount << endl;
    
    // Open the Book

    fbook.open("book.txt");

    // Start Timer

    timer.Start();

    // Spell Check the Book

    if(fbook.is_open()) {
        while (fbook >> word) {
            word = cleanWord(word);
            if(!islower(word[0])) {
                notChecked++;
                count++;
            }
            else if(dict->find(word)) {
                right++;
                count++;
            }
            else {
                incorrect.push_back(word);
                wrong++;
                count++;
            }
        }
        fbook.close();
    }
    else {
        cout << "File Load Error" << endl;
    }

    // Stop Timer

    timer.Stop();
    
    // Output

    cout << "Done checking and these are the results"<<endl;
    cout << "finished in time: "<< timer.Time() <<endl;
    cout << "finished in Milliseconds time: "<< timer.TimeMS() << endl;
    cout << "There are "<<right<<" words found in the dictionary"<<endl;
    cout << dict->fCompares << " compares. Average "<< static_cast<float>(dict->fCompares / right) <<endl;
    cout << endl;
    cout << "There are "<<wrong<<" words NOT found in the dictionary"<<endl;
    cout << dict->nfCompares <<" compares. Average "<< ((wrong != 0) ? (static_cast<float>(dict->nfCompares/wrong)) : 0)<<endl;
    cout << "   There are "<<notChecked<<" words not checked."<<endl;

    // Write Misspelled Words to File

    badbook.open("output.txt");
    for (int i=0; i<incorrect.size(); i++) {
        badbook << incorrect[i] << endl;
    }
    badbook.close();
    
    return 0;
}