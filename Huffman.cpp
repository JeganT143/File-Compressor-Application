#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include "minHeap.h"

using namespace std;

Node* buildHuffmanTree(map<char, int> frequencyTable)
 {
    minHeap mH(frequencyTable.size());
    map<int,char> sorted; // map is sorted by its key. but we need sorted by frequncy.

    for (const auto& pair : frequencyTable)
    {
        sorted[pair.second] = pair.first; // swaping frequncy table and store t into sorted map
    }

    for (auto i : sorted) // for insert nodes in to minHeap
    {
        Node* temp = new Node(i.second, i.first);
        mH.insertNode(*temp);
    }


    while (mH.currentSize > 1) // do untile the last node remains
    {
        // remove least frequncy nodes and make new node
        Node* temp1 = new Node(mH.removeNode());
        Node* temp2 = new Node(mH.removeNode());
        Node* newNode = new Node(0, temp1->frequency + temp2->frequency);
        newNode->left = temp1;
        newNode->right = temp2;
        mH.insertNode(*newNode);
    }

    return &mH.Arr[0]; // Return the root of the Huffman tree
}


map<char, int> freqencyCount(string text)
{
    map<char, int> frequencyTable;

    for (char c : text)
    {
        if (frequencyTable.find(c) != frequencyTable.end()) // Check if the character is already in the map
        {
            frequencyTable[c]++; // If it's already in the map, increment the count
        }
        else
        {

            frequencyTable[c] = 1; // If it's not in the map, add it with a count of 1
        }
    }

    return frequencyTable;
}

void makeEncoder(Node* node, string code, map<char, string>& encodeTable)
 {
    if (node == NULL)
    {
        return;
    }

    if (node->left == NULL && node->right == NULL)
    {
        encodeTable[node->data] = code; // Assign the generated code for the character

    }

    makeEncoder(node->left, code + "0", encodeTable);
    makeEncoder(node->right, code + "1", encodeTable);
}



map<string, char> makedecorder(map <char, string> encodeTable)
{
    map<string, char> decorder;

 // decoder table is swpaed encorder table. so swap
    for (const auto& pair : encodeTable)
    {
        decorder[pair.second] = pair.first;
    }

    return decorder;
}

string encode(string dataFile, map<char, string> encodTable)
{
    string ans = "";

    for (char i : dataFile)
    {
        ans = ans + encodTable[i];
    }
    return ans;
}

string decode(string encoded , map<string , char> decorderTable )
{
    string key = "";
    string decoded = "";
    for (char ch : encoded)
    {
        key = key + ch;

        auto it = decorderTable.find(key);  // Key found in the map

        if (it != decorderTable.end())
        {

            decoded += it->second;
            key = "";  // Reset key for the next sequence
        }
    }

    return decoded;
}

string readFile(string FileName)
{

    ifstream inputFile(FileName);
    string tempString;
    string document;
    while (getline(inputFile, tempString)) // read the file from input file and store it on temp string.
    {
        document = document + (tempString + "\n");
    }
    inputFile.close();

    return document;

}

void writeBinaryToFile(const string& fileName, const string& binaryText) {
    ofstream outFile(fileName, ios::out | ios::binary);

    if (outFile.is_open())
        {
        for (size_t i = 0; i < binaryText.size(); i += 8) {
            string byte = binaryText.substr(i, 8); // Get 8 characters (1 byte) from the binary string
            char byteValue = stoi(byte, nullptr, 2); // Convert the binary string to char
            outFile.put(byteValue); // Write the byte to the file
        }
        outFile.close();
        cout << "Binary-encoded text written to " << fileName << " successfully." << endl;
    }

    else
    {
        cout << "Unable to open the file " << fileName << " for writing." << endl;
    }
}

string readBinaryFromFile(const string& fileName)
{
    ifstream inFile(fileName, ios::in | ios::binary);
    string binaryText = "";

    if (inFile.is_open())
        {
        char byte;
        while (inFile.get(byte))
        {
            for (int i = 7; i >= 0; --i)
             {
                binaryText += ((byte >> i) & 1) ? '1' : '0'; // Convert each byte back to its binary representation
            }
        }
        inFile.close();
        cout << "Binary-encoded text read from " << fileName << " successfully." << endl;
    }
    else
     {
        cout << "Unable to open the file " << fileName << " for reading." << endl;
    }

    return binaryText;
}

void writeFile(const string& inputString)
 {
    ofstream outputFile("decoded_File.txt"); // Create a new file named "decoded_File.txt"

    if (outputFile.is_open())
        {
        size_t start = 0;
        size_t end = inputString.find("\n");
        while (end != string::npos)
        {
            outputFile << inputString.substr(start, end - start + 1); // Write each line including newline character
            start = end + 1;
            end = inputString.find("\n", start);
        }
        outputFile << inputString.substr(start); // Write the last line without a newline character
        outputFile.close();
        cout << "String has been written to decoded_File.txt successfully." << endl;
    }
    else {
        cout << "Unable to open the file." << endl;
    }
}


void writeEncodeTableToFile(const string& fileName, const map<char, string>& encodeTable)
 {
    ofstream outFile(fileName);

    if (outFile.is_open())
    {
        for (const auto& pair : encodeTable)
        {
            outFile << pair.first << " " << pair.second << endl; // Write each character and its code to the file
        }
        outFile.close();
        cout << "Encode table written to " << fileName << " successfully." << endl;
    }
    else
    {
        cout << "Unable to open the file " << fileName << " for writing." << endl;
    }
}

map<char, string> readEncodeTableFromFile(const string& fileName)
 {
    ifstream inFile(fileName);
    map<char, string> encodeTable;

    if (inFile.is_open()) {
        char character;
        string code;
        while (inFile >> character >> code) {
            encodeTable[character] = code; // Read character and its code from the file
        }
        inFile.close();
        cout << "Encode table read from " << fileName << " successfully." << endl;
    } else {
        cout << "Unable to open the file " << fileName << " for reading." << endl;
    }

    return encodeTable;
}



int main()
{

    map<char, int> frequencyMap;            // to store frequncy of each char in input file
    map<char, string> encodeTable;          // to store char and its new binary code
    map<string, char> decodeTable;          // to store new binary code and its char
    string fileName;                        // to store file name which we going to compress
    string dataInFile;                      // to store the data as string formate
    string encodedText; 	                // to store encoded text (its in binary form)
    bool condition = true ;

    while(condition)
    {
    system("cls"); // to clear the screen
    cout << "==================================================================================================================" << endl ;
    cout << "==================================================================================================================" << endl;
    cout << "=============================                                                        =============================" << endl ;
    cout << "=============================        File Compresser using Huffman alogithm          =============================" << endl ;
    cout << "=============================                                                        =============================" << endl ;
    cout << "==================================================================================================================" << endl ;
    cout << "==================================================================================================================" << endl ;
    cout << endl << endl ;

    cout << "***********************************************     Instructions   ***********************************************" << endl ;

    cout << endl << endl ;


    cout << "                                ==>           # To compress operation Press C           <== "                             << endl;
    cout << "                                ==>           # To decompress operation Press D         <== "                             << endl;
    cout << "                                ==>           # To Exit from program press E            <== "                             << endl;

    char asSwitch ='\0';                // for swiching operation

    cin >> asSwitch ;


        if(asSwitch == 'c' || asSwitch == 'C')
        {
            //CompressOperation
                cout << "Enter File Name with extention (Example \"Text.txt\" : )  := " ;
                cin  >> fileName;
                dataInFile = readFile(fileName);
                frequencyMap = freqencyCount(dataInFile);
                Node* fullTree = buildHuffmanTree(frequencyMap);
                makeEncoder(fullTree, "", encodeTable);
                encodedText = encode(dataInFile, encodeTable);
                string encodedBinaryFileName;
                cout << "Enter Output File name with extension .bin (Example: output.bin): ";
                cin >> encodedBinaryFileName; // Read the file name from the user
                writeBinaryToFile(encodedBinaryFileName, encodedText);
                writeEncodeTableToFile("encode_table.txt", encodeTable);
        }
        else if (asSwitch == 'd' || asSwitch == 'D')
        {

                encodeTable = readEncodeTableFromFile("encode_table.txt");
                decodeTable = makedecorder(encodeTable);
                cout << "Enter File name with excention .bin (Example : output.bin)  :" ;
                cin  >> fileName;
                string retrievedBinaryText = readBinaryFromFile( fileName);
                string decoded = decode(retrievedBinaryText ,decodeTable );
                writeFile(decoded);
        }

        else if (asSwitch == 'e' || asSwitch == 'E') {
                condition = false ;
            break; // Exit the loop and end the program
        }

        else
        {
            cout << "Invalid Input :( " << endl;
        }


    }



    return 0;

}
