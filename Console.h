#ifndef _XIE2YUE_CONSOLE_H
#define _XIE2YUE_CONSOLE_H

#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <stack>
#include <ctime>

#include "PolynomialFactorization.h"

#define ll long long
#define mll ModuleLongLong
#define Z BigInt
#define Q Fraction

enum ConsoleColor {
    CC_BLACK         = 0,
    CC_BLUE          = 1,
    CC_GREEN         = 2,
    CC_CYAN          = 3,
    CC_RED           = 4,
    CC_MAGENTA       = 5,
    CC_BROWN         = 6,
    CC_LIGHTGRAY     = 7,
    CC_DARKGRAY      = 8,
    CC_LIGHTBLUE     = 9,
    CC_LIGHTGREEN    = 10,
    CC_LIGHTCYAN     = 11,
    CC_LIGHTRED      = 12,
    CC_LIGHTMAGENTA  = 13,
    CC_YELLOW        = 14,
    CC_WHITE         = 15,
    
    CC_DEFAULT       = 7,
    CC_TITLE         = 14,
    CC_SUCCESS       = 10,
    CC_ERROR         = 12,
    CC_WARNING       = 6,
    CC_INFO          = 11,
    CC_HIGHLIGHT     = 13,
    CC_MENU          = 10,
    CC_INPUT         = 15
};

class Console {
private:
    void SetColor(ConsoleColor Color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
    }
    
    void gotoPosition(int x, int y) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)x, (short)y });
    }
    
    template<typename _T>
    void printAtPosition(int x, int y, _T outPut, ConsoleColor Color = CC_DEFAULT) {
        SetColor(Color);
        gotoPosition(x, y);
        std::cout << outPut;
    }
    
    void clear() {
        system("cls");
    }
    
    void pause() {
        _getch();
    }

public:
    void ConSoleInitialization(const char* header) {
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
        
        SetConsoleTitleA(header);
        
        HWND hwnd = GetConsoleWindow();
        MoveWindow(hwnd, 86, 50, 1080, 640, TRUE);
        
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD bufferSize = {86, 50};
        SetConsoleScreenBufferSize(hStdout, bufferSize);
        
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hStdout, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hStdout, &cursorInfo);
    }
    
    void ConsoleHywStart() {
        clear();
        printAtPosition(0, 0,
            "╔════════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║         和和和                   亿   亿亿亿亿亿亿亿        位        位           ║\n"
            "║     和和和     和和和和和       亿              亿         位   位位位位位位位     ║\n"
            "║         和     和      和      亿             亿          位                       ║\n"
            "║     和和和和和 和      和     亿亿          亿           位位             位       ║\n"
            "║         和     和      和    亿 亿        亿            位 位     位      位       ║\n"
            "║       和和和   和      和       亿      亿                 位     位      位       ║\n"
            "║      和 和  和 和      和       亿    亿                   位      位    位        ║\n"
            "║     和  和     和      和       亿  亿                     位      位    位        ║\n"
            "║         和     和      和       亿  亿            亿       位           位         ║\n"
            "║         和     和和和和和       亿  亿            亿       位           位         ║\n"
            "║         和                      亿   亿亿亿亿亿亿亿        位   位位位位位位位     ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                 和亿位计算器 v0.1                                  ║\n"
            "║                                                                                    ║\n"
            "║                                   作者 : Xie2Yue                                   ║\n"
            "║                                                                                    ║\n"
            "║                                   按任意键以启动                                   ║\n"
            "║                                                                                    ║\n"
            "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
        );
        pause();
    }
    
    std::stack<Q> NormalCalculatorNumberStorage;
    std::stack<char> NormalCalculatorOperatorStorage;
    short parenthesesCounters, firstNumberColumn, secondNumberColumn, secondNumberRow, ConsoleLength = 80, NormalCalculatorState, lengthofDivid;
    bool haveError;
    std::string NumberStreamScaner;
    char CursorOperator;
    
    void HywNormalCalculate(int times = -1) {
        int cnt = 0;
        while (NormalCalculatorNumberStorage.size() > 1) {
            auto opt = NormalCalculatorOperatorStorage.top();
            if (opt == '(') {
                if (times == -1) {
                    NormalCalculatorOperatorStorage.pop();
                    opt = NormalCalculatorOperatorStorage.top();
                } else if (times == -2) {
                    if (cnt == 0) {
                        NormalCalculatorOperatorStorage.pop();
                        opt = NormalCalculatorOperatorStorage.top();
                    } else {
                    	
					}return;
                } else if (times > 0) return;
            }
            NormalCalculatorOperatorStorage.pop();
            
            auto q2 = NormalCalculatorNumberStorage.top();
            NormalCalculatorNumberStorage.pop();
            auto q1 = NormalCalculatorNumberStorage.top();
            NormalCalculatorNumberStorage.pop();
            if (opt == '+') NormalCalculatorNumberStorage.push(q1 + q2);
            else if (opt == '-') NormalCalculatorNumberStorage.push(q1 - q2);
            else if (opt == '*') NormalCalculatorNumberStorage.push(q1 * q2);
            else if (opt == '/') NormalCalculatorNumberStorage.push(q1 / q2);
            else {
            }
            if (++cnt == times) break;
        }
    }
    
    void ConsoleHywNormalCalculatorActionClear() {
        while (NormalCalculatorNumberStorage.size()) NormalCalculatorNumberStorage.pop();
        while (NormalCalculatorOperatorStorage.size()) NormalCalculatorOperatorStorage.pop();
        NormalCalculatorNumberStorage.push(Q(0));
        NormalCalculatorOperatorStorage.push('+');
        parenthesesCounters = 0;
        firstNumberColumn = 1;
        secondNumberColumn = 1;
        secondNumberRow = 0;
        NormalCalculatorState = 2;
        NumberStreamScaner = "";
        CursorOperator = '+';
        clear();
        printAtPosition(0, 0,
            "╔════════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                                                                                    ║\n"
            "║ |0                                                                               | ║\n"
            "║ +                                                                                  ║\n"
            "║ |                                                                                | ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
        );
    }
    
    void ConsoleHywNormalCalculatorAction(int opt = 1) {
        if (opt == 1) {
            NormalCalculatorNumberStorage.push(Q(NumberStreamScaner));
            NumberStreamScaner = "";
        }
        HywNormalCalculate(opt);
        std::string endDelete = "";
        for (int i = 1; i < firstNumberColumn; ++i) {
            endDelete += "                                                                                      \n";
        }
        firstNumberColumn = 0;
        lengthofDivid = 0;
        auto outPut = " " + NormalCalculatorNumberStorage.top().toString();
        auto n = outPut.size() - 1;
        for (int i = 1; i <= n; ++i) {
            if ((i - lengthofDivid - 1) % ConsoleLength + 1 == 1) {
                printAtPosition(0, 1 + (++firstNumberColumn),
                    "║ |                                                                                | ║\n"
                );
            } else if (outPut[i] == '/') {
                printAtPosition(0, 1 + (++firstNumberColumn),
                    "║ ---------------------------------------------------------------------------------- ║\n"
                );
            } else if (outPut[i - 1] == '/') {
                printAtPosition(0, 1 + (++firstNumberColumn),
                    "║ |                                                                                | ║\n"
                );
            }
            if (outPut[i] == '/') {
                lengthofDivid = i;
            } else {
                printAtPosition(2 + (i - lengthofDivid - 1) % ConsoleLength + 1, 1 + firstNumberColumn, outPut[i]);
            }
        }
        secondNumberColumn = 1;
        secondNumberRow = 0;
        printAtPosition(0, 1 + firstNumberColumn + 1,
            "║ ?                                                                                  ║\n"
            "║ |                                                                                | ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "╚════════════════════════════════════════════════════════════════════════════════════╝\n" +
            endDelete
        );
        NormalCalculatorState = 1;
    }
    
    template<typename _T>
    void ConsoleHywNormalCalculatorError(_T ErrorInformation) {
        printAtPosition(2, 1 + firstNumberColumn + 1 + secondNumberColumn + 2, ErrorInformation);
        haveError = 1;
    }
    
    void ConsoleHywNormalCalculatorClearError() {
        if (!haveError) return;
        printAtPosition(0, 1 + firstNumberColumn + 1 + secondNumberColumn + 2,
            "║                                                                                    ║\n"
        );
        haveError = 0;
    }
    
    void ConsoleHywNormalCalculator() {
        ConsoleHywNormalCalculatorActionClear();
        char ch;
        while (1) {
            ch = _getch();
            ConsoleHywNormalCalculatorClearError();
            if (ch == 27) {
                return;
            } else if (ch == 'c' || ch == 'C') {
                ConsoleHywNormalCalculatorActionClear();
            } else if (48 <= ch && ch <= 57) {
                if (NormalCalculatorState == 1) continue;
                if (NormalCalculatorState == 2) NormalCalculatorState = 0;
                NumberStreamScaner.push_back(ch);
                printAtPosition(3 + secondNumberRow, 1 + firstNumberColumn + 1 + secondNumberColumn, ch);
                ++secondNumberRow;
                if (secondNumberRow == ConsoleLength) {
                    secondNumberRow = 0;
                    ++secondNumberColumn;
                    printAtPosition(0, 1 + firstNumberColumn + 1 + secondNumberColumn,
                        "║ |                                                                                | ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
                    );
                }
            } else if (ch == 8) {
                if (NormalCalculatorState == 1) continue;
                if (secondNumberColumn + secondNumberRow > 1) {
                    NumberStreamScaner.pop_back();
                    if (secondNumberRow == 0) {
                        secondNumberRow = ConsoleLength;
                        printAtPosition(0, 1 + firstNumberColumn + 1 + secondNumberColumn--,
                            "║                                                                                    ║\n"
                            "║                                                                                    ║\n"
                            "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
                            "                                                                                      \n"
                        );
                    }
                    printAtPosition(3 + --secondNumberRow, 1 + firstNumberColumn + 1 + secondNumberColumn, ' ');
                }
            } else if (ch == 13) {
                if (NormalCalculatorState == 1 || NumberStreamScaner.size() == 0) continue;
                ConsoleHywNormalCalculatorAction();
            } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                if (NumberStreamScaner.size() > 0) {
                    ConsoleHywNormalCalculatorAction();
                }
                CursorOperator = ch;
                printAtPosition(2, 1 + firstNumberColumn + 1, ch);
                if (NormalCalculatorState == 2) NormalCalculatorOperatorStorage.pop();
                NormalCalculatorOperatorStorage.push(ch);
                NormalCalculatorState = 2;
            } else if (ch == '(') {
                if (parenthesesCounters == 82) {
                    ConsoleHywNormalCalculatorError("Parentheses Limits Error");
                    continue;
                }
                if (NumberStreamScaner.size() > 0 || NormalCalculatorState == 1) continue;
                clear();
                printAtPosition(0, 0,
                    "╔════════════════════════════════════════════════════════════════════════════════════╗\n"
                    "║                                                                                    ║\n"
                    "║ |0                                                                               | ║\n"
                    "║ +                                                                                  ║\n"
                    "║ |                                                                                | ║\n"
                    "║                                                                                    ║\n"
                    "║                                                                                    ║\n"
                    "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
                );
                ++parenthesesCounters;
                gotoPosition(2, 1);
                for (int i = 1; i <= parenthesesCounters; ++i) std::cout << "(";
                NormalCalculatorOperatorStorage.push('(');
                NormalCalculatorNumberStorage.push(Q(0));
                NormalCalculatorOperatorStorage.push('+');
            } else if (ch == ')') {
                if (NormalCalculatorState == 2) continue;
                if (NumberStreamScaner.size() > 0) {
                    ConsoleHywNormalCalculatorAction();
                }
                printAtPosition(1 + parenthesesCounters--, 1, ' ');
                ConsoleHywNormalCalculatorAction(-2);
            } else if (ch == '=') {
                if (NormalCalculatorState == 2) continue;
                if (NumberStreamScaner.size() > 0) ConsoleHywNormalCalculatorAction();
                ConsoleHywNormalCalculatorAction(-1);
                printAtPosition(0, 1,
                    "║ |                                                                                | ║\n"
                );
                parenthesesCounters = 0;
            }
        }
    }

    Z NumberTheoryDataBigInt;
    ll NumberTheoryDataLongLongInt;
    
    void ConsoleHywNumberTheoryCalculator() {
        printConsoleHywNumberTheoryCalculator();
        char ch;
        while (1) {
            ch = _getch();
            if (ch == 27) {
                return;
            } else if (ch == '1') {
                while (1) {
                    clear();
                    printAtPosition(0, 0,
                        "╔════════════════════════════════════════════════════════════════════════════════════╗\n"
                        "║                                                                                    ║\n"
                        "║                                     请输入数据                                     ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
                    );
                    NumberStreamScaner = "";
                    while (1) {
                        ch = _getch();
                        if ('0' <= ch && ch <= '9') {
                            NumberStreamScaner.push_back(ch);
                        } else if (ch == 27) {
                        	break;
						} else if (ch == 13) {
                        	break;
						} else if (ch == 8) {
                            if (NumberStreamScaner.size() > 0) NumberStreamScaner.pop_back();
                        }
                        printAtPosition(38, 3, "          ");
                        printAtPosition(38, 3,
                            NumberStreamScaner.substr(NumberStreamScaner.length() - std::min(NumberStreamScaner.length(), size_t(10)))
                        );
                    }
                    if (ch == 27) break;
                    if (bigIntNumberTheory::isPrime(Z(NumberStreamScaner))) {
                        printAtPosition(40, 4, "是素数");
                    } else {
                        printAtPosition(39, 4, "不是素数");
                    }
                    printAtPosition(35, 6, "按下任意键以继续");
                    ch = _getch();
                    if (ch == 27) break;
                }
            } else if (ch == '2') {
                while (1) {
                    clear();
                    printAtPosition(0, 0,
                        "╔════════════════════════════════════════════════════════════════════════════════════╗\n"
                        "║                                                                                    ║\n"
                        "║                                请输入规模(二进制位)                                ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "║                                                                                    ║\n"
                        "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
                    );
                    NumberStreamScaner = "";
                    while (1) {
                        ch = _getch();
                        if ('0' <= ch && ch <= '9') {
                            NumberStreamScaner.push_back(ch);
                        } else if (ch == 27) {
                        	break;
						} else if (ch == 13) {
                            printAtPosition(33, 4, "  正在生成素数 ...");
                            break;
                        } else if (ch == 8) {
                            if (NumberStreamScaner.size() > 0) NumberStreamScaner.pop_back();
                        }
                        printAtPosition(33, 4, "          ");
                        printAtPosition(33, 4, NumberStreamScaner);
                    }
                    if (ch == 27) break;
                    auto outPut = bigIntNumberTheory::randomPrime((ll)(BigInt(NumberStreamScaner))).toString();
                    auto outLen = outPut.length();
                    for (int i = 0; i <= outLen; ++i) {
                        if (i % 82 == 0) {
                            printAtPosition(0, 6 + i / 82,
                                "║                                                                                    ║\n"
                            );
                        }
                        printAtPosition(2 + i % 82, 6 + i / 82, outPut[i]);
                    }
                    printAtPosition(0, 7 + outLen / 82,
                        "║                                                                                    ║\n"
                        "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
                    );
                    ch = _getch();
                    if (ch == 27) break;
                }
            } else if (ch == '3') {
                
            } else if (ch == '4') {
                
            }
        }
    }
    
    void printConsoleHywNumberTheoryCalculator() {
        clear();
        printAtPosition(0, 0,
            "╔════════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                                                                                    ║\n"
            "║          选择模式:                                                                 ║\n"
            "║                                                                                    ║\n"
            "║            1. 素数判断                                                             ║\n"
            "║                                                                                    ║\n"
            "║            2. 随机生成大素数                                                       ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
        );
    }
    
    void ConsoleHywPolynomialFactorization() {
        char ch;
        while (1) {
            printConsoleHywPolynomialFactorization();
            secondNumberRow = secondNumberColumn = 0;
            NumberStreamScaner = "";
            while (1) {
                ch = _getch();
                if (ch == 27) {
                    return;
                } else if ('0' <= ch && ch <= '9' || ch == 'x' || ch == '-' || ch == '+' || ch == '^') {
                    NumberStreamScaner.push_back(ch);
                    printAtPosition(2 + secondNumberRow, 4 + secondNumberColumn, ch);
                    ++secondNumberRow;
                    if (secondNumberRow == 82) {
                        secondNumberRow = 0;
                        ++secondNumberColumn;
                        printAtPosition(0, 4 + secondNumberColumn,
                            "║                                                                                    ║\n"
                            "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
                        );
                    }
                } else if (ch == 8) {
                    if (secondNumberColumn + secondNumberRow > 0) {
                        NumberStreamScaner.pop_back();
                        if (secondNumberRow == 0) {
                            secondNumberRow = 82;
                            printAtPosition(0, 4 + secondNumberColumn--,
                                "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
                                "                                                                                      \n"
                            );
                        }
                        printAtPosition(2 + --secondNumberRow, 4 + secondNumberColumn, ' ');
                    }
                } else if (ch == 13) {
                    break;
                }
            }
            auto pq = Polynomial<Q>(NumberStreamScaner);
            auto answer = PolynomialFactorization::Factorization(pq);
            auto outLen = answer.length();
            for (int i = 0; i <= outLen; ++i) {
                if (i % 82 == 0) {
                    printAtPosition(0, 6 + i / 82,
                        "║                                                                                    ║\n"
                    );
                }
                printAtPosition(2 + i % 82, 6 + i / 82, answer[i]);
            }
            printAtPosition(0, 7 + outLen / 82,
                "║                                                                                    ║\n"
                "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
            );
            ch = _getch();
            if (ch == 27) return;
        }
    }
    
    void printConsoleHywPolynomialFactorization() {
        clear();
        printAtPosition(0, 0,
            "╔════════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                                                                                    ║\n"
            "║                                  输入多项式(首一)                                  ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
        );
    }
    
    void ConsoleHywSelect() {
        printConsoleHywSelect();
        char ch;
        while (1) {
            ch = _getch();
            if (ch == '1') {
                ConsoleHywNormalCalculator();
            } else if (ch == '2') {
                ConsoleHywNumberTheoryCalculator();
            } else if (ch == '3') {
                ConsoleHywPolynomialFactorization();
            } else if (ch == '4' || ch == 27) {
                return;
            }
            printConsoleHywSelect();
        }
    }
    
    void printConsoleHywSelect() {
        clear();
        printAtPosition(0, 0,
            "╔════════════════════════════════════════════════════════════════════════════════════╗\n"
            "║                                                                                    ║\n"
            "║          选择模式:                                                                 ║\n"
            "║                                                                                    ║\n"
            "║            1. 传统计算器 (初版，暂只支持有理数)                                    ║\n"
            "║                                                                                    ║\n"
            "║            2. 数论工具 (初版，暂制支持整数环)                                      ║\n"
            "║                                                                                    ║\n"
            "║            3. 因式分解 (初版，暂只支持首一整多项式)                                ║\n"
            "║                                                                                    ║\n"
            "║            4. 退出计算器                                                           ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "║                                                                                    ║\n"
            "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
        );
    }
};

#undef Z
#undef Q
#undef ll
#undef mll
#endif