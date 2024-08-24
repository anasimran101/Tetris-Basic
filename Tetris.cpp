#include <iostream>
//#include <windows.h>
using namespace std;
class tetris {
	int r = 20;
	int c = 26;
	int ** arr;
	int* pi;
	int* pj;
	int s_type;
	int state = 1;
public:
	tetris()
	{ 
		//making the board
		pi = new int[4];
		pj = new int[4];
		arr = new int* [r];
		for (int i = 0; i < r; i++)
		{
			arr[i] = new int[c] {};
		}
		for (int i = 0; i < r; i++)
			arr[i][0] = arr[i][c - 1] = 1;
		for (int i = 0; i < c; i++)
			arr[0][i] = arr[r - 1][i] = 1;
	}
	int move(int x, int y)
	{
		for (int i = 0; i < 4; i++)
		{
			int c1 = 1, p = 1;
			//check if there is a need for new block
			for (int j = 0; j < 4 && (p || c1); j++)
			{
				if (pi[i]+x == pi[j]) 
				{
					c1 = 0;
				}
				if (pj[i] + y == pj[j])
				{
					p = 0;
				}
			}
			if (c1 )
				if (arr[(pi[i] + x)][(pj[i])] != 0)
				{
					//check for if there is a line to remove
					int start = 1;
					for (int i = 1; i < r-1; i++)
					{
						int count = 0;
						for (int j = 1; j < c-1; j+=2) 
						{
							if (arr[i][j] != 0)
								++count;
						}
						if (count == 0)
							start = i;
						if (count == 12)
						{
							for (int w = i; w > start; --w)
								for (int z = 1; z < c - 1; z += 2)
									arr[w][z] = arr[w - 1][z];
							
						}
					}
					return 0;
				}
			if (p)
				if (arr[pi[i]][pj[i] + y] != 0)
				{
					return 1;
				}
					
		}
		// moving the block in the required direction
		for (int i = 0; i < 4; i++)
		{
			arr[pi[i]][pj[i]] = 0;
			pi[i] += x;
			pj[i] += y;
		}
		for (int i = 0; i < 4; i++)
			arr[pi[i]][pj[i]] = s_type;   
		return 2;
	}
	void display()
	{
		//printing the game
		cout << "       Tetris\n\n\n";
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j+=2)
			{
				
				switch (arr[i][j])
				{
				case 0:
					cout << "\x1B[40m  ";
					break;
				case 1:
					cout << "\x1B[46m ";
					--j;
					break;
				case 2:
					cout << "\x1B[41m[]";
					break;
				case 3:
					cout << "\x1B[43m[]";
					break;
				case 4:
					cout << "\x1B[45m[]";
					break;
				case 5:
					cout << "\x1B[44m[]";
					break;
				default:
					//cout << arr[i][j] << " ";
					break;
				}
			}
			cout << endl;
		}
		cout << "\x1B[40m";
	}
	bool shapes(int type)
	{
		state = 1;
		int w = c / 2;
		s_type = type + 1;
		switch (s_type)
		{
		//Square
		case 2:
			pi[0] = pi[1] = 1;
			pj[0] = pj[2] = w-2;
			pi[2] = pi[3] = 2;
			pj[1] = pj[3] = w;
			break;
		//T
		case 3:
			pi[2] = pi[1] = pi[3] = 2;
			pj[1] = w-2, pj[0] = pj[2] = w, pj[3] = w+2;
			pi[0] = 1;
			break;
		//Pole
		case 4:
			pj[0] = pj[1] = pj[2] = pj[3] = w;
			pi[0] = 1, pi[1] = 2, pi[2] = 3, pi[3] = 4;
			break;

		//L
		case 5:
			pj[0] = pj[1] = pj[2] = w;
			pi[0] = 1, pi[1] = 2, pi[2] = pi[3] = 3;
			pj[3] = w + 2;
			break;
		default:
			break;
		}
		
		for (int i = 0; i < 4; i++)
		{
			if (arr[pi[i]][pj[i]] != 0)
			{
				for (int i = 0; i < 4; i++)
					arr[pi[i]][pj[i]] = s_type;
				return true;
			}
				
		}
		for (int i = 0; i < 4; i++)
			arr[pi[i]][pj[i]] = s_type;
		return false;
	}
	void rotation()
	{
		for (int i = 0; i < 4; i++)
		{
			arr[pi[i]][pj[i]] = 0;
		}
		switch (s_type)
		{
			
			
			
		case 3:
			switch (state)
			{
			case 1:
				++pi[1], pj[1]+=2;
				break;
			case 2:
				++pi[0]; pj[0] -= 2;
				break;
			case 3:
				--pi[0], pj[0] += 2, pj[3] -= 4;
				break;
			case 4:
				pi[1] = pi[3], pj[1] = pj[3];
				pj[3] += 4;
				break;
			default:
				break;
			}
			
			break;
			//T
		case 4:

			
			break;

			//Pole
		case 5:
			
			break;

			//L
		case 6:
			
			break;
		default:

			break;
		}
		if (state == 4)
			state = 1;
		else
			state++;
		for (int i = 0; i < 4; i++)
			arr[pi[i]][pj[i]] = s_type;
	}
	void stopper()
	{

	}
	~tetris()
	{
		for (int i = 0; i < r; i++)
		{
			delete[]arr[i];
		}
		delete[]arr;
		delete[]pi;
		delete[]pj;
	}

};
int key_input(int& x, int& y, int& s)
{
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		x = 0, y = -2;
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		x = 0, y = 0;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		x = 0, y = 2;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		x = 2, y = 0;
	}
	else if (GetKeyState(VK_SPACE) & 0x8000)
	{
		x = 1, y = 0;
	}
	else
	{
		x = 1, y = 0;
	}
	return 0;
}
int over(bool flag)
{
	int choice = 0;
	if (flag)
	{
		system("cls");
		cout << "\nGame Over\n";
		cout << "Play Again\n";
		cout << "1. Yes\n2. No\n";
		cin >> choice;
		if (choice)
			system("cls");
	}
	return choice;
}
int main()
{
	while (1)
	{
		int ch = 0;
		bool flag;
		int speed = 500;
		srand(time(0));
		int X = 1, Y = 0;
		tetris t;
		flag = t.shapes(1);// (rand() % 4 + 1));
		int count = 0;
		while (1)
		{
			if (speed != 0 && count % 35000 == 0)
			{
				t.display();
				/*for (int i = 0; i < 30; i++)
					cout << "\x1b[A\b";*/
			}
			if (ch == 0) {}
			else if (ch == 1)
				break;
			else
				exit(0);
			if (count % 6 == 0)
				key_input(X, Y, speed);
			if (!(X + Y) && count % 40000 == 0)
			{
				t.rotation();
				X = 1;
			}
			if (count % 40300 == 0 && (X||Y))
			{
				if (!t.move(X, Y))
				{
					ch = over(t.shapes(1));//((rand() % 4 + 1)));
					speed = 500;
				}
			}
			count++;
			//Sleep(speed);
		}
	}
}