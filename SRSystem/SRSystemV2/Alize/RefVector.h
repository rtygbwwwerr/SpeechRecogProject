

#if !defined(ALIZE_RefVector_h)
#define ALIZE_RefVector_h

#if defined(_WIN32)
#if defined(ALIZE_EXPORTS)
#define ALIZE_API __declspec(dllexport)
#else
#define ALIZE_API __declspec(dllimport)
#endif
#else
#define ALIZE_API
#endif

#if defined(_WIN32)
#pragma warning( disable : 4150)			// disable warning 4150 due to virtual SegCluster functions
#endif


#include "Object.h"
#include <new>
#include <memory.h>
#include "Exception.h"
#include "DoubleSquareMatrix.h"
#include "Feature.h"

namespace alize
{
  /// This class implements a growable template array of objects.
  /// Note that the array just store pointers on the elements.
  /// If you delete the array, the pointed objects are not deleted.
  /// To delete all the pointed objects, call deleteAllObjects()
  ///
  /// @author Frederic Wils  frederic.wils@lia.univ-avignon.fr
  /// @version 1.0
  /// @date 2006

  template <class T> class ALIZE_API RefVector : public Object
  {
    friend class TestRefVector;
  
  public:
  
    /// Create an RefVector object.
    /// @param capacity maximum number of elements in the array\n
    ///    The capacity will automatically grow when the size will
    ///    overtake the capacity
    /// @param reserve when the capacity grow, a number of locations
    ///    equals to this value is added to the vector.
    ///
    explicit RefVector(unsigned long capacity = 1)
    :Object(), _size(0), _capacity(capacity!=0?capacity:1),
     _array(createArray()) {}

    RefVector(const RefVector<T>& v)
    :Object(), _size(v._size), _capacity(v._size!=0?v._size:1),
    _array(createArray())
    { memcpy(_array, v._array, _size*sizeof(_array[0])); }
    
    const RefVector<T>& operator=(const RefVector<T>& v)
    {
      if (this != &v)
      {
        assert(_array != NULL);
        _size = v._size;
        if (_capacity < _size)
        {
          delete[] _array;
          _capacity = _size!=0?_size:1;
          _array = createArray();
        }
        memcpy(_array, v._array, _size*sizeof(_array[0]));
      }
      return *this;
    }

    virtual ~RefVector() { delete[] _array; }

    void clear() { _size = 0; }

    /// Adjusts the size of the internal array
    /// Take care of consequences if the new capacity is smaller than the
    /// actual capacity
    /// @param c new capacity
    ///
    void setCapacity(unsigned long newCapacity)
    {
      T** oldArray = _array;
      _capacity = newCapacity!=0?newCapacity:1;
      _array = createArray();
      memcpy(_array, oldArray, _size*sizeof(_array[0]));
      delete[] oldArray;
      if (_size > _capacity)
        _size = _capacity;
    }

    unsigned long size() const { return _size; }
    bool isEmpty() const{ return _size == 0; }
    
    /// Appends an object to the end of the vector
    /// @param o the object to add
    /// @return the index of the added object
    ///
    unsigned long addObject(T& o)
    {
      assert(_array != NULL);
      if (_size == _capacity)
      {
        _capacity += _capacity;
        T** oldArray = _array;
        _array = createArray();
        memcpy(_array, oldArray, _size*sizeof(_array[0]));
        delete[] oldArray;
      }
      _array[_size] = &o;
      _size++;
      return _size-1;
    }
    
    /// Inserts an object at a specified place
    /// @param o the object to add
    /// @param i index
    /// @return the index of the added object
    ///
    unsigned long addObject(T& o, unsigned long i)
    {
      // TODO : ?optimiser
      if (i>=_size)
        return addObject(o);
      addObject(getObject(_size-1));
      for (long t=_size-3; t>=(long)i; t--)
        setObject(getObject(t), t+1);
      setObject(o, i);
      return i;
    }
  
    /// Set an object at a specified location in the vector. Note
    /// that the previous object inside this location is not destroyed.
    /// @param o the object to store
    /// @param index an index into this vector
    /// @exception IndexOutOfBoundsException
    ///
    void setObject(T& o, unsigned long index) const
    {
      assertIsInBounds(__FILE__, __LINE__, index, _size);
      assert(_array != NULL);
      _array[index] = &o;
    }
  
    /// Returns the object at the specified index
    /// @param index an index into this vector
    /// @return a reference to the object at the specified index
    /// @exception IndexOutOfBoundsException
    ///
    T& getObject(unsigned long index) const
    {
      assertIsInBounds(__FILE__, __LINE__, index, _size);
      assert(_array != NULL);
      return *_array[index];
    }

    T& operator[](unsigned long index)
    {
      assertIsInBounds(__FILE__, __LINE__, index, _size);
      assert(_array != NULL);
      return *_array[index];
    }
    const T& operator[](unsigned long index) const
    {
      assertIsInBounds(__FILE__, __LINE__, index, _size);
      assert(_array != NULL);
      return *_array[index];
    }
    
    /// Returns the index of the object (the first found)
    /// @param o the object
    /// @return the index of the object
    /// @exception Exception if the object cannot be found
    ///
    unsigned long getObjectIndex(const T& o) const
    {
      for (unsigned long i=0; i< _size; i++)
        if (_array[i] == &o)
          return i;
      throw Exception("Object not found", __FILE__, __LINE__);
      return 0; // never executed
    }
  
    /// Removes a set of objects from the array.
    /// @param first index of the first object to remove
    /// @param last index of the last object to remove
    /// @param fl DELETE = remove and delete the objects
    ///           <br>DO_NOT_DELETE = remove but do not delete the objects
    ///
    void removeObjects(unsigned long first, unsigned long last,
                       DeleteFlag fl = DO_NOT_DELETE)
    {
      if (last>_size-1)
        last = _size-1;
      if (first > last)
        return;
      assert(_array != NULL);
      if (fl == DELETE)
        for (unsigned long i=first; i<=last; i++)
          delete _array[i];
      last++;
      for (; last<_size; first++, last++)
        _array[first] = _array[last];
      _size -= last-first;
    }

    /// Removes an object from the array.
    /// @param i index of the object to remove
    /// @return the removed object
    ///
    T& removeObject(unsigned long i)
    {
      T& o = getObject(i);
      for (; i+1<_size; i++)
        _array[i] = _array[i+1];
      _size--;
      return o;
    }
    
    /// Remove the first occurence of an object
    /// @param o the object to remove
    /// @return the removed object (same as o)
    /// @exception Exception if the object is not referenced in the
    ///      vector
    ///
    const T& removeObject(const T& o)
    {
      for (unsigned long i=0; i<_size; i++)
      {
        if (_array[i] == &o)
        {
          for (i++; i<_size; i++)
            _array[i-1] = _array[i];
          _size--;
          return o;
        }
      }
      throw Exception("Object not found in the vector", __FILE__, __LINE__);
    }

    /// Use this method to access directly to the internal vector
    /// @return a pointer on the first element
    /// @warning Fast but dangerous ! Use preferably set and get.
    ///
    T** getArray() const { return _array; }

    void deleteAllObjects(unsigned long first = 0)
    {
		
      for (unsigned long i=first; i<_size; i++)
        delete _array[i];
      _size = first<_size?first:_size;
		
    }

    virtual String getClassName() const { return "RefVector"; }

  private:
  
    unsigned long _size;
    unsigned long _capacity;
    T**    _array;

    T** createArray()
    {
      assert(_capacity != 0);
      T** p = new (std::nothrow) T*[_capacity];
      assertMemoryIsAllocated(p, __FILE__, __LINE__);
      return p;
    }
	//bool operator==(const RefVector<T>&) const; /*!Not implemented*/
    //bool operator!=(const RefVector<T>&) const; /*!Not implemented*/
  };

  typedef RefVector<Object> ObjectRefVector;

#if defined(_WIN32)
  template class RefVector<Object>;
  template class RefVector<DoubleSquareMatrix>;
  template class RefVector<DoubleVector>;
  template class RefVector<ULongVector>;
  template class RefVector<SegCluster>;
  template class RefVector<MixtureGDStat>;
  template class RefVector<MixtureStat>;
  template class RefVector<Feature>;
  template class RefVector<XList>;
  template class RefVector<MixtureGD>;
#endif

} // end namespace alize

#endif // ALIZE_RefVector_h










