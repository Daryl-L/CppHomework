#include <iostream>
#include <iterator>

using std::string;
using std::begin;
using std::end;
using std::cout;
using std::endl;
using std::ostream;

class Large
{
private:
	int carry;
	int *num;
	size_t length;

public:
	Large(const string &num = "0")
	{
		carry = 0;
		length = num.size();
		this->num = new int[length];
		auto p = this->num + length - 1;
		for (auto v : num)
		{
			if (!isdigit(v))
			{
				cout << "Wrong input!" << endl;
				exit(1);
			}
			*p = v - '0';
			--p;
		}
	}

	Large(const Large &copySource)
	{
		length = copySource.length;
		num = new int[length];
		for (size_t count = 0; count < length; count++)
		{
			num[count] = copySource.num[count];
		}
		carry = 0;
	}

	friend ostream &operator<<(ostream &os, const Large &out);

	Large operator+(const Large &addition)
	{
		string sum;
		for (size_t count = 0; count < length || count < addition.length; count++)
		{
			int additionTemp1 = (count >= length ? 0 : num[count]);
			int additionTemp2 = (count >= addition.length ? 0 : addition.num[count]);
			int temp = carry + additionTemp1 + additionTemp2;
			carry = temp / 10;
			sum = (char)('0' + (temp % 10)) + sum;
		}

		return Large(sum);
	}
};

ostream &operator<<(ostream &os, const Large &out)
{
	for (size_t count = out.length - 1; count < out.length; count--)
	{
		os << *(out.num + count);
	}

	return os;
}

int main(void)
{
	Large a("19865541244563246523545566");
	Large b("7546837846541534764568345634");
	Large c(a + b);

	cout << c << endl;
	
	return 0;
}