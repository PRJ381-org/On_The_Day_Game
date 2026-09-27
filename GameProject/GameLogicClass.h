#pragma once
#define PY_SSIZE_T_CLEAN
#include <string>
#include <random>
#include <cctype>
#include <vector>
#include <algorithm>



class GameLogicClass
{
private:
	std::string FinalMorseCode;
	std::string FinalCypherCode;
	const std::string CodeOptions[5] ={"Belgium Campus Is Awsome","Information Technology Is The Future","Belgium Campus ITversity","The Future Is Code","It's The Way We're Wired"};
	const std::string MoseCode[26] = { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.." };

	int Random(int Lower, int Upper) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distrib(Lower, Upper);
		return distrib(gen);
	}

	void SelectCode() {
		int RandomIndex = Random(0,3);
		FinalMorseCode = CodeOptions[RandomIndex];
		FinalCypherCode = CodeOptions[RandomIndex+1];

		return;
	}


public:


	GameLogicClass() {
		//constructor Code
		SelectCode();
	}

	bool CheckMorseCode(std::string TestString) {
		std::string text = FinalMorseCode;
		for (char& c : text) {
			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		}
		for (char& c : TestString) {
			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		}

		if (TestString == text) {
			return true;
		}else
		{
			return false;
		}
	}

	std::string GenerateMorseCode(std::string InString) {
		std::vector<char> chars(InString.begin(), InString.end());
		std::string outString = "";
		int i = 0;
		for (char C : chars)
		{
			i++;
			C = std::tolower(C);
			char lower_char = std::tolower(static_cast<unsigned char>(C));
			if (lower_char >= 'a' && lower_char <= 'z') {
				outString += MoseCode[lower_char - 'a'] + " ";
			}
			else {
				outString += "  ";
			}
		}
		return outString;
	}


	std::string GetMorseCode() { return GenerateMorseCode(FinalMorseCode); }

	static std::string rot13(const std::string& s) { 
		std::string out = s; 
		for (char& c : out) 
		{ 
			if (c >= 'a' && c <= 'z') c = char('a' + (c - 'a' + 13) % 26); 
			else if (c >= 'A' && c <= 'Z') c = char('A' + (c - 'A' + 13) % 26); 
		} 
		return out; 
	}

	std::string GetCypherCode() { return rot13(FinalCypherCode); }

	bool CheckCypherCode(std::string TestString) {
		std::string text = FinalCypherCode;
		for (char& c : text) {
			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		}
		for (char& c : TestString) {
			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		}
		if (TestString == text) {
			return true;
		}
		else
		{
			return false;
		}
	}
	
	std::string GetUserInfoMorseCode() {
		std::string OutString = "The Morse Code is:\n"+GenerateMorseCode(FinalMorseCode)+"\n";

		OutString += "\nUse the Following Python Code to decode the Morse Code:\n\n";
		
		OutString+= R"PYTHON_CODE(# Dictionary mapping Morse Code to English Alphanumeric Characters
MORSE_CODE_DICT = {
    '.-': 'A', '-...': 'B', '-.-.': 'C', '-..': 'D', '.': 'E', 
    '..-.': 'F', '--.': 'G', '....': 'H', '..': 'I', '.---': 'J', 
    '-.-': 'K', '.-..': 'L', '--': 'M', '-.': 'N', '---': 'O', 
    '.--.': 'P', '--.-': 'Q', '.-.': 'R', '...': 'S', '-': 'T', 
    '..-': 'U', '...-': 'V', '.--': 'W', '-..-': 'X', '-.--': 'Y', 
    '--..': 'Z', '-----': '0', '.----': '1', '..---': '2', '...--': '3', 
    '....-': '4', '.....': '5', '-....': '6', '--...': '7', '---..': '8', 
    '----.': '9'
}

def decode_morse(morse_code: str) -> str:
    """
    Decodes a string of Morse code into plain English text.
    Letters should be separated by 1 space, and words by 3 spaces.
    """
    decoded_message = []
    
    words = morse_code.strip().split("   ")
    
    for word in words:
        decoded_word = []
        letters = word.split(" ")
        
        for letter in letters:
            if letter in MORSE_CODE_DICT:
                decoded_word.append(MORSE_CODE_DICT[letter])
            elif letter == '':
                continue
            else:
                decoded_word.append('?') 
                
        decoded_message.append("".join(decoded_word))
        
    return " ".join(decoded_message)

if __name__ == "__main__":
    sample_input =" )PYTHON_CODE"+ GenerateMorseCode(FinalMorseCode) + R"PYTHON_CODE("  
    result = decode_morse(sample_input)
    print(f"Encoded: {sample_input}")
    print(f"Decoded: {result}"))PYTHON_CODE";

		// Outputting the stored Python code example to the user
		OutString += "\n\nPress 'Enter' to Run your code!.\n";


		return OutString;
	}

	std::string GetUserInfoCypherCode() {
		std::string OutString = "The Cypher Code is:\n" + GetCypherCode() + "\n";
		OutString += "\nUse the Following Python Code to decode the Cypher Code:\n\n";
		OutString += R"PYTHON_CODE( import codecs

ciphertext = ")PYTHON_CODE" + GetCypherCode() + R"PYTHON_CODE("

# Decode the message
plaintext = codecs.encode(ciphertext, 'rot13')
print(plaintext) )PYTHON_CODE";
		// Outputting the stored Python code example to the user
		OutString += "\n\nPress 'Enter' to Run your code!.\n";
		return OutString;
	}

	std::string GetUserInfoProblemSolve() {
		std::string OutString = "Use the space below to help you figure out your solution to the challenge:\n\n";
		OutString += "Press enter to test your solution!\n\n";
		OutString += "The AI *NEON* is locked in an infinite loop due to conflicting logical rules. Solve the issue by analyzing the conditions and writing a solution.\n\nRules:\n\n\t-If the system detects an error, it logs the error and attempts to restart.\n\t-If the system logs an error, it prevents a restart to avoid corruption.\n\t-If the system iis prevented from restarting, the error is never resolved.\n\nGuiding Thoughts:\n\n\t-Identify the contradiction: which rules are preventing resolution?\n\t-How would a real world system handle an error like this?\n\t-Consider adding a time-out mechanisim, a self-repair mode or modifying one of the rules.\n\t-Think about how operating systems, databases, or automated systems handle recovery\n\nIdentify the issue and purpose in **Plain English**. What should change?";
		return OutString;
	}

	bool CheckProblemSolve(std::string TestString) {
		// For this example, we will consider the correct solution to be any string that contains the word "timeout" or "self-repair"
		std::string lowerTestString = TestString;
		std::transform(lowerTestString.begin(), lowerTestString.end(), lowerTestString.begin(), ::tolower);
		if (lowerTestString.find("timeout") != std::string::npos || lowerTestString.find("self-repair") != std::string::npos || lowerTestString.find("recovery") != std::string::npos || lowerTestString.find("loop") != std::string::npos || lowerTestString.length() > 20) {
			return true;
		}
		else
		{
			return false;
		}
	}

};

