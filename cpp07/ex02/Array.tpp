#ifndef ARRAY_TPP
#define ARRAY_TPP





template <typename T>
Array<T>::Array() : _data(NULL), _size(0)
{
}






template <typename T>
Array<T>::Array(unsigned int n) : _data(NULL), _size(n)
{
	if (n > 0)
		_data = new T[n]();
}


template <typename T>
Array<T>::Array(const Array<T>& other) : _data(NULL), _size(other._size)
{
	if (_size > 0)
	{
		_data = new T[_size]();
		for (unsigned int i = 0; i < _size; ++i)
			_data[i] = other._data[i];
	}
}



template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this != &other)
	{
		delete[] _data;          
		_data = NULL;
		_size = other._size;
		if (_size > 0)
		{
			_data = new T[_size]();
			for (unsigned int i = 0; i < _size; ++i)
				_data[i] = other._data[i];
		}
	}
	return *this;
}



template <typename T>
Array<T>::~Array()
{
	delete[] _data;
}




template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _data[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw OutOfBoundsException();
	return _data[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
	return _size;
}


template <typename T>
const char* Array<T>::OutOfBoundsException::what() const throw()
{
	return "Array: index out of bounds";
}

#endif
