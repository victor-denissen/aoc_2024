#ifndef GRID_HPP
# define GRID_HPP
#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>

// Custom class: grid
template <typename T>
class	grid
{
	public:
		// Constructor
		grid	(int, int);

		// Destructor
		~grid	(void);

		// Getters
		size_t	getSizeY()const;
		size_t	getSizeX()const;

		// Accessors
		T &	at(std::pair<int, int>)const;
		T &	at(size_t, size_t)const;
		
		// Inserters
		void	insert(T, size_t, size_t);
		void	insert(T, std::pair<int, int>);

		void	insertRow(T, size_t);
		void	insertColumn(T, size_t);
		void	insertAll(T);
		void	insertString(std::string, size_t);

	private:
		T **		_grid;
		const size_t	_size_y;
		const size_t	_size_x;

		bool		_outOfBounds(size_t, size_t)const;
		bool		_outOfXBounds(size_t)const;
		bool		_outOfYBounds(size_t)const;
		void		_throwOutOfBounds()const;

};

using namespace std;

// Constructor
template <typename T>
grid<T>::grid(int size_y, int size_x): _size_y(size_y), _size_x(size_x)
{
	_grid = new T*[size_y];
	for (int i = 0; i < size_y; i++)
		_grid[i] = new T[size_x]{};
}

// Destructor
template <typename T>
grid<T>::~grid(void)
{
	cout << "grid:\tdestroying object\n";
	for (int y = 0; y < _size_y; ++y)
		delete[] _grid[y];
	delete[] _grid;
}

// Getters
template <typename T>
size_t	grid<T>::getSizeY()const
{
	return _size_y;
}

template <typename T>
size_t	grid<T>::getSizeX()const
{
	return _size_x;
}

// Accessors
template <typename T>
T &	grid<T>::at(size_t y, size_t x)const
{
	if (_outOfBounds(y, x))
		_throwOutOfBounds();
	return _grid[y][x];
}

template <typename T>
T &	grid<T>::at(pair<int, int> coords)const
{
	return at(coords.first, coords.second);
}

// Inserters
template <typename T>
void	grid<T>::insert(T t, size_t y, size_t x)
{
	if (_outOfBounds(y, x))
		_throwOutOfBounds();	
	at(y, x) = t;
}

template <typename T>
void	grid<T>::insert(T t, pair<int, int> p)
{
	insert(t, p.first, p.second);
}

template <typename T>
void	grid<T>::insertRow(T t, size_t y)
{
	if (_outOfYBounds(y))
		_throwOutOfBounds();
	for (size_t x = 0; x < _size_x; ++x)
		insert(t, y, x);
}

template <typename T>
void	grid<T>::insertColumn(T t, size_t x)
{
	if (_outOfXBounds(x))
		_throwOutOfBounds();
	for (size_t y = 0; y < _size_y; ++y)
		insert(t, y, x);
}

template <typename T>
void	grid<T>::insertAll(T t)
{
	for (int y = 0; y < _size_y; ++y)
		for (int x = 0; x < _size_x; ++x)
			insert(t, y, x);
}

template <typename T>
void	grid<T>::insertString(string str, size_t y)
{
	if (_outOfYBounds(y))
		_throwOutOfBounds();
	if (_outOfXBounds(str.size()))
		cout <<  "WARNING:" <<  "String is too long, some data will be lost" << endl;
	for (int x = 0; x < (str.size() > _size_x? _size_x: str.size()); x++)
		insert(str[x], y, x);
	
}

// << operator
template <typename T>
ostream& operator<<(ostream & o, const grid<T> & g)
{
	size_t xSize = g.getSizeX();
	size_t ySize = g.getSizeY();
	for (int y = 0; y < ySize; ++y)
	{
		for (int x = 0; x < xSize; ++x)
			cout << "[" << g.at(y, x) << "]";
		cout << endl;
	}
	return o;
}

// Out of bounds checks
template <typename T>
bool	grid<T>::_outOfBounds(size_t y, size_t x) const
{
	return _outOfYBounds(y) || _outOfXBounds(x);
}

template <typename T>
bool	grid<T>::_outOfXBounds(size_t x) const
{
	if (x >= _size_x)
		return true;
	return false;
}

template <typename T>
bool	grid<T>::_outOfYBounds(size_t y) const
{
	if (y >= _size_y)
		return true;
	return false;
}

template <typename T>
void	grid<T>::_throwOutOfBounds()const
{
	throw out_of_range("Given co-ordinates do no lie within the grid");
}

#endif

