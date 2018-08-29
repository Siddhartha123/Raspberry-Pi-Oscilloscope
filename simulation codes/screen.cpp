#include "screen.h"
using namespace std;

/*
void CursorMove (unsigned nRow, unsigned nColumn);
TScreenColor
void Rotor (unsigned nIndex, unsigned nCount);
*/
int main(){
    Screen m_screen(640,480);
    //m_screen.display();
    m_screen.SetPixel(0,100);
    m_screen.SetPixel(100,100);
    m_screen.SetPixel(100,0);
    m_screen.SetPixel(0,0);
    
    m_screen.display();
    return 0;

}