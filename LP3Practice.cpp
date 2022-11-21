// ATHARVA BELEKAR
// LP3 DAA ASSIGNMENTS

#include <bits/stdc++.h>
using namespace std;

#define fast_io		ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)


// ----------------- FIBONACCI -----------------
int recFibo(int n)
{
	if (n == 1)
		return 0;
	if (n == 2)
		return 1;
	return (recFibo(n - 1) + recFibo(n - 2));
}

void iterFibo(int n)
{
	if (n == 1)
	{
		cout << "0" << endl;
		return;
	}

	cout << "0 1";
	if (n == 2)
		return;

	int f1 = 1;
	int f2 = 0;
	int curr = 0;
	for (int i = 3; i <= n; ++i)
	{
		curr = f1 + f2;
		cout << " " << curr;
		f2 = f1;
		f1 = curr;
	}
}


// ----------------- HUFFMAN ENCODING -----------------
struct MinHeapNode
{
	string data;
	unsigned freq;
	MinHeapNode *left, *right;

	MinHeapNode(string data, unsigned freq)
	{
		this->left = this->right = NULL;
		this->data = data;
		this->freq = freq;
	}
};


struct compare
{
	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		if (l->freq == r->freq)
			return (l->data > r->data);

		return (l->freq > r->freq);
	}
};

void printCodes(MinHeapNode* root, string str)
{
	if (!root)
		return;

	if (root->data.length() == 1)
		cout << root->data << " : " << str << endl;

	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

void HuffmanCodes(string data[], int freq[], int size)
{
	struct MinHeapNode *left, *right, *top;
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

	for (int i = 0; i < size; ++i)
		minHeap.push(new MinHeapNode(data[i], freq[i]));

	while (minHeap.size() != 1)
	{
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		top = new MinHeapNode(left->data + right->data, left->freq + right->freq);

		top->left = left;
		top->right = right;

		minHeap.push(top);
	}
	printCodes(minHeap.top(), "");
}


// ----------------- 0/1 KNAPSACK -----------------
// top-down approach (recursive)
int knapsackUtil(vector<int>& wt, vector<int>& val, int ind, int W, vector<vector<int>>& dp)
{
	if (ind == 0)
	{
		if (wt[0] <= W) return val[0];
		else return 0;
	}

	if (dp[ind][W] != -1)
		return dp[ind][W];

	int notTaken = 0 + knapsackUtil(wt, val, ind - 1, W, dp);

	int taken = INT_MIN;
	if (wt[ind] <= W)
		taken = val[ind] + knapsackUtil(wt, val, ind - 1, W - wt[ind], dp);

	return dp[ind][W] = max(taken, notTaken);
}

int knapsack(vector<int>& wt, vector<int>& val, int n, int W)
{
	vector<vector<int>> dp(n, vector<int>(W + 1, -1));
	return knapsackUtil(wt, val, n - 1, W, dp);
}

// bottom-up approach (tabulation)
int Knapsack(vector<int>& wt, vector<int>& val, int n, int W)
{
	vector<vector<int>> dp(n, vector<int>(W + 1, 0));

	for (int i = wt[0]; i <= W; ++i)
		dp[0][i] = val[0];

	for (int ind = 1; ind < n; ++ind)
	{
		for (int w = 0; w <= W; ++w)
		{
			int notTaken = 0 + dp[ind - 1][w];

			int taken = INT_MIN;
			if (wt[ind] <= w)
				taken = val[ind] + dp[ind - 1][w - wt[ind]];

			dp[ind][w] = max(taken, notTaken);
		}
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j <= W; ++j)
			cout << dp[i][j] << " ";
		cout << endl;
	}

	return dp[n - 1][W];
}


// ----------------- N QUEENS -----------------
int m[10][10];
int cnt = 0;
int x = 0, y = 0;
int n = 0;

bool isCorrect(int col, int row)
{
	// column
	for (int i = 0; i < row; ++i)
		if (m[i][col])
			return false;

	// north-west
	for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
		if (m[i][j])
			return false;

	// north-east
	for (int i = row, j = col; i >= 0 && j < n; --i, ++j)
		if (m[i][j])
			return false;

	return true;
}

void display()
{
	if (m[x - 1][y - 1])
	{
		cnt++;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
				cout << m[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		return;
	}
}

bool nqueens(int row)
{
	if (row == n)
	{
		display();
		return true;
	}

	// backtracking
	bool chk = false;
	for (int i = 0; i < n; ++i)
	{
		if (isCorrect(i, row))
		{
			m[row][i] = 1;
			chk = nqueens(row + 1) || chk;
			m[row][i] = 0;
		}
	}
	return chk;
}


// ----------------- QUICKSORT -----------------
int partition(int *a, int s, int e)
{
	int i = s - 1;
	int j = s;

	int random_ind = s + (std::rand() % (e - s + 1));
	swap(a[random_ind], a[e]);

	int partition = a[e];

	while (j < e)
	{
		if (a[j] <= partition)
		{
			i++;
			swap(a[i], a[j]);
		}
		j += 1;
	}
	// swap pivot to sorted position
	swap(a[i + 1], a[e]);
	return i + 1;
}

void quicksort(int *arr, int s, int e)
{
	if (s >= e)
		return;

	int p = partition(arr, s, e);
	quicksort(arr, s, p - 1);
	quicksort(arr, p + 1, e);
}


int32_t main()
{
	fast_io;

	// FIBONACCI
	// int n;
	// cin >> n;
	// for (int i = 1; i <= n; ++i)
	// 	cout << recFibo(i) << " ";
	// cout << endl;
	// iterFibo(n);


	// HUFFMAN ENCODING
	// string data[] = {"a", "b", "c", "d", "e"};
	// int freq[] = {3, 4, 2, 6, 4};
	// int size = sizeof(data) / sizeof(data[0]);
	// HuffmanCodes(data, freq, size);


	// KNAPSACK
	// vector<int> wt = {2, 3, 4, 5};
	// vector<int> val = {3, 4, 5, 6};
	// int W = 5;
	// int n = wt.size();
	// cout << "Maximum value = " << knapsack(wt, val, n, W) << endl << endl;
	// cout << "\nMaximum value = " << Knapsack(wt, val, n, W);


	// N Queens
	// cin >> n >> x >> y;
	// for (int i = 0; i < n; ++i)
	// 	for (int j = 0; j < n; ++j)
	// 		m[i][j] = 0;
	// bool chk = nqueens(0);
	// cout << "\nNumber of solutions = " << cnt << endl;


	// QUICKSORT
	// int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
	// int n = sizeof(arr) / sizeof(int);
	// quicksort(arr, 0, n - 1);
	// for (auto i : arr)
	// 	cout << i << " ";

	return 0;
}