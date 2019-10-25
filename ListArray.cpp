#include <iostream>
#include "ListArray.h"
using namespace std;


/*Constructor
 Pre: none
 Post: creates an empty list. Allocates enough memory for the list containing maxNumber data items.
 */
template <typename DataType>
List<DataType>::List( int maxNumber) :size(0), maxSize(maxNumber), cursor(-1)
{
    if(maxNumber <= 0)
    {
        throw logic_error("maxNumber must be bigger than 0.");
    }
    else
    {
        dataItems = new DataType[maxNumber];
    }
}


/*Constructor
 Pre: none
 Post: Copy constructor. Initializes the list to be equivalent to the source List object parameter.
 */
template <typename DataType>
List<DataType>::List ( const List& source )
{
    dataItems = new DataType[source.maxSize];
    maxSize = source.maxSize;
    size = source.size;
    cursor = source.cursor;
    
   
    for(int i = 0; i < maxSize; i++)
    {
        dataItems[i] = source.dataItems[i];
    }
}


/*Constructor
 Pre: none
 Post: Sets the list to be equivalent to the source object parameter and returns a reference to the object.
 */
template <typename DataType>
List<DataType>& List<DataType>:: operator= ( const List &source )

// Overloaded assignment operator. Resets a list object to contain a
// deep-copy of the provided model object, source.

{
    // Set buffer to correct size. If current buffer too small, allocate a new one.
    // NOTE: this also happens to protect against self-destruction.  Explicit
    // checks against &source vs. this will appear later (e.g. Stack).
    if( source.maxSize > maxSize ) {
        delete [] dataItems;
        dataItems = new DataType[maxSize];
    }
    
    maxSize = source.maxSize;
    size = source.size;
    cursor = source.cursor;
    
    for( int i=0; i < size; i++ ) {
        dataItems[i] = source.dataItems[i];
    }
    
    // Return an object reference to support multiple assignment.
    // E.g., "a = b = c".
    return *this;
}



/*Destructor
 Pre: none
 Post: frees the memory used to store the list.
 */
template <typename DataType>
List<DataType>::~List()
{
    delete [] dataItems;
}



/*Constructor
 Pre: List is not full.
 Post: Inserts newDataItem to the list.
 */
template <typename DataType>
void List<DataType>::insert(const DataType &newDataItem)
                        throw(logic_error)
{
    if (size >= maxSize)
        throw logic_error ("List is full.");
    else if (size != 0)
        {
            for(int i = size; i > cursor; i--)
            {
                dataItems[i] = dataItems[i-1];

            }
            dataItems[cursor + 1] = newDataItem;
            size++;
            cursor++;
        }
    else
    {
        dataItems[0] = newDataItem;
        size = 1;
        cursor = 0;
    }
}



/*Constructor
 Pre: List is not empty
 Post: Removes the data item marked by the cursor from the list.
 */
template <typename DataType>
void List<DataType>::remove() throw(logic_error)
{
    if(isEmpty())
    {
        throw logic_error("List is empty. Please add elements to the list.");
    }
    else if(size != 1)
    {
        for(int i = cursor; i < size; i++)
        {
            dataItems[i] = dataItems[i+1];
        }
        
        size--;
        
        if(cursor == size)
        {
            cursor = 0;
        }
    }
}



/*replace
 Pre: List is not empty
 Post: Replaces the data item marked by the cursor with newDataItem.
 */
template <typename DataType>
void List<DataType>::replace(const DataType &newDataItem) throw(logic_error)
{
    if(isEmpty())
    {
        throw logic_error("List is empty. Please add elements to the list.");
    }
    else
    {
        dataItems[cursor] = newDataItem;
    }
}



/*Clear
 Pre: none
 Post: Removes all the data items in the list.
 */
template <typename DataType>
void List<DataType>::clear()
{
    size = 0;
    cursor = -1;
}



/*IsEmpty
 Pre: none
 Post: Returns true if the list is empty. Otherwise, returns false.
 */
template <typename DataType>
bool List<DataType>::isEmpty() const
{
    return (size == 0);
}


/*Constructor
 Pre: none
 Post: Returns true if the list is full. Otherwise,returns false.
 */
template <typename DataType>
bool List<DataType>::isFull() const
{
    
    return (size == maxSize);
}


/*Constructor
 Pre: List is not empty.
 Post: moves the cursor to the data item at the beginning of the list.
 */
template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
    if(size != 0)
    {
        cursor = 0;
    }
    else
    {
        throw logic_error("The list is empty. Please add elements to the list");
    }
}


/*Constructor
 Pre: List is not empty.
 Post: moves the cursor to the data item at the end of the list.
 */
template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
    if(size != 0)
    {
        cursor = size - 1;
    }
    else
    {
        throw logic_error("The list is empty. Please add elements to the list");
    }
}




/*gotoNext
 Pre: List is not empty.
 Post: moves the cursor to the next data item in the list and returns true. Otherwise, returns false.
 */
template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
    if(size == 0)
    {
        throw logic_error ("The list is empty. Please add elements to the list");
    }
    
    if(cursor != (size - 1))
    {
        cursor++;
        return true;
    }
    else
    {
        return false;
    }
}


/*Constructor
 Pre: List is not empty.
 Post: moves the cursor to the preceding t data item in the list and returns true. Otherwise, returns false.
 */
template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
    if(size == 0)
    {
        throw logic_error ("The list is empty. Please add elements to the list");
    }
    
    if(dataItems[cursor] != 0)
    {
        cursor--;
        return true;
    }
    else
    {
        return false;
    }
}



/*Constructor
 Pre: List is not empty.
 Post: Returns the value of the data item marked by the cursor.
 */
template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
    if(size != 0)
    {
        return dataItems[cursor];
    }
    else
    {
        throw logic_error ("The list is empty. Cannot return the item.");
    }
}


/*Constructor
 Pre: none.
 Post: Output the data items in the list.
 */
template <typename DataType>
void List<DataType>:: showStructure () const

// outputs the data items in a list. if the list is empty, outputs
// "empty list". this operation is intended for testing/debugging
// purposes only.

{
    int j;
    
    if ( size == 0 )
        cout << "empty list" << endl;
    {
        cout << "size = " << size
        <<  "   cursor = " << cursor << endl;
        for ( j = 0 ; j < maxSize ; j++ )
            cout << j << "\t";
        cout << endl;
        for ( j = 0 ; j < size ; j++ ) {
            if( j == cursor ) {
                cout << "[";
                cout << dataItems[j];
#ifdef ORDEREDLIST_CPP
                .getKey()
#endif
                ;
                cout << "]";
                cout << "\t";
            }
            else
                cout << dataItems[j]
#ifdef ORDEREDLIST_CPP
                .getKey()
#endif
                << "\t";
        }
        cout << endl;
    }
}



 //Programming Exercise 3

/*Bool Find
 Pre: List is not empty.
 Post: Searches a list for searchDataItem.
 */
template <typename DataType>
bool List<DataType>::find(const DataType &searchDataItem) throw (logic_error)
{
    if(isEmpty())
    {
        throw logic_error ("List is empty. Please add elements to the list.");
    }
    else
    {
        for(int i = cursor; i < size; i++)
        {
            if(dataItems[i] == searchDataItem)
            {
                return true;
            }
            if(cursor + 1 < size)
            {
                cursor++;
            }
        }
    }
    return false;
}

