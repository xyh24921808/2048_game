#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<easyx.h>
#include<random>
#include<queue>
#include<stack>
#include <graphics.h>
#include <conio.h>
#include <tchar.h>
#include<Windows.h>
using namespace std;

void reverseStack(stack<int>& st) 
{
	if (st.empty()) 
	{
		return;  // 栈为空，无需逆序
	}

	std::stack<int> tempStack;

	while (!st.empty()) 
	{
		int element = st.top();
		st.pop();
		tempStack.push(element);
	}

	st = tempStack;  // 将临时栈赋值给原始栈，实现逆序
}
class myclass
{
public:
	myclass(size_t r=4,size_t c=4,size_t winL=2048)
	{
		ROW = r;
		COL = c;
		minval = 2;
		maxval = 2;
		winler = winL;
		_grid.resize(r, vector<size_t>(c, 0));
		randcreat();
		randcreat();
	}

	void gamestart()
	{
		
		initgraph(ROW*112,COL*112);
		settextstyle(29, 0, _T("Consolas"));

		while (true)
		{
			printfG();
			if (maxval == winler)
			{
				break;
			}
			char ch = _getch();

			if(ch!='q')
			{
				switch (ch)
				{
					case 'a':
					{
						leftmove();
						break;
					}

					case 'd':
					{
						
						rightmove();
						break;
					}

					case 's':
					{
						downmove();
						break;
					}

					case 'w':
					{
						topmove();
						break;
					}
				}
				if (ch == 'a' || ch == 's' || ch == 'd' || ch == 'w')
				{
					randcreat();
				}
				
			}
			cleardevice();
		}
		
	}

	void printfG()
	{
		int CELLSIZE =(ROW*COL*100)/(ROW*COL);
		int windowWidth = getwidth();
		int windowHeight = getheight();

		int matrixWidth = ROW * CELLSIZE;
		int matrixHeight = COL * CELLSIZE;

		int startX = (windowWidth - matrixWidth) / 2;
		int startY = (windowHeight - matrixHeight) / 2;

		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				
				int x = startX + j * CELLSIZE;
				int y = startY + i * CELLSIZE;

				rectangle(x, y, x + CELLSIZE, y + CELLSIZE);

				if (_grid[i][j] == 0)
				{
					continue;
				}
				TCHAR s[5];
				_stprintf(s, _T("%d"), _grid[i][j]);		// 高版本 VC 推荐使用 _stprintf_s 函数
				outtextxy(x + CELLSIZE / 2 - 5, y + CELLSIZE / 2 - 10,s);
			}
		}
	}
	void printfG2()
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				cout << _grid[i][j] << " ";
			}
			cout << endl;
		}
	}
private:
	void right_and_left_move(int staus)
	{
		//带实现
	}
	void top_and_down_move(int staus)
	{
		//带实现
	}
	void rightmove()
	{
		for (auto&x:_grid)
		{
			stack<int>st;
			for (int j = x.size() - 1; j >= 0; j--)
			{
				if (x[j] != 0)
				{
					if (st.size() && st.top() == x[j])
					{
						st.pop();
						st.push(x[j] * 2);
						maxval = fmax(maxval, x[j] * 2);
					}
					else
					{
						st.push(x[j]);
					}
				}
				x[j] = 0;
			}

			int tmp = COL-1;
			reverseStack(st);
			while (st.size())
			{
				x[tmp--] = st.top();
				st.pop();
			}
		}
	}
	void leftmove()
	{
		
		for (auto& x : _grid)
		{
			stack<int>st;
			for (int j = 0; j <x.size(); j++)
			{
				if (x[j] != 0)
				{
					if (st.size() && st.top() == x[j])
					{
						st.pop();
						st.push(x[j] * 2);
						maxval = fmax(maxval, x[j] * 2);
						
					}
					else
					{
						st.push(x[j]);
					}
				}
				x[j] = 0;
			}

			int tmp = 0;
			reverseStack(st);
			while (st.size())
			{
				x[tmp++] = st.top();
				st.pop();
			}
		}
	}
	void topmove()
	{
		for (int i = 0; i < COL; i++)
		{
			stack<int>st;
			for (int j = 0; j < ROW; j++)
			{
				if (_grid[j][i] != 0)
				{
					if (st.size() && st.top() == _grid[j][i])
					{
						st.pop();
						st.push(_grid[j][i] * 2);
						maxval = fmax(_grid[j][i] * 2, maxval);
					}
					else
					{
						st.push(_grid[j][i]);
					}
				}
				_grid[j][i] = 0;
			}

			int tmp = 0;
			reverseStack(st);
			while (st.size())
			{
				_grid[tmp++][i] = st.top();
				st.pop();
			}
		}
	}
	void downmove()
	{
		for (int i = 0; i < COL; i++)
		{
			stack<int>st;
			for (int j = ROW-1; j >=0; j--)
			{
				if (_grid[j][i] != 0)
				{
					if (st.size() && st.top() == _grid[j][i])
					{
						st.pop();
						st.push(_grid[j][i] * 2);
						maxval = fmax(_grid[j][i] * 2, maxval);
					}
					else
					{
						st.push(_grid[j][i]);
					}
				}
				_grid[j][i] = 0;
			}

			

			int tmp = ROW-1;
			reverseStack(st);
			while (st.size())
			{
				_grid[tmp--][i] = st.top();
				st.pop();
			}
		}
	}
	bool isfu()
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (_grid[i][j] == 0)
				{
					return true;
				}
			}
		}
		return false;
	}
	void randcreat()
	{
		int x = rand() % ROW;
		int y = rand() % COL;
		while (isfu())
		{
			x = rand() % ROW;
			y = rand() % COL;
			if (_grid[x][y] == 0)
			{
				_grid[x][y] = minval;
				break;
			}
		}
	}
private:
	vector<vector<size_t>>_grid;
	size_t ROW;
	size_t COL;
	size_t winler=2048;
	size_t minval;
	size_t maxval;
};

int main(void)
{
	myclass c(5,5);
	c.gamestart();
	return 0;
}