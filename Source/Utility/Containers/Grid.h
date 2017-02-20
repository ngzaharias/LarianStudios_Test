#include <vector>

struct GridCoord
{
public:
	GridCoord() { }
	GridCoord(int col, int row) : column(col), row(row) { }

public:
	int column = 0;
	int row = 0;
};

template<class T>
class Grid
{
public:
	Grid() { }
	~Grid() { }

public:
	T Get(int column, int row) const
	{
		return nullptr;
	}

	T Get(const GridCoord& coord) const
	{
		return nullptr;
	}

	void Set(int column, int row, const T& value)
	{
		int index = ToIndex(column, row);
		m_vector[index] = value;
	}

	void Set(const GridCoord& coord, const T& value)
	{
		int index = ToIndex(coord);
		m_vector[index] = value;
	}

	T AtIndex(int index) const
	{
		return m_vector[index];
	}

	void Clear()
	{
		m_vector.clear();
	}

	void Resize(int columns, int rows)
	{
		m_columns = columns;
		m_rows = rows;
		m_vector.resize(m_columns * m_rows, nullptr);
	}

	int Size() const
	{
		return m_vector.size();
	}

	int ToIndex(int column, int row) const 
	{ 
		return column + (row * m_columns); 
	}

	int ToIndex(const GridCoord& coord) const 
	{ 
		return coord.column + (coord.row * m_columns); 
	}

private:
	int m_columns = 0;
	int m_rows = 0;

	std::vector<T> m_vector;
};
