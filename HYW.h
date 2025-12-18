#ifndef _XIE2YUE_HYW_H
#define _XIE2YUE_HYW_H


#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <stack>

#include "PolynomialFactorization.h"

#define ll long long
#define mll ModuleLongLong
#define Z BigInt
#define Q Fraction


class HYW {
private:
	std::fstream fileLogger;
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
	
	std::string NumberStreamScaner;
	ll mode;
	void HYW0() {
		fileLogger.open("user.hyw", std::ios::in | std::ios::out | std::ios::app );
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
            "║                               和亿位计算器 v.114514                                ║\n"
            "║                                                                                    ║\n"
            "║                                   作者 : Xie2Yue                                   ║\n"
            "║                                                                                    ║\n"
            "║                                 输入任意数字以启动                                 ║\n"
            "║                                                                                    ║\n"
            "╚════════════════════════════════════════════════════════════════════════════════════╝\n"
        );
        char ch;
        while(1) {
        	ch=_getch();
        	if(48 <= ch && ch <= 57) {
        		NumberStreamScaner.push_back(ch);
			} else if(ch == 13) {
				break;
			} else if(ch == 8) {
				if(NumberStreamScaner.size()) NumberStreamScaner.pop_back();
			} else if(ch == 27) {
				return;
			}
		}
		mode = (ll)(Z(NumberStreamScaner));
		if(mode == 1) HYW1();
		else HYW2();
	}
	
    void HYW1Actionclear() {
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
	
	
	
	void HYW1() {
		clear();
		std::cout<<"你";Sleep(500);std::cout<<"想";Sleep(500);std::cout<<"和";Sleep(500);
		std::cout<<"出";Sleep(500);std::cout<<"怎";Sleep(500);std::cout<<"样";Sleep(500);
		std::cout<<"的";Sleep(500);std::cout<<"亿";Sleep(500);std::cout<<"位";Sleep(500);
		std::cout<<"?"; Sleep(500);std::cout<<"!"; Sleep(500);std::cout<<"&"; Sleep(500);
		std::cout<<"o"; Sleep(500);std::cout<<"^"; Sleep(500);std::cout<<"d"; Sleep(500);
		std::cout<<")"; Sleep(500);std::cout<<"-"; Sleep(500);std::cout<<"."; Sleep(500);
		std::cout<<"."; Sleep(500);std::cout<<".";
		pause();
		clear();
	}
	void HYW2() {
		clear();
		pause();
	}
};






#undef ll
#undef mll
#undef Z
#undef Q

#endif