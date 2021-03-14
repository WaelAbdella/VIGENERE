#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;
int KeywordLength();
void readfile(const string& filename);  // reads the file
void Find_IC();
int counter=0;  // counter to find the total number of characters in the cipher text
double counter2=0; // counter to find the number of characters in the assumed character size
char ch; // reads the first character in the file
char ch2;// reads second character
int i = 1;
int keyLength;
vector <int> CipherTextvec;   // vector to hold the hex values in decimals
vector <int> CipherTextvecCopy;
vector <int> KnownKeyLengthVec; // holds the decimal values after knowing the key length
vector <int>  KeyvaluesforCipher; // holds the decimal values of the key
vector <int>  Positions;
vector <char> letterCorrectionvector;
vector <string> Dictionary; //
vector <string> FinalizedWords;
vector <char> mostOccuringCharacters; // vector that hold the most occuring letters in the english language
map<int,double> LetterFrequencymap; // displays the most reoccuring letters in the
map<int,double>::iterator itr; // iterator for the Letter Frequency map
int main()
{

    readfile("new-extended-given-ciphertext.txt");
    CipherTextvecCopy=CipherTextvec;
    Find_IC();
    int highestCnt=0;
    int mostFreqInt;


    int y=0;
    while(KeyvaluesforCipher.size() < keyLength)
    {
        KnownKeyLengthVec.clear();
        Positions.clear();
        LetterFrequencymap.clear();
    for(int i=y; i < CipherTextvec.size(); i+=(keyLength)) // all the values keylength apart
    {
        KnownKeyLengthVec.push_back(CipherTextvec[i]); // holds all the values keylength apart
    }
     for(int j = 0; j < KnownKeyLengthVec.size(); j++)  // counts the number of occurences of each decimal and counts them
    {
            ch=KnownKeyLengthVec[j];
            itr = LetterFrequencymap.find(ch);
            if(itr!=LetterFrequencymap.end())
            {
                 (*itr).second = (*itr).second+1;
                 counter2++;
                // cout << (*itr).second <<  "       The value" << endl;
            }
            else
            {
            LetterFrequencymap.insert(pair<int, int>(ch, 1));
            counter2++;
            }
          //  TempCharsvec.push_back(ch);
           // cout <<TempCharsvec[counter] << "   checking"<< endl;
            //counter++;
        }

        for (itr = LetterFrequencymap.begin();  itr != LetterFrequencymap.end();  ++itr)
            {
                    if((*itr).second >= highestCnt)
                    {
                        if((*itr).second > highestCnt)
                        {
                            Positions.clear();
                            highestCnt=(*itr).second;
                            mostFreqInt=(*itr).first;
                        }
                        if((*itr).second = highestCnt)
                        {
                                Positions.push_back((*itr).first);
                        }
                    }
            }
            int diffrence;
            int possiblekey;
            int letterCounter=0;
            int highestLettercount=0;
            int MostFreqLetter;
            for(int r=0; r < Positions.size(); r++)
            {
                    for(int v=0; v < mostOccuringCharacters.size(); v++)
                    {
                        possiblekey = (Positions[r])^(mostOccuringCharacters[v]);
                            for(int l=0; l < KnownKeyLengthVec.size(); l++ )
                                {

                                    if((char(possiblekey)^(KnownKeyLengthVec[l])) > 96 && ((char(possiblekey)^(KnownKeyLengthVec[l]) < 123)))
                                        {
                                            letterCounter++;
                                        }
                                        if(letterCounter > highestLettercount)
                                        {
                                            MostFreqLetter=Positions[r];
                                            mostFreqInt=mostOccuringCharacters[v];
                                            highestLettercount=letterCounter;
                                        }
                                }
                                letterCounter=0;
                                highestCnt=0;
                    }

            }
            diffrence = (MostFreqLetter)^(mostFreqInt); //= diffrence;
            KeyvaluesforCipher.push_back(diffrence);
            y++;
            highestCnt=0;
    }
/*
    for(int w = 0; w < KeyvaluesforCipher.size(); w++)
    {
        cout << char(KeyvaluesforCipher[w]) << endl;
    }
  */
    for(int q=0; q < CipherTextvec.size(); q++)
    {
         CipherTextvec[q] = KeyvaluesforCipher[(q % KeyvaluesforCipher.size())] ^ CipherTextvec[q];
         if(q < keyLength)
         {
             letterCorrectionvector.push_back(CipherTextvec[q]);
         }
    }
    ifstream infile;
    infile.open("dictionary.txt");
    string readfile;
    while(!infile.eof())
    {
     infile >> readfile;
     Dictionary.push_back(readfile);
    }
    string mystring;
    string read;
    string finalString;
    int matchcounter=0;
    int highestMatchCounter=0;
    for(int s=0; s < letterCorrectionvector.size(); s++)
    {
        if(char(CipherTextvec[s])!= ' ' && char(CipherTextvec[s])!= ',')
        {
            mystring.push_back(char(CipherTextvec[s]));
        }
        if(char(CipherTextvec[s])== ' ')
        {
            highestMatchCounter=0;
            //system("Pause");
            for(int n = 0; n < Dictionary.size(); n++)
            {
                if(Dictionary[n].length()==mystring.length())
                {
                 //   cout << "2" << endl;
                   // system("Pause");
                    read=Dictionary[n];
                    for(int k=0; k < mystring.length(); k++)
                    {
                     //   cout << "3" << endl;
                       // system("Pause");
                        if(mystring[k]==read[k])
                        {
                            matchcounter++;
                        }
                    }
                        if(matchcounter > highestMatchCounter)
                        {
                        highestMatchCounter=matchcounter;
                        if(char(CipherTextvec[s-1])== ',')
                        {
                          read=read+",";
                        }
                        finalString=read;
                   //     FinalizedWords.push_back(read);
                     //   FinalizedWords.push_back(" ");
                 //       cout << read << endl;
                 //       system("Pause");
                        }

                    matchcounter=0;
                }
            }
            FinalizedWords.push_back(finalString);
            FinalizedWords.push_back(" ");
            mystring.clear();
        }

    }
    string word;
    KeyvaluesforCipher.clear();
    int diffrence2=0;
    int cipherincrement=0;
    cout << "Key length is " << keyLength <<endl;
    for(int h = 0; h < FinalizedWords.size(); h++)
    {
        word = FinalizedWords[h];
        for(int z = 0; z < word.size(); z++)
        {
            diffrence2 = ((int(word[z]))^(CipherTextvecCopy[cipherincrement]));
            cipherincrement++;
            cout << char(diffrence2);
            KeyvaluesforCipher.push_back(diffrence2);
        }
    }
    cout << endl;
    cout << endl;

    for(int b=0; b < CipherTextvecCopy.size(); b++)
    {
         CipherTextvecCopy[b] = KeyvaluesforCipher[(b % KeyvaluesforCipher.size())] ^ CipherTextvecCopy[b];
         cout << char(CipherTextvecCopy[b]);
    }


    return 0;
}

void readfile(const string& filename)
{
    ifstream infile;  //opens the reading stream
    infile.open(filename.c_str());  // uses the passed name from the function to open file
    if(!infile) // if opening the file fails
    {
        cout << "Fail" << endl; // display fail
    }
    unsigned int value;
    while(!infile.eof())  // if the file has opened, while not at the end of the file do this
    {
        string s1;
        string s2;
        string myHexa;
        stringstream ss;
        infile.get(ch);  // read one character from the file
        infile.get(ch2);
        s1.push_back(ch);
        s2.push_back(ch2);
        myHexa=s1+s2;
        ss << hex << myHexa;
        ss >> value;
        counter++;
        CipherTextvec.push_back(value); // insert it into the vector called CipherTextvec
        counter++;
    }
        CipherTextvec.pop_back();
        counter--;
        infile.close();
        mostOccuringCharacters.push_back(' ');
        mostOccuringCharacters.push_back('e');
        mostOccuringCharacters.push_back('t');
        mostOccuringCharacters.push_back('a');
        mostOccuringCharacters.push_back('o');
        mostOccuringCharacters.push_back('i');
        mostOccuringCharacters.push_back('n');
}
void Find_IC()
{
    int counter1=0;
    int enteredCounter=0;
    while(i < 400)////CipherTextvec.size()/4))
    {
        vector <int> TempIntsvec; // a temp vector to hold the decimal values of the cypher
        TempIntsvec=CipherTextvec;
        for (int j=0; j < TempIntsvec.size()-i; j++)
        {
            if(CipherTextvec[j+i] == TempIntsvec[j]) // a shift of positions by one to the right and comparison
            {
                counter2++;
            }
        }
        if(counter2-counter1 > 100)
        {
            enteredCounter++;
            keyLength = i / enteredCounter;
        }

        counter1 = counter2;
        counter2=0;

        i++;
    }

}
