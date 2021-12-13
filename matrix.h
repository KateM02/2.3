#pragma once
#include <iostream>
#include <complex>
#include <vector>

struct comparator_for_class_matrix 
{
	bool operator()(std::complex<int> lhs, std::complex<int> rhs) const
	{
		return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
	}
	bool operator()(std::complex<double> lhs, std::complex<double> rhs) const 
	{
		return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
	}
	bool operator()(std::complex<float> lhs, std::complex<float> rhs) const 
	{
		return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
	}
};

template <typename T, typename TComparator = std::less <T>>
class matrix
{
private:
	std::vector<std::vector<T>> _mat;
	int _col, _row;
public:

	matrix()
	{
		_row = 0;
		_col = 0;
	}

	matrix(const int row, const int col)
	{
		_row = row;
		_col = col;
		_mat.resize(_row);
		for (int i = 0; i < _row; i++)
		{
			_mat[i].resize(_col);
		}
	}

	int get_row() const
	{
		return _row;
	}

	int get_col() const
	{
		return _col;
	}

	void set_col(const int col)
	{
		_col = col;
		_mat.resize(_col);
	}

	void set_row(const int row)
	{
		_row = row;
		for (int i = 0; i < _col; i++)
		{
			_mat.resize(_row);
		}
	}

	T& operator() (const int row, const int col)
	{
		if (col >= _col || row >= _row || col < 0 || row < 0)
		{
			throw std::logic_error("no such index exists");
		}
		return _mat[row][col];
	}

	T operator()(const int row, const int col) const
	{
		if (col >= _col || row >= _row || col < 0 || row < 0)
		{
			throw std::logic_error("no such index exists");
		}
		return _mat[row][col];
	}
	matrix<T, comparator_for_class_matrix> operator + (const matrix& c) const
	{
		if (_col != c._col || _row != c._row)
		{
			throw std::logic_error("matrices of different sizes cannot be stacked");
		}

		matrix<T, comparator_for_class_matrix> res(_row, _col);
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				res._mat[i][j] = _mat[i][j] + c._mat[i][j];
			}
		}
		return res;
	}

	matrix<T, comparator_for_class_matrix> operator -  (const matrix& c) const
	{
		if (c._col != _col || c._row != _row)
		{
			throw std::logic_error("matrices of different sizes cannot be subtracted");
		}

		matrix<T, comparator_for_class_matrix> res(_row, _col);
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				res._mat[i][j] = _mat[i][j] - c._mat[i][j];
			}
		}
		return res;
	}

	matrix<T, comparator_for_class_matrix> operator * (const matrix& c) const
	{
		if (_col != c._row)
		{
			throw std::logic_error("the number of rows of the first matrix is not equal to the number of columns of the second");
		}

		matrix<T, comparator_for_class_matrix> res(_row, c._col);

		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < c._col; j++)
			{
				res._mat[i][j] = 0;
				for (int k = 0; k < _col; k++)
				{
					res._mat[i][j] += _mat[i][k] * c._mat[k][j];
				}
			}
		}
		return res;
	}

	matrix<T, comparator_for_class_matrix> operator * (const T a) const
	{
		matrix<T, comparator_for_class_matrix> res(_row, _col);
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				res._mat[i][j] = _mat[i][j] * a;
			}
		}
		return res;
	}

	matrix<T, comparator_for_class_matrix> operator / (const T a) const
	{
		T b = 0;
		if (a == b)
		{
			throw std::logic_error("you cannot divide by zero");
		}
		matrix<T, comparator_for_class_matrix> res(_row, _col);
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				res._mat[i][j] = _mat[i][j] / a;
			}
		}
		return res;
	}

	bool operator == (const matrix& c) const
	{
		if (_row == c._row && _col == c._col)
		{
			for (int i = 0; i < _row; i++)
			{
				for (int j = 0; j < _col; j++)
				{
					if (_mat[i][j] != c._mat[i][j])
						return false;
				}
			}
			return true;
		}
		return false;
	}

	bool operator != (const matrix& c) const
	{
		//if (_row == c._row && _col == c._col)
		//{
		//	for (int i = 0; i < _row; i++)
		//	{
		//		for (int j = 0; j < _col; j++)
		//		{
		//			if (_mat[i][j] != c._mat[i][j])
		//				return true;
		//		}
		//	}
		//	return false;
		//}
		//return true;
		return !this->operator==(c);
	}
	auto begin() 
	{
		return _mat.begin();
	}
	auto end() 
	{
		return _mat.end();
	}
	auto cbegin() 
	{
		return _mat.cbegin();
	}
	auto cend() 
	{
		return _mat.cend();
	}

};

//template<typename T>
//double finding_a_trace(const matrix<std::complex<T>, comparator_for_class_matrix>& c)
//{
//	if (c.get_row() != c.get_col())
//	{
//		throw std::logic_error("matrix is not square");
//	}
//	double a = 0;
//	for (int i = 0; i < c.get_col(); i++)
//	{
//		a += c(i, i).real();
//	}
//	return a;
//}
template<typename T>
T finding_a_trace(const matrix<T, comparator_for_class_matrix>& c)
{
	if (c.get_row() != c.get_col())
	{
		throw std::logic_error("matrix is not square");
	}
	T a = 0;
	for (int i = 0; i < c.get_col(); i++)
	{
		a += c(i,i);
	}
	return a;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const matrix<T, comparator_for_class_matrix>& a)
{
	for (int i = 0; i < a.get_row(); i++)
	{
		for (int j = 0; j < a.get_col(); j++)
		{
			out << a(i, j) << " ";
		}
		out << std::endl;
	}
	return out;
}
template <typename T>
std::istream& operator >> (std::istream& in, const matrix<T, comparator_for_class_matrix>& a)
{
	for (int i = 0; i < a.get_row(); i++)
	{
		for (int j = 0; j < a.get_col(); j++)
		{
			std::cout << "[" << i << "][" << j << "] : ";
			in >> a(i, j);
		}
	}
	return in;
}
template <typename T>
std::istream& operator>>(std::istream& in, matrix<std::complex <T>, comparator_for_class_matrix>& lhs) {
	for (int i = 0; i < lhs.get_col(); i++) {
		for (int j = 0; j < lhs.get_row(); j++) {
			T real = 0, imagine = 0;
			std::cout << "\nData [" << i << ", " << j << "]\nInput real part: ";
			std::cin >> real;
			std::cout << "Input imagine part: ";
			std::cin >> imagine;
			lhs(i, j) = { real, imagine };
		}
	}
	return in;
}