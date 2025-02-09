#include <iostream> // for cin, cout
#include <sstream> // for stringstream
#include <chrono> // for *fancy* timers
#include <iomanip> // for manipulators
#include <fstream> // for file streams
#include <vector> // for vector
// #include <stream>

/* Lecture 1 Code, by Avery Wang, Jan. 9, 2020 */

using namespace std;

int stringToInteger(const string& s);
void stringToIntegerTest();
int mindlessWork();
void bufferedExperiment(ostream& oss);
int endlEachTime();
int endlAtEnd();
void badWelcomeProgram();
void printStateBits(const istream& iss);
std::vector<string> stringSplit(const string& str);
void manipulatorFun();
void printEndTime(const string& input);
void testPrintEndTime();


// During lecture, fill in this main function
// Follow along, type in some code, and
// try experimenting with anything you can think of
// did something unexpected happen? Ask!
int main() {

    /* Uncomment these to play with them */
    // stringToIntegerTest(); // runs ok

    // bufferedExperiment(std::cout); // slowly prints out cs106l
    // bufferedExperiment(std::cerr);
    // why they look the same?

    /* int a = endlEachTime();
    int b = endlAtEnd();
    cout << "endl each time: " << a << endl;
    cout << "endl at end: " << b << endl; */

    // badWelcomeProgram();

    // example 1.1
    ostringstream oss("I'm taking this course lecture 1 ");
    cout << oss.str() << endl;

    oss << "on 25.2.10";
    cout << oss.str() << endl;
    // output "on 25.2.10 this course lecture 1"

    // example 1.2
    ostringstream oss1("I'm taking this course lecture 1 ", stringstream::ate);
    cout << oss1.str() << endl;

    oss1 << "on 25.2.10";
    cout << oss1.str() << endl;
    // output "I'm taking this course lecture 1 on 25.2.10"

    // example 1.3
    istringstream iss("16.9 Ounces");

    double amount;
    string unit;

    iss >> amount;
    iss >> unit;

    cout << iss.str() << endl;
    cout << amount/2 << endl;
    cout << unit << endl;

    int number;

    // example 2.1 state bits
    printStateBits(iss);
    // "State bits: --E-"

    iss >> number; // 失败！流已处于末尾，无法提取数字，number保持未初始化（实际可能为0）
    iss >> unit; // 失败！unit未被修改，仍为"Ounces"

    cout << iss.str() << endl;
    cout << number << " " << unit << endl;
    // "0 Ounces"

    // example 1.4 from deepseek
    iss.clear();          // 清除错误状态（如eofbit）
    iss.seekg(0);         // 将指针移回流的开头
    iss >> number >> unit; // 现在可以正确读取
    cout << number << unit << endl;

    // example 1.5 whitespace separated token
    istringstream iss1("16.9 \n Ounces. . \t \n \n");
    int token1; string token2; char token3; bool token4;
    iss1 >> token1 >> token2 >> token3 >> token4;
    cout << token1 << token2 << token3 << token4 << endl;
    // Types matter! Stream stops reading at any whitespace or any invalid character for the type.

    manipulatorFun();
    testPrintEndTime();

    return 0;
}

// you haven't learned about const or the ampersand
// but that's fine, just pretend it's just a string
// converts the string to an integer
// if the string is not an integer, then throws an exception
int stringToInteger(const string& s) {
    istringstream iss(s);

    int result;
    if (!(iss >> result))
        throw std::domain_error("stringToInteger: no valid integer at beginning found");

    char remain;
    if (iss >> remain)
        throw std::domain_error("stringToInteger: can't have characters after the int");

    return result;
}

// Call this function to test your stringToInteger function
// ignore how it is implemented - you'll learn about this next week.
void stringToIntegerTest() {
    while (true) {
        cout << "Type in an integer: ";
        string s;
        if (!getline(cin, s)) throw std::domain_error("getline failed");
        cout << "You typed in: " << s << "\n";
        int result = stringToInteger(s);
        cout << "As an integer, this is: " << result << "\n";
        cout << "Half of that is: " << result/2 << "\n";
    }
}

// the purpose of this function is to
// experiment with cout vs. cerr
// which are both types of ostreams
// we covered this optional topic at the end of lecture
void bufferedExperiment(ostream& oss) {
    oss << "CS";
    mindlessWork();

    oss << "106";
    mindlessWork();

    // oss << flush;
    // mindlessWork();

    oss << "L";
    mindlessWork();

    oss << endl;
    // mindlessWork();
}

// This is how I feel about my classes this quarter
// This function acts as a pause so you can more clearly see the interesting
// parts around this call, such as the buffering above.
// This is probably a life lesson about mindless work.
int mindlessWork() {
    double sum = 0;
    for (int i = 0; i < 400000000; ++i) {
        sum += i/999959;
        // large prime number so compiler can't optimize :)
    }
    return sum;
}

// Prints the first 100 integers including an endl at the end of each line
// Returns the duration it took.
// Optional topic covered at end of lecture.
int endlEachTime() {
    auto startMove = std::chrono::high_resolution_clock::now(); // records start time

    for (int i = 0; i < 10000; ++i) {
        cout << i << endl;
    }

    auto stopMove = std::chrono::high_resolution_clock::now(); // records end time
    // don't worry too much about this syntax, you can google it easily
    // in fact, that's exactly what I did
    auto moveDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopMove - startMove);
    return moveDuration.count();
}

// Prints the first 100 integers including only a newline character after each line
// Returns the duration it took.
// Optional topic covered at end of lecture
int endlAtEnd() {
    auto startMove = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10000; ++i) {
        cout << i << '\n';
    }
    cout << flush;

    auto stopMove = std::chrono::high_resolution_clock::now();
    auto moveDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopMove - startMove);
    return moveDuration.count();
}

// This is a bad program, and is how most C++ beginners get themselves into
// trouble (so don't use it in CS 106B!)
// WE DID NOT GET TO THIS IN LECTURE, WILL BEGIN LECTURE 3 WITH THIS
void badWelcomeProgram() {
    string name, response;
    int age;

    cout << "What is your name? "; // sidenote: no flush needed! why?
    cin >> name;

    cout << "What is your age? ";
    cin >> age;

    cout << "Hello " << name << " (age " << age << ")" << '\n';

    cout << "Do you want to try again? ";
    cin >> response;

    cout << "You said: " << response << endl;
}

// Takes in any istream and prints the state bits

void printStateBits(const istream& iss) {
    cout << "State bits: ";

    /*
     *
     * Quick syntax lesson (Keith will teach this too!)
     * TERNARY OPERATOR
     * The following are equivalent:
     * [boolean] ? [statement 1] : [statement 2]
     *
     * if (boolean) {
     *     statement1
     * } else {
     *     statement2
     * }
     *
     * Many people (understandably) hate it, but it makes some expressions super short.
     *
     * int i = 0;
     * if (x > 100) i = 3;
     * else i = 5
     *
     * can replaced by...
     *
     * int i = (x > 100) ? 3 : 5;
     *
     */

    cout << (iss.good() ? "G" : "-");
    cout << (iss.fail() ? "F" : "-");
    cout << (iss.eof() ? "E" : "-");
    cout << (iss.bad() ? "B" : "-");
    cout << '\n';
    cout << "-----------" << '\n';
    // automatically flushed! why?
}

// splits a string with whitespace separated tokens
// into a vector of tokens
std::vector<string> stringSplit(const string& str) {
    std::vector<string> tokens;
    // to add a token to tokens, use tokens.push_back(token);
    return tokens;
}

// some fun with manipulators
// we're not gonna spend too much time on these
// just google them and find the one you want to use
void manipulatorFun() {
    cout << "[" << std::setw(10) << "Ito" << "]";
    cout << "[" << std::left << std::setw(10) << "Ito" << "]";
    cout << "[" << std::left << std::setfill('-')
         << std::setw(10) << "Ito" << "]";
    cout << endl;

}

// std::setw(n) 设置输出字段的宽度为  n 个字符。
// std::left 将输出内容左对齐。与 std::setw 结合使用时，内容会靠左对齐，填充字符会出现在右侧。
// std::setfill(c) 与 std::setw 结合使用时，填充字符会替换默认的空格

// Given a start time and a duration,
// calculate the end time.
// Assume correct formatting of string.

// input string: “1:30 PM \n 1 hour 20 minute”
// console string: “2:50 PM”

// Common bug: "1:30 PM \n 0 hour 30 minute"
// should print "2:00 PM", not "2:0 PM"
// Hint: use manipulators
void printEndTime(const string& input) {
    int startHour, durHour, endHour;
    int startMin, durMin, endMin;
    char trashChar;
    const string am = "AM", pm = "PM";
    string halfDay, trashString;

    istringstream iss(input);
    iss >> startHour; iss >> trashChar;
    iss >> startMin; iss >> halfDay;
    iss >> durHour; iss >> trashString;
    iss >> durMin; iss >> trashString;

    // turn it into 24 hour
    if (halfDay == pm && startHour != 12) startHour += 12;

    endHour = (startHour + durHour + ((startMin+durMin) >= 60 ? 1 : 0)) %24;
    endMin = (startMin + durMin) % 60;

    if (endHour > 12) {
        endHour -= 12;
        halfDay = pm;
    } else if (endHour == 12 && endMin != 0)
        halfDay = pm;
     else halfDay = am;

    cout << endHour << ':'
         << std::right << std::setfill('0') << std::setw(2) << to_string(endMin)
         << ' ' << halfDay << endl;
}

void testPrintEndTime() {
    printEndTime("1:30 PM \n 1 hour 20 minute");
    printEndTime("1:30 PM \n 0 hour 30 minute");
    printEndTime("11:45 PM \n 0 hour 15 minute");
    printEndTime("11:45 AM \n 0 hour 16 minute");
    printEndTime("12:00 AM \n 24 hour 0 minute");
    /* should see:
     * End time: 2:50 PM
     * End time: 2:00 PM
     * End time: 0:00 AM
     * End time: 12:01 PM
     * End time: 12:00 AM */
}

void printEndTimeAI(const string& input) {
    // Step 1: Parse input string
    istringstream iss(input);
    string startTime, ampm;
    int startHour, startMinute;
    char colon;
    iss >> startHour >> colon >> startMinute >> ampm;

    // Step 2: Convert start time to total minutes
    int totalMinutes = startHour * 60 + startMinute;
    if (ampm == "PM" && startHour != 12) {
        totalMinutes += 12 * 60; // Convert PM to 24-hour format
    }
    if (ampm == "AM" && startHour == 12) {
        totalMinutes -= 12 * 60; // Handle 12 AM case
    }

    // Step 3: Parse duration
    int durationHours, durationMinutes;
    string dummy;
    iss >> durationHours >> dummy >> durationMinutes;

    // Step 4: Calculate end time in total minutes
    totalMinutes += durationHours * 60 + durationMinutes;

    // Step 5: Convert total minutes back to HH:MM AM/PM format
    int endHour = (totalMinutes / 60) % 24;
    int endMinute = totalMinutes % 60;
    string endAmPm = (endHour < 12) ? "AM" : "PM";

    // Convert to 12-hour format
    if (endHour == 0) {
        endHour = 12; // 0:00 is 12:00 AM
    } else if (endHour > 12) {
        endHour -= 12;
    }

    // Step 6: Format and print the end time
    cout << "End time: " << endHour << ":"
         << setw(2) << setfill('0') << endMinute << " " << endAmPm << endl;
}
