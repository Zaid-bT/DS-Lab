#include<iostream>
#include<string>
using namespace std;


void bruteForceSearch(string text, string pattern) {
	int n = text.length();
	int m = pattern.length();
	for (int i = 0; i <= n - m; i++) {
		int j = 0;
		while (j < m && text[i + j] == pattern[j]) {
			j++;
		}
		if (j == m) { // Match found
		cout << "Pattern found at index " << i << endl;
		}
	}
}

// Rabin-Karp Function
void rabinKarp(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    int d = 256;          // total characters (ASCII)
    int q = 101;          // prime modulus to reduce collisions

    int pHash = 0;        // pattern hash
    int tHash = 0;        // text hash
    int h = 1;
    bool found = false;

    // h = (d^(m-1)) % q
    for (int i = 0; i < m-1; i++)
        h = (h * d) % q;

    // Calculate initial hash of pattern & first window of text
    for (int i = 0; i < m; i++) {
        pHash = (d * pHash + pattern[i]) % q;
        tHash = (d * tHash + text[i]) % q;
    }

    // Slide the window one by one
    for (int i = 0; i <= n - m; i++) {

        // Hash match then check character by character
        if (pHash == tHash) {
            bool match = true;

            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                cout << "Pattern found at index: " << i << endl;
                found = true;
            }
        }

        // Recalculate hash for next window
        if (i < n - m) {
            tHash = (d * (tHash - text[i] * h) + text[i + 1 + m - 1]) % q;

            // If hash becomes negative, convert to positive
            if (tHash < 0)
                tHash += q;
        }
    }
}
int main() { 
	string text = "ABAAABCDBBABCDDEBCABC";
	string pattern = "ABC";
//	bruteForceSearch(text, pattern);
	rabinKarp(text,pattern);
	return 0;
}
