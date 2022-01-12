
/*
tesztinput:

6 7
0 1
1 4
3 1
3 5
2 0
2 3
1 2

*/





#include <iostream>

#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

#include <algorithm>

class CsucslistasGraf
{
public:
	vector<vector<int>>* csucslista;
	int N;
	int M;

	CsucslistasGraf()
	{
		cin >> N >> M;

		csucslista = new vector<vector<int>>(N +1, vector<int>());


		for (int i = 0; i < M; i++)
		{
			int honnan;
			int hova;
			cin >> honnan >> hova;

			csucslista->at(honnan).push_back(hova);
			if (honnan != hova)
			{
				(*csucslista)[hova].push_back(honnan);
			}
		}
	}

	void diagnostics()
	{
		for (int i = 1; i < N+1; i++)
		{
			cout << i << ": [ ";
			for (auto& szomszed : csucslista->at(i))
			{
				cout << szomszed << " ";
			}
			cout << "]\n";
		}
	}

	

	int find_szelessegi(int csucs, bool (*predicate)(int))
	{
		vector<string> szin(N, "feher");
		queue<int> tennivalok;
		tennivalok.push(csucs);

		while (!tennivalok.empty())
		{
			int tennivalo = tennivalok.front();
			tennivalok.pop();
			if (predicate(tennivalo)) // feldolgoz�s = feket�re sz�nez�s
				return tennivalo;
			szin[tennivalo] = "fekete";

			for (int& szomszed : csucslista->at(tennivalo))
			{
				if (szin[szomszed] == "feher")
				{
					tennivalok.push(szomszed);
					szin[szomszed] = "szurke";
				}
			}
		}

		return -1;
	};


	vector<int> utvonal(int end, const vector<int>& honnan)
	{
		stack<int> verem;
		while (honnan[end] != -2)
		{
			verem.push(end);
			end = honnan[end];
		}
		vector<int> result;
		while (!verem.empty())
		{
			result.push_back(verem.top());
			verem.pop();
		}
		return result;
	}



	int count(int csucs, bool (*predicate)(int))
	{
		int db = 0;
		vector<string> szin(N, "feher");
		stack<int> tennivalok;
		tennivalok.push(csucs);

		while (!tennivalok.empty())
		{
			int tennivalo = tennivalok.top();
			tennivalok.pop();
			if (predicate(tennivalo))
				db++;
			szin[tennivalo] = "fekete";

			for (int& szomszed : csucslista->at(tennivalo))
			{
				if (szin[szomszed] == "feher")
				{
					tennivalok.push(szomszed);
					szin[szomszed] = "szurke";
				}
			}
		}
		return db;
	}

	
	bool connected()
	{
		return N = 0 || (N == count(0, [](int x) {return x == x; }));

	}

	~CsucslistasGraf()
	{
	}


private:

	pair<int, int> helye(int a, int b)
	{
		int i = 0;
		while (i < csucslista->at(a).size() && csucslista->at(a)[i] != b)
		{
			i++;
		}

		int j = 0;
		while (j < csucslista->at(b).size() && csucslista->at(b)[j] != a)
		{
			j++;
		}

		pair<int, int> p{ i,j };
		return p;
	}
};

string to_string(vector<int> v)
{
	string sum = "[";
	for (int& i : v)
	{
		sum += " " + to_string(i);
	}
	return sum + " ]";
}

int main()
{
	CsucslistasGraf cslgraf;

	cslgraf.diagnostics();


}


/*
tesztinput
5 4
1 5
1 5
3 2
2 4

*/
